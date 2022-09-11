#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(slider1);
    slider1.setSliderStyle(juce::Slider::Rotary);
    slider1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider1.setName("Mix");

    addAndMakeVisible(slider2);
    slider2.setSliderStyle(juce::Slider::LinearVertical);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider2.setName("Gain");

    setLookAndFeel(&mNoMachLookAndFeel);
    setSize(sliderWidth + knobWidth, juce::jmax(sliderHeight, knobHeight));
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    slider1.setBounds(area.removeFromRight(knobWidth));
    slider2.setBounds(area);
}
