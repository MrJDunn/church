/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class ChurchAudioProcessor  : public AudioProcessor
{
public:
	struct StateVariable
	{
		const String roomSize	 = "roomSize";
		const String damping	 = "damping";
		const String wetLevel	 = "wetLevel";
		const String dryLevel	 = "dryLevel";
		const String width		 = "width";
		const String freezeMode  = "freezeMode";
	} stateVariable;

    //==============================================================================
    ChurchAudioProcessor();
    ~ChurchAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	float getParameter(const String&);
	void setParameter(const String&, float);

	void setRoomSize(float);
	float getRoomSize();

	void setDamping(float);
	float getDamping();

	void setWetLevel(float);
	float getWetLevel();

	void setDryLevel(float);
	float getDryLevel ();

	void setWidth(float);
	float getWidth();

	void setFreezeMode(float);
	float getFreezeMode();

	float getGain();

private:

	AudioProcessorValueTreeState parameters;
	Reverb reverb;

	float* roomSizeParameter   = nullptr;
	float* dampingParameter	   = nullptr;
	float* wetLevelParameter   = nullptr;
	float* dryLevelParameter   = nullptr;
	float* widthParameter      = nullptr;
	float* freezeModeParameter = nullptr;

	std::atomic<float> gain;

    void clearUnusedChannels(AudioBuffer<float>&);
	void calculateGain(AudioBuffer<float>&);
    void applyReverb(AudioBuffer<float>&);
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChurchAudioProcessor)
};
