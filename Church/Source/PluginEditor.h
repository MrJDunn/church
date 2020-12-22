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

	Slider sRoomSize;

	ToggleButton tRoomSizeSmall{"S"};
	ToggleButton tRoomSizeMedium{"M"};
	ToggleButton tRoomSizeLarge{"L"};

	Slider sDamping{"damp"};
	Slider sWetLevel{"wet"};
	Slider sDryLevel{"dry"};
	Slider sWidth{"width"};
	ToggleButton tFreezeMode{"freeze"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChurchAudioProcessorEditor)
};
