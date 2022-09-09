#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), mVts(vts)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible(mWidthSlider);
    mWidthAttachment.reset(new SliderAttachment(mVts, "width", mWidthSlider));
    mWidthSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mWidthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, labelWidth, sliderHeight);

    addAndMakeVisible(mSpeedSlider);
    mSpeedAttachment.reset(new SliderAttachment(mVts, "speed", mSpeedSlider));
    mSpeedSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mSpeedSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, labelWidth, sliderHeight);

    addAndMakeVisible(mOffsetSlider);
    mOffsetAttachment.reset(new SliderAttachment(mVts, "offset", mOffsetSlider));
    mOffsetSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mOffsetSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, labelWidth, sliderHeight);

    setSize (sliderWidth + labelWidth, 3 * sliderHeight);
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
    mWidthSlider.setBounds(area.removeFromTop(sliderHeight));
    mSpeedSlider.setBounds(area.removeFromTop(sliderHeight));
    mOffsetSlider.setBounds(area.removeFromTop(sliderHeight));
}
