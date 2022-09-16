#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class PanBotLookAndFeel : public juce::LookAndFeel_V4
{
public:
	PanBotLookAndFeel() {};
	~PanBotLookAndFeel() {};
	void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;
	void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
};

//class PanVisualizer : juce::Component
//{
//public:
//	PanVisualizer();
//	~PanVisualizer();
//	void setPanPosition(float )
//	void paint(juce::Graphics& g) override;
//	void resized() override;
//};

