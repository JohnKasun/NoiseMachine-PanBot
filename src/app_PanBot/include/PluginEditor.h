#pragma once

#include "PluginProcessor.h"
#include "PanBotLookAndFeel.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Timer
{
public:

    enum {
        knobWidth = 200,
        sliderHeight = 75,
        panVisHeight = 25
    };
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:
    AudioPluginAudioProcessor& processorRef;
    juce::AudioProcessorValueTreeState& mVts;
    PanBotLookAndFeel mPanBotLookAndFeel;

    juce::Slider mWidthSlider;
    std::unique_ptr<SliderAttachment> mWidthAttachment;

    juce::Slider mSpeedSlider;
    std::unique_ptr<SliderAttachment> mSpeedAttachment;

    juce::Slider mOffsetSlider;
    std::unique_ptr<SliderAttachment> mOffsetAttachment;

    PanVisualizer mPanVis;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
