#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
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
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() < layouts.getMainInputChannelSet())
        return false;

    return true;
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;

    auto inputBuffer = getBusBuffer(buffer, true, 0);
    auto outputBuffer = getBusBuffer(buffer, false, 0);

    if (inputBuffer.getNumChannels() == 1) {
        auto* channelData = inputBuffer.getReadPointer(0);
        for (int i = 0; i < inputBuffer.getNumSamples(); i++) {
            auto output = mPanner.at(0)->process(channelData[i]);
            outputBuffer.getWritePointer(0)[i] = std::get<0>(output);
            outputBuffer.getWritePointer(1)[i] = std::get<1>(output);
        }
    }
    else {
        auto* inputL = inputBuffer.getReadPointer(0);
        auto* inputR = inputBuffer.getReadPointer(1);
        for (int i = 0; i < inputBuffer.getNumSamples(); i++) {
            auto outputL = mPanner.at(0)->process(inputL[i]);
            auto outputR = mPanner.at(1)->process(inputR[i]);

            outputBuffer.getWritePointer(0)[i] = std::get<0>(outputL);
            outputBuffer.getWritePointer(1)[i] = std::get<1>(outputR);
            outputBuffer.getWritePointer(0)[i] = std::get<0>(outputR);
            outputBuffer.getWritePointer(1)[i] = std::get<1>(outputL);
        }
    }

}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
