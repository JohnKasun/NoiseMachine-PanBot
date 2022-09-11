#include "MyLookAndFeel.h"
#include <math.h>

MyLookAndFeel::MyLookAndFeel()
{
}

MyLookAndFeel::~MyLookAndFeel()
{
}

void MyLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
	float radius = juce::jmin(width / 2.0f, height / 2.0f) - 25.0f;
	float centerX = x + width * 0.5f;
	float centerY = y + height * 0.5f;
	float rx = centerX - radius;
	float ry = centerY - radius;
	float rw = radius * 2.0f;
	juce::Rectangle<float> outlineArea(rx, ry, rw, rw);

	juce::Path basePath;
	basePath.addTriangle(outlineArea.getCentre(), outlineArea.getBottomLeft(), outlineArea.getBottomRight());
	g.setColour(juce::Colours::black);
	g.fillPath(basePath);

	g.setColour(juce::Colours::black);
	g.fillEllipse(outlineArea);

	juce::Path outlinePath;
	outlinePath.addArc(outlineArea.getX(), outlineArea.getY(), outlineArea.getWidth(), outlineArea.getWidth(), rotaryStartAngle, rotaryEndAngle, true);
	juce::PathStrokeType strokeType(1.0f);
	g.setColour(juce::Colours::white);
	g.strokePath(outlinePath, strokeType);

	const float tickLength = 10.0f;
	const float tickThickness = 1.0f;
	const int numTicks = 5;
	float distance = 0.0f;
	float rotation = 0.0f;
	for (auto tick = 0; tick < numTicks; tick++) {
		juce::Path currentTick;
		currentTick.addRectangle(0, 0, tickLength, tickThickness);
		currentTick.applyTransform(juce::AffineTransform::rotation(rotaryStartAngle + rotation + juce::MathConstants<float>::pi / 2.0f).translated(outlinePath.getPointAlongPath(distance)));
		g.setColour(juce::Colours::white);
		g.fillPath(currentTick);
		rotation += (rotaryEndAngle - rotaryStartAngle) / (numTicks - 1);
		distance += outlinePath.getLength() / (numTicks - 1);
	}

	juce::Rectangle<float> sliderArea(outlineArea.reduced(15));
	float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	g.setColour(juce::Colours::grey);
	g.fillEllipse(sliderArea);
	g.setColour(juce::Colours::white);
	g.drawEllipse(sliderArea, 1.0f);

	juce::Path path;
	float pointerLength = sliderArea.getWidth() / 2.0f * 0.33f;
	float pointerThickness = 5.0f;
	path.addRectangle(-pointerThickness * 0.5f, -sliderArea.getWidth() / 2.0f, pointerThickness, pointerLength);
	path.applyTransform(juce::AffineTransform::rotation(angle).translated(centerX, centerY));
	g.setColour(juce::Colours::black);
	g.fillPath(path);
	g.setColour(juce::Colours::white);

	g.setColour(juce::Colours::whitesmoke);
	g.setFont(juce::Font::fromString("Times New Roman"));
	g.setFont(15);
	g.drawText(slider.getName(), sliderArea, juce::Justification::centred);
}

void MyLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
	if (style == juce::Slider::LinearVertical)
	{
		juce::Rectangle<float> baseArea(x, y + height - width, width, width);

		juce::Path base;
		base.addCentredArc(baseArea.getCentreX(), baseArea.getCentreY(), baseArea.getWidth() / 2, baseArea.getHeight() / 2, 0, juce::MathConstants<float>::pi / 6.0f, 11.0f * juce::MathConstants<float>::pi / 6.0f, true);
		juce::Point<float> arcStart(base.getPointAlongPath(0));
		juce::Point<float> arcEnd(base.getCurrentPosition());
		g.setColour(juce::Colours::white);
		g.strokePath(base, juce::PathStrokeType(1.0f));
		base.closeSubPath();
		g.setColour(juce::Colours::green);
		g.fillPath(base);

		juce::Rectangle<float> neck(arcEnd.getX(), y, arcStart.getX() - arcEnd.getX(), height - baseArea.getHeight() + 3);
		const float sliderPosScaled = (sliderPos - y) / (maxSliderPos - y) * neck.getHeight();
		g.setColour(juce::Colours::green);
		g.fillRect(neck.withTrimmedTop(sliderPosScaled));

		g.setColour(juce::Colours::white);
		g.drawLine(juce::Line<float>(neck.getBottomLeft(), neck.getTopLeft()));
		g.drawLine(juce::Line<float>(neck.getTopLeft(), neck.getTopRight()));
		g.drawLine(juce::Line<float>(neck.getTopRight(), neck.getBottomRight()));

		g.drawText(slider.getName(), baseArea, juce::Justification::centred);
	}
	else
	{
		drawLinearSliderBackground(g, x, y, width,
			height, sliderPos, minSliderPos,
			maxSliderPos, style, slider);
		drawLinearSliderThumb(g, x, y, width,
			height, sliderPos, minSliderPos,
			maxSliderPos, style, slider);
	}
}

