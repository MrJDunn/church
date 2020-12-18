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
	sTest.setColour(Slider::trackColourId, Colour::fromRGB(149, 159, 173));

}

ChurchAudioProcessorEditor::~ChurchAudioProcessorEditor()
{
	setLookAndFeel(nullptr);
}

//==============================================================================
void ChurchAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void ChurchAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	auto area = getLocalBounds();

	bTest.setBounds(area.removeFromTop(50).reduced(10));
	sTest.setBounds(area.removeFromTop(50).reduced(10));

}
