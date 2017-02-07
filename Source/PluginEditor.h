/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class IncrediblySimpleFmsynthAudioProcessorEditor  : public AudioProcessorEditor,
                                                     public Slider::Listener,
                                                     private Timer
{
public:
    IncrediblySimpleFmsynthAudioProcessorEditor (IncrediblySimpleFmsynthAudioProcessor&);
    ~IncrediblySimpleFmsynthAudioProcessorEditor();

    //==============================================================================
    void                     paint (Graphics&) override;
    void                     resized() override;
    void                     sliderValueChanged (Slider*) override;
private:
    void                     timerCallback() override;
    AudioProcessorParameter* getParameter (const String& paramId);
    float                    getParameterValue (const String& paramId);
    void                     setParameterValue (const String& paramId, float value);
    
    Slider                   modulationIndex;
    Slider                   modulationFrequencyRatio;
    
    IncrediblySimpleFmsynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IncrediblySimpleFmsynthAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
