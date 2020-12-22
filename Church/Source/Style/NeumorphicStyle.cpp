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
	if(shouldDrawButtonAsDown)
	{
		drawConcaveButton(g, button, backgroundColour,
			shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
	}
	else 
	{
		drawConvexButton(g, button, backgroundColour,
			shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
	}

	auto text = button.getButtonText();
	g.drawFittedText(text, button.getLocalBounds(), Justification::centred, 1);
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

void NeumorphicStyle::drawToggleButton(Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto backgroundColour = findColour(TextButton::ColourIds::buttonColourId);
	auto text = button.getButtonText();

	if(button.getToggleState())
	{
		drawConcaveButton(g, button, backgroundColour,
			shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

		auto textColour = findColour(TextButton::ColourIds::textColourOnId);

		g.setColour(textColour);
		g.drawFittedText(text, button.getLocalBounds(), Justification::centred, 1);
	}
	else 
	{
		drawConvexButton(g, button, backgroundColour,
			shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

		g.setColour(findColour(TextButton::ColourIds::textColourOffId));
		g.drawFittedText(text, button.getLocalBounds(), Justification::centred, 1);
	}


}

void NeumorphicStyle::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
	auto fill = slider.findColour(Slider::rotarySliderFillColourId);

	auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto lineW = jmin(8.0f, radius * 0.5f);
	auto arcRadius = radius - lineW * 0.5f;

	Path backgroundArc;
	backgroundArc.addCentredArc(bounds.getCentreX(),
		bounds.getCentreY(),
		arcRadius,
		arcRadius,
		0.0f,
		rotaryStartAngle,
		rotaryEndAngle,
		true);

	blackShadow.drawForPath(g, backgroundArc);
	whiteShadow.drawForPath(g, backgroundArc);

	g.setColour(outline);
	g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

	if (slider.isEnabled())
	{
		Path valueArc;
		valueArc.addCentredArc(bounds.getCentreX(),
			bounds.getCentreY(),
			arcRadius,
			arcRadius,
			0.0f,
			rotaryStartAngle,
			toAngle,
			true);

		g.setColour(fill);
		g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
	}

	auto text = String(slider.getValue());

	g.setColour(findColour(TextButton::ColourIds::textColourOffId));
	g.drawFittedText(text, slider.getLocalBounds(), Justification::centred, 1);
}

//=====================================================================================
// PRIVATE
void NeumorphicStyle::drawConcaveButton(Graphics & g, Button & button, const Colour & backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
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
		path.addRoundedRectangle(bounds.getX() + 4, bounds.getY() + 4,
			bounds.getWidth() - 4, bounds.getHeight() - 4,
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
		float shadowDepth = 1.5f;
		int w = button.getWidth();
		int h = button.getHeight();

		// N
		g.setGradientFill(ColourGradient(colours.darkShadow, 0, 0,
			colours.invisible, w, shadowDepth, false));
		g.fillRoundedRectangle(bounds, cornerSize);

		// W
		g.setGradientFill(ColourGradient(colours.lightShadow, w, h,
			colours.invisible, w - shadowDepth, 0, false));
		g.fillRoundedRectangle(bounds, cornerSize);

		// S
		g.setGradientFill(ColourGradient(colours.lightShadow, w, h,
			colours.invisible, 0, h - shadowDepth, false));
		g.fillRoundedRectangle(bounds, cornerSize);

		// E
		g.setGradientFill(ColourGradient(colours.darkShadow, 0, 0,
			colours.invisible, shadowDepth, h, false));
		g.fillRoundedRectangle(bounds, cornerSize);

		// C
		Path path;
		path.addRoundedRectangle(bounds.getX() + shadowDepth * 2, bounds.getY() + shadowDepth * 2,
			bounds.getWidth() - shadowDepth * 2, bounds.getHeight() - shadowDepth * 2,
			cornerSize, cornerSize,
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight(),
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight());

		DropShadow centerShadow(baseColour.darker(0.01), 5, juce::Point<int>(0, 0));
		centerShadow.drawForPath(g, path);
	}
}

void NeumorphicStyle::drawConvexButton(Graphics & g, Button & button, const Colour & backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
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
