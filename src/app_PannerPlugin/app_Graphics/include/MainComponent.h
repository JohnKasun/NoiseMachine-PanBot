#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "PanBotLookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component
{
public:
    enum {
        knobWidth = 200,
        knobHeight = knobWidth,

        sliderWidth = 50,
        sliderHeight = 200
    };
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Slider slider1;
    juce::Slider slider2;
    PanBotLookAndFeel mNoMachLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
