/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChurchAudioProcessor::ChurchAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ChurchAudioProcessor::~ChurchAudioProcessor()
{
}

//==============================================================================
const String ChurchAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChurchAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChurchAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChurchAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChurchAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChurchAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChurchAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChurchAudioProcessor::setCurrentProgram (int index)
{
}

const String ChurchAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChurchAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChurchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	reverb.reset();
	reverb.setSampleRate(sampleRate);
}

void ChurchAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChurchAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChurchAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
    }

	reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), getBlockSize());

}

//==============================================================================
bool ChurchAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChurchAudioProcessor::createEditor()
{
    return new ChurchAudioProcessorEditor (*this);
}

//==============================================================================
void ChurchAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChurchAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void ChurchAudioProcessor::setRoomSize(float newVal)
{
	auto state = reverb.getParameters();
	state.roomSize = newVal;
	reverb.setParameters(state);
}

float ChurchAudioProcessor::getRoomSize()
{
	return reverb.getParameters().roomSize;
}

void ChurchAudioProcessor::setDamping(float newVal)
{
	auto state = reverb.getParameters();
	state.damping = newVal;
	reverb.setParameters(state);
}

float ChurchAudioProcessor::getDamping()
{
	return reverb.getParameters().damping;
}

void ChurchAudioProcessor::setWetLevel(float newVal)
{
	auto state = reverb.getParameters();
	state.wetLevel = newVal;
	reverb.setParameters(state);
}

float ChurchAudioProcessor::getWetLevel()
{
	return reverb.getParameters().wetLevel;
}

void ChurchAudioProcessor::setDryLevel(float newVal)
{
	auto state = reverb.getParameters();
	state.dryLevel = newVal;
	reverb.setParameters(state);
}

float ChurchAudioProcessor::getDryLevel()
{
	return reverb.getParameters().dryLevel;
}

void ChurchAudioProcessor::setWidth(float newVal)
{
	auto state = reverb.getParameters();
	state.width = newVal;
	reverb.setParameters(state);
}

float ChurchAudioProcessor::getWidth()
{
	return reverb.getParameters().width;
}

void ChurchAudioProcessor::setFreezeMode(float newVal)
{
	auto state = reverb.getParameters();
	state.freezeMode = newVal;
	reverb.setParameters(state);
}

float ChurchAudioProcessor::getFreezeMode()
{
	return reverb.getParameters().freezeMode;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChurchAudioProcessor();
}
