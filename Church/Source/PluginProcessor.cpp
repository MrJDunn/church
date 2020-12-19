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
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	parameters(*this, nullptr, Identifier("ChurchReverbState"),
		{
				std::make_unique<AudioParameterFloat>(stateVariable.roomSize,	  "Room Size", 0.0, 1.0, 0.5f),
				std::make_unique<AudioParameterFloat>(stateVariable.damping,	    "Damping", 0.0, 1.0, 0.5f),
				std::make_unique<AudioParameterFloat>(stateVariable.wetLevel,	  "Wet Level", 0.0, 1.0, 0.33f),
				std::make_unique<AudioParameterFloat>(stateVariable.dryLevel,	  "Dry Level", 0.0, 1.0, 0.4f),
				std::make_unique<AudioParameterFloat>(stateVariable.width,			  "Width", 0.0, 1.0, 1.0f),
				std::make_unique<AudioParameterFloat>(stateVariable.freezeMode, "Freeze Mode", 0.0, 1.0, 0.0f)
		})
#endif
{
	roomSizeParameter	= parameters.getRawParameterValue(stateVariable.roomSize);
	dampingParameter	= parameters.getRawParameterValue(stateVariable.damping);
	wetLevelParameter	= parameters.getRawParameterValue(stateVariable.wetLevel);
	dryLevelParameter	= parameters.getRawParameterValue(stateVariable.dryLevel);
	widthParameter		= parameters.getRawParameterValue(stateVariable.width);
	freezeModeParameter = parameters.getRawParameterValue(stateVariable.freezeMode);
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

void ChurchAudioProcessor::setCurrentProgram(int index)
{
}

const String ChurchAudioProcessor::getProgramName(int index)
{
	return {};
}

void ChurchAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void ChurchAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	reverb.reset();
	reverb.setSampleRate(sampleRate);

	reverb.setParameters(
		{
			*roomSizeParameter,
			*dampingParameter,
			*wetLevelParameter,
			*dryLevelParameter,
			*widthParameter,
			*freezeModeParameter
		}
	);
}

void ChurchAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChurchAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void ChurchAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
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
	return new ChurchAudioProcessorEditor(*this);
}

//==============================================================================
void ChurchAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	auto savedState = parameters.copyState();
	std::unique_ptr<juce::XmlElement> xml(savedState.createXml());
	copyXmlToBinary(*xml, destData);
}

void ChurchAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

float ChurchAudioProcessor::getParameter(const String& param)
{
	return *parameters.getRawParameterValue(param);
}

void ChurchAudioProcessor::setParameter(const String& param, float val)
{
	auto state = reverb.getParameters();

	if (param == stateVariable.damping)
	{
		state.damping = val;
	}
	else if (param == stateVariable.dryLevel)
	{
		state.dryLevel = val;
	}
	else if (param == stateVariable.freezeMode)
	{
		state.freezeMode = val;
	}
	else if (param == stateVariable.roomSize)
	{
		state.roomSize = val;
	}
	else if (param == stateVariable.wetLevel)
	{
		state.wetLevel = val;
	}
	else if (param == stateVariable.width)
	{
		state.width = val;
	}
	else
	{
		jassertfalse;
		throw "Parameter" + param + "doesn't exist";
	}

	parameters.getParameterAsValue(param).setValue(val);
	reverb.setParameters(state);
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
