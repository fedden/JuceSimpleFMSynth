/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
IncrediblySimpleFmsynthAudioProcessor::IncrediblySimpleFmsynthAudioProcessor()
{
    addParameter(modulationIndexParamter = new AudioParameterInt("ModIndex",
                                                                 "Modulation Index",
                                                                 0,
                                                                 1500,
                                                                 0));
    addParameter(modulationFrequencyRatioParameter = new AudioParameterFloat("ModFreqRatio",
                                                                             "Modulation Frequency Ratio",
                                                                             -3.8,
                                                                             3.8,
                                                                             0));
    synth.clearVoices();
    for (int i = 0; i < maxNumVoices; ++i)
        synth.addVoice(new SimpleVoice());
    
    synth.clearSounds();
    synth.addSound(new SimpleSound());
}

//==============================================================================
const String IncrediblySimpleFmsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IncrediblySimpleFmsynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IncrediblySimpleFmsynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double IncrediblySimpleFmsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IncrediblySimpleFmsynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IncrediblySimpleFmsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IncrediblySimpleFmsynthAudioProcessor::setCurrentProgram (int index)
{
}

const String IncrediblySimpleFmsynthAudioProcessor::getProgramName (int index)
{
    return String();
}

void IncrediblySimpleFmsynthAudioProcessor::changeProgramName (int           index,
                                                               const String& newName)
{
}

//==============================================================================
void IncrediblySimpleFmsynthAudioProcessor::prepareToPlay (double sampleRate,
                                                           int    samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    synth.setCurrentPlaybackSampleRate(lastSampleRate);
    maxiSettings::setup(lastSampleRate, getTotalNumOutputChannels(), samplesPerBlock);
}

void IncrediblySimpleFmsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IncrediblySimpleFmsynthAudioProcessor::setPreferredBusArrangement (bool                   isInput,
                                                                        int                    bus,
                                                                        const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void IncrediblySimpleFmsynthAudioProcessor::processBlock (AudioSampleBuffer& buffer,
                                                          MidiBuffer&        midiMessages)
{
    for (int i = synth.getNumVoices(); --i >= 0;)
    {
        if ((voice = dynamic_cast<SimpleVoice*>(synth.getVoice(i))))
        {
            voice->setParameters(double(modulationFrequencyRatioParameter->get()),
                                 double(modulationIndexParamter->get()));
        }
    }
    
    buffer.clear();
    
    synth.renderNextBlock(buffer,
                          midiMessages,
                          0,
                          buffer.getNumSamples());
    
    
}

//==============================================================================
bool IncrediblySimpleFmsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* IncrediblySimpleFmsynthAudioProcessor::createEditor()
{
    return new IncrediblySimpleFmsynthAudioProcessorEditor (*this);
}

//==============================================================================
void IncrediblySimpleFmsynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream stream(destData, true);
    
    stream.writeFloat(*modulationIndexParamter);
    stream.writeFloat(*modulationFrequencyRatioParameter);
}

void IncrediblySimpleFmsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
    
    modulationIndexParamter->setValueNotifyingHost(stream.readFloat());
    modulationFrequencyRatioParameter->setValueNotifyingHost(stream.readFloat());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IncrediblySimpleFmsynthAudioProcessor();
}
