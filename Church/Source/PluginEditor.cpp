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
	addAndMakeVisible(sRoomSize);
	addAndMakeVisible(sDamping);
	addAndMakeVisible(sWetLEvel);
	addAndMakeVisible(sDryLEvel);
	addAndMakeVisible(sWidth);
	addAndMakeVisible(sFreezeMode);

	sRoomSize.setRange(0.0, 1.0, 0.0001);
	sDamping.setRange(0.0, 1.0, 0.0001);
	sWetLEvel.setRange(0.0, 1.0, 0.0001);
	sDryLEvel.setRange(0.0, 1.0, 0.0001);
	sWidth.setRange(0.0, 1.0, 0.0001);
	sFreezeMode.setRange(0.0, 1.0, 0.0001);

	sRoomSize.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sDamping.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sWetLEvel.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sDryLEvel.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sWidth.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sFreezeMode.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	sRoomSize.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sDamping.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sWetLEvel.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sDryLEvel.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sWidth.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));
	sFreezeMode.setColour(Slider::trackColourId, Colour::fromRGB(186, 140, 200));

	sRoomSize.onValueChange   = [this] { processor.setParameter(processor.stateVariable.roomSize, sRoomSize.getValue()); };
	sDamping.onValueChange    = [this] { processor.setParameter(processor.stateVariable.damping, sDamping.getValue()); };
	sWetLEvel.onValueChange   = [this] { processor.setParameter(processor.stateVariable.wetLevel, sWetLEvel.getValue()); };
	sDryLEvel.onValueChange   = [this] { processor.setParameter(processor.stateVariable.dryLevel, sDryLEvel.getValue()); };
	sWidth.onValueChange	  = [this] { processor.setParameter(processor.stateVariable.width, sWidth.getValue()); };
	sFreezeMode.onValueChange = [this] { processor.setParameter(processor.stateVariable.freezeMode, sFreezeMode.getValue()); };

	sRoomSize.setValue(processor.getParameter(processor.stateVariable.roomSize), dontSendNotification);
	sDamping.setValue(processor.getParameter(processor.stateVariable.damping), dontSendNotification);
	sWetLEvel.setValue(processor.getParameter(processor.stateVariable.wetLevel), dontSendNotification);
	sDryLEvel.setValue(processor.getParameter(processor.stateVariable.dryLevel), dontSendNotification);
	sWidth.setValue(processor.getParameter(processor.stateVariable.width), dontSendNotification);
	sFreezeMode.setValue(processor.getParameter(processor.stateVariable.freezeMode), dontSendNotification);
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
	int h = 40;
	sRoomSize.setBounds(column.removeFromTop(h).reduced(10));
	sDamping.setBounds(column.removeFromTop(h).reduced(10));
	sWetLEvel.setBounds(column.removeFromTop(h).reduced(10));
	sDryLEvel.setBounds(column.removeFromTop(h).reduced(10));
	sWidth.setBounds(column.removeFromTop(h).reduced(10));
	sFreezeMode.setBounds(column.removeFromTop(h).reduced(10));
}
