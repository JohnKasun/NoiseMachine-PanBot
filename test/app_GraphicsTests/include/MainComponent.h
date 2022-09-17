#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "PanBotLookAndFeel.h"

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
    std::array<std::pair<float, float>, 3> mPanPositions{
        std::pair{100.0f, 0.0f},
        std::pair{50.0f, 50.0f},
        std::pair{0.0f, 100.0f}
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
