/*
  ==================================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==================================================================================
*/


#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <memory>
#include "maximilian.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==================================================================================
/**
 */
struct SimpleSound : public SynthesiserSound
{
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

//==================================================================================
/**
 */
class SimpleVoice : public SynthesiserVoice
{
public:
    SimpleVoice() : modulationFrequencyRatio(0),
                    modulationIndex(0),
                    frequency(1),
                    level(0)
    {}
    
    void setParameters(double modRatio,
                       double modIndex)
    {
        modulationFrequencyRatio = modRatio;
        modulationIndex          = modIndex;
    }
    
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast<SimpleSound*>(sound) != nullptr;
    }
    
    void startNote(int midiNoteNumber,
                   float velocity,
                   SynthesiserSound*,
                   int) override
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
    }
    
    void stopNote(float, bool) override
    {
        level = 0;
        clearCurrentNote();
    }
    
    void renderNextBlock(AudioSampleBuffer& outputBuffer,
                         int                startSample,
                         int                numberSamples) override
    {
        while (--numberSamples >= 0)
        {
            const double modulatorFrequency = frequency + frequency * modulationFrequencyRatio;
            const double modulationLevel    = modulationIndex;
            const double modulationSample   = modulationLevel * modulator.sinewave(modulatorFrequency);
            
            const double carrierFrequency   = frequency + modulationSample;
            
            const float  currentSample      = level * float(carrier.sinewave(carrierFrequency));
            
            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, currentSample);
                
            ++startSample;
        }
    }
    
    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}
    
    
private:
    maxiOsc          carrier;
    maxiOsc          modulator;
    double           modulationFrequencyRatio;
    double           modulationIndex;
    double           frequency;
    double           level;
};


//==================================================================================
/**
 */
class IncrediblySimpleFmsynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    IncrediblySimpleFmsynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
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

    static constexpr int maxNumVoices = 1;
    
private:
    SimpleVoice*         voice;
    Synthesiser          synth;
    AudioParameterInt*   modulationIndexParamter;
    AudioParameterFloat* modulationFrequencyRatioParameter;
    double               lastSampleRate;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IncrediblySimpleFmsynthAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
