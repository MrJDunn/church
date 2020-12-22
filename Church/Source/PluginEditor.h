/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "Style/NeumorphicStyle.h"

//==============================================================================
/**
*/
class ChurchAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ChurchAudioProcessorEditor (ChurchAudioProcessor&);
    ~ChurchAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChurchAudioProcessor& processor;

	NeumorphicStyle style;

	TextButton bTest;
	ToggleButton tTest;
	Slider sTest;

	Slider sRoomSize;

	ToggleButton tRoomSizeSmall;
	ToggleButton tRoomSizeMedium;
	ToggleButton tRoomSizeLarge;

	Slider sDamping;
	Slider sWetLevel;
	Slider sDryLevel;
	Slider sWidth;
	ToggleButton tFreezeMode{"FreezeMode"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChurchAudioProcessorEditor)
};
