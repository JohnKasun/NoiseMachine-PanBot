#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "PanBotLookAndFeel.h"
#include "PanBotEngine.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component, juce::Timer
{
public:
    enum {
        knobWidth = 200,
        knobHeight = knobWidth,

        sliderWidth = 500,
        sliderHeight = 100
    };
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Slider slider1;
    juce::Slider slider2;
    PanBotLookAndFeel mNoMachLookAndFeel;
    PanVisualizer mPanVis;
    PanBotEngine mPanBotEngine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
