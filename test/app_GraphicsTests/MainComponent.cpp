#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(slider1);
    slider1.setSliderStyle(juce::Slider::Rotary);
    slider1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider1.setName("Mix");

    addAndMakeVisible(slider2);
    slider2.setSliderStyle(juce::Slider::LinearHorizontal);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider2.setName("Gain");

    addAndMakeVisible(mPanVis);

    startTimer(500);

    setLookAndFeel(&mNoMachLookAndFeel);
    setSize(juce::jmax(sliderWidth, knobWidth), sliderHeight + knobHeight + sliderHeight);
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
    stopTimer();
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    slider1.setBounds(area.removeFromTop(knobHeight));
    slider2.setBounds(area.removeFromTop(sliderHeight));
    mPanVis.setBounds(area);
}

void MainComponent::timerCallback()
{
    static int counter = 0;
    auto nextPan = mPanPositions.at(counter);
    mPanVis.setPanPosition(nextPan.first, nextPan.second);
    counter = (counter + 1) % 3;
    repaint();
}
