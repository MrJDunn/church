/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChurchAudioProcessorEditor::ChurchAudioProcessorEditor (ChurchAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	setLookAndFeel(&style);
	LookAndFeel::setDefaultLookAndFeel(&style);

	//--------------------------------------------------------------------------
	addAndMakeVisible(&bTest);

	addAndMakeVisible(&sTest);
	sTest.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sTest.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));// 149, 159, 173));

	addAndMakeVisible(&tTest);

	//--------------------------------------------------------------------------
	addAndMakeVisible(tRoomSizeSmall);
	addAndMakeVisible(tRoomSizeMedium);
	addAndMakeVisible(tRoomSizeLarge);

	tRoomSizeSmall.onClick = [this]
	{ 
		tRoomSizeSmall.setToggleState(true, dontSendNotification);
		tRoomSizeMedium.setToggleState(false, dontSendNotification);
		tRoomSizeLarge.setToggleState(false, dontSendNotification);
		processor.setParameter(processor.stateVariable.roomSize, 0.1); 
	};
	tRoomSizeMedium.onClick = [this]
	{
		tRoomSizeSmall.setToggleState(false, dontSendNotification);
		tRoomSizeMedium.setToggleState(true, dontSendNotification);
		tRoomSizeLarge.setToggleState(false, dontSendNotification);
		processor.setParameter(processor.stateVariable.roomSize, 0.5);
	};
	tRoomSizeLarge.onClick = [this]
	{
		tRoomSizeSmall.setToggleState(false, dontSendNotification);
		tRoomSizeMedium.setToggleState(false, dontSendNotification);
		tRoomSizeLarge.setToggleState(true, dontSendNotification);
		processor.setParameter(processor.stateVariable.roomSize, 0.9);
	};

	float roomSizeValue = processor.getParameter(processor.stateVariable.roomSize);
	if(roomSizeValue < 0.5)
	{
		tRoomSizeSmall.setToggleState(true, dontSendNotification);
		tRoomSizeMedium.setToggleState(false, dontSendNotification);
		tRoomSizeLarge.setToggleState(false, dontSendNotification);
	}
	else if(roomSizeValue >= 0.5 && roomSizeValue < 0.9)
	{
		tRoomSizeSmall.setToggleState(false, dontSendNotification);
		tRoomSizeMedium.setToggleState(true, dontSendNotification);
		tRoomSizeLarge.setToggleState(false, dontSendNotification);
	}
	else 
	{
		tRoomSizeSmall.setToggleState(false, dontSendNotification);
		tRoomSizeMedium.setToggleState(false, dontSendNotification);
		tRoomSizeLarge.setToggleState(true, dontSendNotification);
	}

	//--------------------------------------------------------------------------
	addAndMakeVisible(sDamping);
	addAndMakeVisible(sWetLevel);
	addAndMakeVisible(sDryLevel);
	addAndMakeVisible(sWidth);
	addAndMakeVisible(tFreezeMode);

	sDamping.setRange(0.0, 1.0, 0.0001);
	sWetLevel.setRange(0.0, 1.0, 0.0001);
	sDryLevel.setRange(0.0, 1.0, 0.0001);
	sWidth.setRange(0.0, 1.0, 0.0001);

	sDamping.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sWetLevel.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sDryLevel.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sWidth.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	sDamping.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sWetLevel.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sDryLevel.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sWidth.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));

	sDamping.onValueChange    = [this] { processor.setParameter(processor.stateVariable.damping, sDamping.getValue()); };
	sWetLevel.onValueChange   = [this] { processor.setParameter(processor.stateVariable.wetLevel, sWetLevel.getValue()); };
	sDryLevel.onValueChange   = [this] { processor.setParameter(processor.stateVariable.dryLevel, sDryLevel.getValue()); };
	sWidth.onValueChange	  = [this] { processor.setParameter(processor.stateVariable.width, sWidth.getValue()); };
	tFreezeMode.onClick		  = [this] { processor.setParameter(processor.stateVariable.freezeMode, tFreezeMode.getToggleState()); };

	sDamping.setValue(processor.getParameter(processor.stateVariable.damping), dontSendNotification);
	sWetLevel.setValue(processor.getParameter(processor.stateVariable.wetLevel), dontSendNotification);
	sDryLevel.setValue(processor.getParameter(processor.stateVariable.dryLevel), dontSendNotification);
	sWidth.setValue(processor.getParameter(processor.stateVariable.width), dontSendNotification);
	tFreezeMode.setToggleState(processor.getParameter(processor.stateVariable.freezeMode), dontSendNotification);
}

ChurchAudioProcessorEditor::~ChurchAudioProcessorEditor()
{
	setLookAndFeel(nullptr);
}

//==============================================================================
void ChurchAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ChurchAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	auto area = getLocalBounds();
	auto column = area.removeFromLeft(getWidth()/2);

	//bTest.setBounds(column.removeFromTop(100).reduced(10));
	//sTest.setBounds(column.removeFromTop(100).reduced(10));
	//tTest.setBounds(column.removeFromTop(100).reduced(10));
	int h = 50;

	auto rowRoomSize = column.removeFromTop(h);

	tRoomSizeSmall.setBounds(rowRoomSize.removeFromLeft(rowRoomSize.getWidth() / 3.f).reduced(2));
	tRoomSizeMedium.setBounds(rowRoomSize.removeFromLeft(rowRoomSize.getWidth() / 2.f).reduced(2));
	tRoomSizeLarge.setBounds(rowRoomSize.removeFromLeft(rowRoomSize.getWidth()).reduced(2));

	sDamping.setBounds(column.removeFromTop(h).reduced(10));
	sWetLevel.setBounds(column.removeFromTop(h).reduced(10));
	sDryLevel.setBounds(column.removeFromTop(h).reduced(10));
	sWidth.setBounds(column.removeFromTop(h).reduced(10));
	tFreezeMode.setBounds(column.removeFromTop(h).reduced(10));
}
