#include "PanBotLookAndFeel.h"
#include <math.h>

void PanBotLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
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

void PanBotLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
	if (style == juce::Slider::LinearHorizontal)
	{
		auto area = slider.getLocalBounds();
		auto topSliver = area.removeFromTop(area.getHeight() / 5.0f);
		auto labelArea = topSliver.removeFromLeft(topSliver.getWidth() / 8.0f);
		auto bottomSliver = area.removeFromBottom(area.getHeight() / 5.0f);
		auto valueArea = bottomSliver.removeFromRight(bottomSliver.getWidth() / 8.0f);
		auto sliderArea = area;

		g.setColour(juce::Colours::darkgrey);
		g.fillRect(labelArea);
		g.fillRect(valueArea);

		juce::Path topTriangle;
		topTriangle.addTriangle(labelArea.getTopRight().getX(), labelArea.getTopRight().getY(),
			labelArea.getTopRight().getX(), labelArea.getBottomRight().getY(),
			labelArea.getTopRight().getX() + labelArea.getWidth() / 4.0f, labelArea.getBottomRight().getY());
		g.fillPath(topTriangle);

		juce::Path bottomTriangle;
		bottomTriangle.addTriangle(valueArea.getTopLeft().getX(), valueArea.getTopLeft().getY(),
			valueArea.getTopLeft().getX(), valueArea.getBottomLeft().getY(),
			valueArea.getTopLeft().getX() - valueArea.getWidth() / 4.0f, valueArea.getTopLeft().getY());
		g.fillPath(bottomTriangle);

		g.setColour(juce::Colours::white);
		g.drawFittedText(slider.getName(), labelArea, juce::Justification::centred, 1);
		g.drawFittedText(juce::String(slider.getValue()), valueArea, juce::Justification::centred, 1);

		g.setColour(juce::Colours::grey);
		g.fillRect(sliderArea);

		juce::Rectangle<float> bookend(sliderArea.getX(), sliderArea.getY(), x, sliderArea.getHeight());
		g.setColour(juce::Colours::darkgrey);
		g.fillRect(bookend);
		g.fillRect(bookend.translated(x + width, 0));

		juce::Rectangle<float> thumbSlider(0, 0, 10, sliderArea.getHeight());
		thumbSlider.setCentre(sliderPos, sliderArea.getY() + sliderArea.getHeight() * 0.5f);
		g.setColour(juce::Colours::black);
		g.fillRect(thumbSlider);

		g.setColour(juce::Colours::darkgrey);
		g.drawRect(sliderArea);
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

void PanVisualizer::setPanPosition(float leftPan, float rightPan)
{
	mPanPosition = (rightPan - leftPan + 100.0f) / 200.0f;
}

void PanVisualizer::paint(juce::Graphics& g)
{
	auto area = getLocalBounds();
	g.setColour(juce::Colours::grey);
	g.fillRect(area);
	const auto speakerRectWidth = area.getWidth() / 8.0f;
	auto leftSpeakerRect = area.removeFromLeft(speakerRectWidth);
	auto rightSpeakerRect = area.removeFromRight(speakerRectWidth);
	g.setColour(juce::Colours::darkgrey);
	g.fillRect(leftSpeakerRect);
	g.fillRect(rightSpeakerRect);
	g.setColour(juce::Colours::white);
	g.drawFittedText("L", leftSpeakerRect, juce::Justification::centred, 1);
	g.drawFittedText("R", rightSpeakerRect, juce::Justification::centred, 1);

	juce::Line<float> bottomMiddleTick(getWidth() * 0.5f, getHeight(), getWidth() * 0.5f, getHeight() * 0.75f);
	juce::Line<float> topMiddleTick(getWidth() * 0.5f, 0, getWidth() * 0.5f, getHeight() * 0.25f);
	g.setColour(juce::Colours::white);
	g.drawLine(bottomMiddleTick, 1.0f);
	g.drawLine(topMiddleTick, 1.0f);

	juce::Rectangle<float> mPanRect(0, 0, 10, 10);
	auto panPosition = mPanPosition;
	mPanRect.setCentre(leftSpeakerRect.getCentreX() + (rightSpeakerRect.getCentreX() - leftSpeakerRect.getCentreX()) * panPosition, getHeight() / 2.0f);

	if (!mPrevRects.empty()) {
		int reduction = mPrevRects.size();
		for (auto rect : mPrevRects) {
			g.setColour(juce::Colours::darkgrey);
			g.fillEllipse(rect.reduced(reduction));
			reduction--;
		}
	}
	g.setColour(juce::Colours::black);
	g.fillEllipse(mPanRect);

	mPrevRects.push_back(mPanRect);
	if (mPrevRects.size() > 5)
		mPrevRects.pop_front();

	g.setColour(juce::Colours::black);
	g.drawRect(getLocalBounds());
}

