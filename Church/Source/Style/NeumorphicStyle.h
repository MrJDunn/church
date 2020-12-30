/*
  ==============================================================================

	NeumorphicStyle.h
	Created: 18 Dec 2020 9:15:24am
	Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class NeumorphicStyle : public LookAndFeel_V4
{
public:
	struct NeumorphicColours
	{
		Colour invisible = Colour::fromRGBA(0, 0, 0, 0);

		Colour black = Colour::fromRGB( 10,  10,  10);
		Colour white = Colour::fromRGB(245, 245, 245);

		Colour primary		= Colour::fromRGB(220, 220, 230);
		Colour primaryLight = Colour::fromRGB(255, 255, 255);
		Colour primaryDark  = Colour::fromRGB(209, 217, 230);

		Colour lightShadow = Colour::fromRGBA(255, 255, 255, 127);
		Colour darkShadow  = Colour::fromRGBA(159, 167, 180, 127);

		Colour textColour = Colour::fromRGB(105, 114, 127);
	} colours;

	NeumorphicStyle();
	~NeumorphicStyle() override;

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override;

	void drawToggleButton(Graphics& g, ToggleButton& button,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);

private:

	void drawConcaveButton(Graphics& g, Button& button, const Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
	void drawConvexButton(Graphics& g, Button& button, const Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);

	ColourScheme colourScheme;
	DropShadow blackShadow;
	DropShadow whiteShadow;
};
