#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), mVts(vts)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible(mWidthSlider);
    mWidthAttachment.reset(new SliderAttachment(mVts, "width", mWidthSlider));
    mWidthSlider.setSliderStyle(juce::Slider::Rotary);
    mWidthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mWidthSlider.setName("Width");
    mWidthSlider.setLookAndFeel(&mMyLookAndFeel);

    addAndMakeVisible(mSpeedSlider);
    mSpeedAttachment.reset(new SliderAttachment(mVts, "speed", mSpeedSlider));
    mSpeedSlider.setSliderStyle(juce::Slider::Rotary);
    mSpeedSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mSpeedSlider.setName("Speed");
    mSpeedSlider.setLookAndFeel(&mMyLookAndFeel);

    addAndMakeVisible(mOffsetSlider);
    mOffsetAttachment.reset(new SliderAttachment(mVts, "offset", mOffsetSlider));
    mOffsetSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mOffsetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    setSize (knobWidth * 2, knobWidth + sliderHeight);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto knobArea = area.removeFromTop(knobWidth);
    mWidthSlider.setBounds(knobArea.removeFromLeft(knobWidth));
    mSpeedSlider.setBounds(knobArea);
    mOffsetSlider.setBounds(area);
}
