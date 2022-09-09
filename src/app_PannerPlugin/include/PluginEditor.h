#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:

    enum {
        sliderWidth = 500,
        sliderHeight = 100,
        labelWidth = 100
    };
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:
    AudioPluginAudioProcessor& processorRef;
    juce::AudioProcessorValueTreeState& mVts;

    juce::Slider mWidthSlider;
    std::unique_ptr<SliderAttachment> mWidthAttachment;

    juce::Slider mSpeedSlider;
    std::unique_ptr<SliderAttachment> mSpeedAttachment;

    juce::Slider mOffsetSlider;
    std::unique_ptr<SliderAttachment> mOffsetAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
