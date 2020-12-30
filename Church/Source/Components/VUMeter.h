/*
  ==============================================================================

    VUMeter.h
    Created: 22 Dec 2020 4:28:44pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"

class VUMeter : public AnimatedAppComponent
{
public: 
	VUMeter(ChurchAudioProcessor&);
	~VUMeter();

	void update() override;

	void resized() override;
	void paint(Graphics& g);
	
private:	
	//============================================================================
	ChurchAudioProcessor& processor;

	Colour lightShadow = Colour::fromRGBA(255, 255, 255, 90);
	Colour darkShadow = Colour::fromRGBA(159, 167, 180, 90);
	DropShadow blackShadow;
	DropShadow whiteShadow;

	float needleValue = 0.0f;

	const float xOffset = 5.0f;
	const float yOffset = 10.0f;

	const float bevelDepthX = 15.0f;
	const float bevelDepthY = 10.0f;

	//============================================================================
	void drawBorder(Graphics& g);
	void drawBackground(Graphics& g);
	void drawWindows(Graphics& g);
	void drawDial(Graphics& g);
	void drawNeedle(Graphics& g);
};
