/*
  ==============================================================================

	NeumorphicStyle.cpp
	Created: 18 Dec 2020 9:59:45am
	Author:  Jeff

  ==============================================================================
*/

#include "NeumorphicStyle.h"

NeumorphicStyle::NeumorphicStyle() :
	colourScheme(
		{
			colours.primary		/*windowBackground*/,
			colours.primary		/*widgetBackground*/,
			colours.primary		/*menuBackground*/,
			colours.invisible	/*outline*/,
			colours.textColour	/*defaultText*/,
			colours.primaryDark /*defaultFill*/,
			colours.textColour	/*highlightedText*/,
			colours.primaryLight/*highlightedFill*/,
			colours.textColour	/*menuText*/
		}
	),
	blackShadow(colours.darkShadow, 5, juce::Point<int>(4, 4)),
	whiteShadow(colours.lightShadow, 5, juce::Point<int>(-4, -4))
{
	setColourScheme(colourScheme);
}

NeumorphicStyle::~NeumorphicStyle()
{
}

void NeumorphicStyle::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
	bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto cornerSize = 10.0f;
	auto bounds = button.getLocalBounds().toFloat().reduced(5.f, 5.f);

	auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
		.withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

	if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
		baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

	g.setColour(baseColour);

	if (button.isConnectedOnLeft() || button.isConnectedOnRight())
	{
		Path path;
		path.addRoundedRectangle(bounds.getX(), bounds.getY(),
			bounds.getWidth(), bounds.getHeight(),
			cornerSize, cornerSize,
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight(),
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight());

		g.fillPath(path);

		g.setColour(button.findColour(ComboBox::outlineColourId).darker());
		g.strokePath(path, PathStrokeType(1.0f));
	}
	else
	{
		Path path;
		path.addRoundedRectangle(bounds.getX(), bounds.getY(),
			bounds.getWidth(), bounds.getHeight(),
			cornerSize * 2, cornerSize * 2,
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight(),
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight());

		blackShadow.drawForPath(g, path);
		whiteShadow.drawForPath(g, path);

		g.setColour(baseColour.darker(0.01));

		g.fillRoundedRectangle(bounds, cornerSize);
	}
}

void NeumorphicStyle::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
	float sliderPos,
	float minSliderPos,
	float maxSliderPos,
	const Slider::SliderStyle style, Slider& slider)
{
	if (slider.isBar())
	{
		g.setColour(slider.findColour(Slider::trackColourId));
		g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
			: Rectangle<float>(x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
	}
	else
	{
		int cornersize = 10;
		auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
		auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

		// Draw soft shadows
		auto bounds = slider.getLocalBounds().toFloat().reduced(5.f, 5.f);
		Path path;
		path.addRoundedRectangle(bounds.getX(), bounds.getY(),
			bounds.getWidth(), bounds.getHeight(),
			cornersize * 2, cornersize * 2,true,true,true,true);

		blackShadow.drawForPath(g, path);
		whiteShadow.drawForPath(g, path);

		// Draw background
		g.setColour(slider.findColour(Slider::backgroundColourId));
		g.fillRoundedRectangle(bounds, cornersize);

		// Draw track
		auto trackWidth = jmin(6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

		Rectangle<float> track = bounds;
		track.setWidth(sliderPos + 2);

		g.setColour(slider.findColour(Slider::trackColourId));
		g.fillRoundedRectangle(track, cornersize);
	}
}