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
    mWidthSlider.setLookAndFeel(&mPanBotLookAndFeel);

    addAndMakeVisible(mSpeedSlider);
    mSpeedAttachment.reset(new SliderAttachment(mVts, "speed", mSpeedSlider));
    mSpeedSlider.setSliderStyle(juce::Slider::Rotary);
    mSpeedSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mSpeedSlider.setName("Speed");
    mSpeedSlider.setLookAndFeel(&mPanBotLookAndFeel);

    addAndMakeVisible(mOffsetSlider);
    mOffsetAttachment.reset(new SliderAttachment(mVts, "offset", mOffsetSlider));
    mOffsetSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mOffsetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mOffsetSlider.setLookAndFeel(&mPanBotLookAndFeel);

    setSize (knobWidth * 2, knobWidth + sliderHeight);
    startTimer(1);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::darkgrey);

}

void AudioPluginAudioProcessorEditor::paintOverChildren(juce::Graphics& g)
{
    juce::Rectangle<float> mPanRect(0, 0, 10, 10);
    auto panPosition = processorRef.getPanPosition();
    mPanRect.setCentre(mOffsetSlider.getWidth() * ((panPosition.second - panPosition.first + 1) / 2.0f), mOffsetSlider.getY() + mOffsetSlider.getHeight() / 2.0f);
    g.setColour(juce::Colours::red);
    g.fillEllipse(mPanRect);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto knobArea = area.removeFromTop(knobWidth);
    mWidthSlider.setBounds(knobArea.removeFromLeft(knobWidth));
    mSpeedSlider.setBounds(knobArea);
    mOffsetSlider.setBounds(area);
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    repaint();
}
