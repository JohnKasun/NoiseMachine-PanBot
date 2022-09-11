#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_core/juce_core.h"

class NoMachLookAndFeel : public juce::LookAndFeel_V4 {
public:
	NoMachLookAndFeel();
	~NoMachLookAndFeel();
	void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;
	void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
private:
};