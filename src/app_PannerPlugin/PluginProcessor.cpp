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
        std::make_unique<juce::AudioParameterFloat>("offset", "Offset", -100, 100, 0)
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
    for (auto& panner : mPanner) {
        panner.reset(new Panner(sampleRate));
    }
}

void AudioPluginAudioProcessor::releaseResources()
{
    for (auto& panner : mPanner) {
        panner.reset();
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

    for (auto& panner : mPanner) {
        panner->setWidth(*mWidth);
        panner->setSpeed(*mSpeed);
        panner->setOffset(*mOffset);
    }

    auto inputBuffer = getBusBuffer(buffer, true, 0);
    auto outputBuffer = getBusBuffer(buffer, false, 0);

    for (int i = 0; i < inputBuffer.getNumSamples(); i++) {
        float outputSumL = 0.0f;
        float outputSumR = 0.0f;
        for (auto c = 0; c < inputBuffer.getNumChannels(); c++) {
            auto output = mPanner.at(c)->process(inputBuffer.getSample(c, i));
            outputSumL += std::get<0>(output);
            outputSumR += std::get<1>(output);
        }
        for (auto j = inputBuffer.getNumChannels(); j < mPanner.size(); j++) {
            mPanner.at(j)->process(0.0f); // Dummy call to keep lfos in sync
        }
        outputBuffer.getWritePointer(0)[i] = outputSumL;
        outputBuffer.getWritePointer(1)[i] = outputSumR;
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

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
