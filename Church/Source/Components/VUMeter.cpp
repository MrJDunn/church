/*
  ==============================================================================

    VUMeter.cpp
    Created: 22 Dec 2020 4:28:44pm
    Author:  Jeff

  ==============================================================================
*/

#include "VUMeter.h"

VUMeter::VUMeter(ChurchAudioProcessor& p): 
	processor(p),
	blackShadow( darkShadow, 6, juce::Point<int>( 6,  6)),
	whiteShadow(lightShadow, 6, juce::Point<int>(-6, -6))
{
	setOpaque(false);
	setFramesPerSecond(10);
}

VUMeter::~VUMeter()
{
}

void VUMeter::update()
{
	needleValue = processor.getGain();
	repaint();
}

void VUMeter::resized()
{
	repaint();
}

void VUMeter::paint(Graphics& g)
{
	drawBackground(g);
	drawDial(g);
	drawNeedle(g);
}

void VUMeter::drawBorder(Graphics& g)
{
	Path circularPath;
	circularPath.addEllipse(0, 0, getWidth(), getHeight());

	auto outline = findColour(Slider::rotarySliderOutlineColourId);

	blackShadow.drawForPath(g, circularPath);
	whiteShadow.drawForPath(g, circularPath);

	g.setColour(outline);
	g.fillPath(circularPath);
}

void VUMeter::drawBackground(Graphics & g)
{
	auto fill = getLookAndFeel().findColour(Slider::backgroundColourId);
	auto bounds = getLocalBounds().reduced(2);
	auto radius = jmin(bounds.getWidth(), bounds.getHeight());	
	int x = getLocalBounds().getWidth() / 2.f - radius / 2.f;
	int y = 2;

	Rectangle<int> shadowArea(x, y, radius, radius);

	Path backGround;
	backGround.addEllipse(shadowArea.getX(), shadowArea.getY(),
		shadowArea.getWidth(), shadowArea.getHeight());

    //blackShadow.drawForPath(g, backGround);
    //whiteShadow.drawForPath(g, backGround);

	g.setGradientFill(ColourGradient(fill, shadowArea.getCentre().getX(), shadowArea.getCentre().getY(),
		Colours::transparentWhite, shadowArea.getCentre().getX() + radius / 2.f, shadowArea.getCentre().getY() + radius / 2.f, true));

	g.fillPath(backGround);

	g.setGradientFill(ColourGradient(
		Colour::fromRGB(darkShadow.getRed(), darkShadow.getGreen(), darkShadow.getBlue()), x, y,
		Colour::fromRGB(lightShadow.getRed(), lightShadow.getGreen(), lightShadow.getBlue()), x + radius - 1, y + radius - 1, false));
	g.drawEllipse(x, y, radius, radius, 1.f);

}

void VUMeter::drawWindows(Graphics& g)
{
	const float width = (float)getWidth();
	const float height = (float)getHeight();

	Point<float> nwi(0.0f + bevelDepthX + xOffset, 0.0f + bevelDepthY + yOffset);
	Point<float> sei(width - bevelDepthX - xOffset, height - bevelDepthY - yOffset);

	juce::Rectangle<float> centerRectangle(nwi, sei);

	Image glass(Image::ARGB, 736, 409, true);
	Graphics glassG(glass);

	File glassFile = File("C:\\Users\\Jeff\\Pictures\\Textures\\Glass.png");
	Image glassTile = ImageCache::getFromFile(glassFile);

	glassG.setTiledImageFill(glassTile, centerRectangle.getX(), centerRectangle.getY(), 0.5f);
	glassG.fillAll();

	g.drawImage(glass, centerRectangle, false);
}

void VUMeter::drawDial(Graphics& g)
{
	auto fill = getLookAndFeel().findColour(Slider::backgroundColourId);
	auto bounds = getLocalBounds().reduced(12);
	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 1.3f;
	int x = getLocalBounds().getWidth() / 2.f - radius / 2.f;
	int y = getHeight() /2.f - radius / 2.f;

	Rectangle<int> shadowArea(x, y, radius, radius);

	Path backGround;
	backGround.addEllipse(shadowArea.getX(), shadowArea.getY(),
		shadowArea.getWidth(), shadowArea.getHeight());

	blackShadow.drawForPath(g, backGround);
	whiteShadow.drawForPath(g, backGround);

	// Fill center of dial
	g.setColour(Colour::fromRGB(219, 227, 188));
	g.fillEllipse(x, y, radius, radius);

	// Shadow in center of dial
	g.setGradientFill(ColourGradient(darkShadow.darker(0.5f), x, y,
		lightShadow.brighter(0.5f), x + radius, y + radius, false));
	g.fillEllipse(x, y, radius, radius);

	// Center rim
	g.setGradientFill(ColourGradient(
		Colour::fromRGB(darkShadow.getRed(), darkShadow.getGreen(), darkShadow.getBlue()), x, y,
		Colour::fromRGB(lightShadow.getRed(), lightShadow.getGreen(), lightShadow.getBlue()), x + radius, y + radius, false));
	g.drawEllipse(x, y, radius, radius,4.f);

	//g.setGradientFill(ColourGradient(darkShadow, x, y,
	//	lightShadow, x + radius, y + radius, false));


}


void VUMeter::drawNeedle(Graphics& g)
{
	auto area = getLocalBounds();

	g.setColour(getLookAndFeel().findColour(Slider::ColourIds::textBoxTextColourId));
	
	g.setFont(getLookAndFeel().getPopupMenuFont().withHeight(20.f));

	int dbValue = 20 * log10(needleValue);

	if(dbValue < -100)
	{
		dbValue = -100;
	}

    // left
    g.drawText(String(dbValue / 10), area.withX(area.getX() - 15), Justification::centred, false);

    // mid
    g.drawText(String(abs(dbValue % 10)), area, Justification::centred, false);

    // right
    g.drawText("db", area.withX(area.getX() + 20), Justification::centred, false);

}
