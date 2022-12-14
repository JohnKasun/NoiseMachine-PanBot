#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
    mParameters(*this, nullptr, juce::Identifier("Parameters"), {
        std::make_unique<juce::AudioParameterFloat>("width", "Width", 0, 100, 100),
        std::make_unique<juce::AudioParameterFloat>("speed", "Speed", 1, 5, 1),
        std::make_unique<juce::AudioParameterInt>("offset", "Offset", -100, 100, 0)
        })
{
    mWidth = mParameters.getRawParameterValue("width");
    mSpeed = mParameters.getRawParameterValue("speed");
    mOffset = mParameters.getRawParameterValue("offset");
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
    return false;
}

bool AudioPluginAudioProcessor::producesMidi() const
{
    return false;
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
    return false;
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused (sampleRate, samplesPerBlock);
    for (auto& panBot : mPanBot) {
        panBot.reset(new PanBotEngine(sampleRate));
    }
}

void AudioPluginAudioProcessor::releaseResources()
{
    for (auto& panBot : mPanBot) {
        panBot.reset();
    }
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    juce::ScopedNoDenormals noDenormals;

    for (auto& panBot : mPanBot) {
        panBot->setWidth(*mWidth);
        panBot->setSpeed(*mSpeed);
        panBot->setOffset(*mOffset);
    }

    auto inputBuffer = getBusBuffer(buffer, true, 0);
    auto outputBuffer = getBusBuffer(buffer, false, 0);

    for (int i = 0; i < inputBuffer.getNumSamples(); i++) {
        auto input = 0.0f;
        for (auto c = 0; c < inputBuffer.getNumChannels(); c++) {
            input += inputBuffer.getSample(c, i);
        }
        auto output = mPanBot.at(0)->process(input);
        outputBuffer.getWritePointer(0)[i] = output.first;
        outputBuffer.getWritePointer(1)[i] = output.second;
        updatePanPosition();
    }

}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this, mParameters);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mParameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName(mParameters.state.getType())) {
            mParameters.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

std::pair<float, float> AudioPluginAudioProcessor::getPanPosition() const
{
    return std::make_pair(mPanPositionL.load(), mPanPositionR.load());
}

void AudioPluginAudioProcessor::updatePanPosition()
{
    auto channelPositions = mPanBot.at(1)->process(100.0f);
    mPanPositionL.store(channelPositions.first);
    mPanPositionR.store(channelPositions.second);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
