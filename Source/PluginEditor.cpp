/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
IncrediblySimpleFmsynthAudioProcessorEditor::IncrediblySimpleFmsynthAudioProcessorEditor (IncrediblySimpleFmsynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);
    
    modulationIndex.setName("ModIndex");
    modulationIndex.addListener(this);
    modulationIndex.setSliderStyle (Slider::LinearBarVertical);
    modulationIndex.setRange(0.0, 1500.0, 0.0);
    modulationIndex.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    modulationIndex.setPopupDisplayEnabled(true, this);
    modulationIndex.setTextValueSuffix(" % Gnarly");
    modulationIndex.setValue(0.0);
    
    addAndMakeVisible(modulationIndex);
    
    modulationFrequencyRatio.setName("ModFreqRatio");
    modulationFrequencyRatio.addListener(this);
    modulationFrequencyRatio.setSliderStyle (Slider::LinearBarVertical);
    modulationFrequencyRatio.setRange(-3.8, 3.8, 0);
    modulationFrequencyRatio.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    modulationFrequencyRatio.setPopupDisplayEnabled(true, this);
    modulationFrequencyRatio.setTextValueSuffix(" Times The Carrier's Frequency");
    modulationFrequencyRatio.setValue(0.0);
    
    addAndMakeVisible(modulationFrequencyRatio);
    
    startTimer(100);
}

IncrediblySimpleFmsynthAudioProcessorEditor::~IncrediblySimpleFmsynthAudioProcessorEditor()
{
}

//==============================================================================
void IncrediblySimpleFmsynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Simple FM Synth", 0, 0, getWidth(), 30, Justification::centred, 1);
    
    
}

void IncrediblySimpleFmsynthAudioProcessorEditor::resized()
{
    modulationIndex.setBounds(40, 30, 20, getHeight() - 60);
    
    modulationFrequencyRatio.setBounds(getWidth() - 40 - modulationFrequencyRatio.getWidth(), 30, 20, getHeight() - 60);
}

void IncrediblySimpleFmsynthAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider->getName() == "ModIndex")
    {
        setParameterValue("ModIndex", modulationIndex.getValue());
    }
    else if (slider->getName() == "ModFreqRatio")
    {
        setParameterValue("ModFreqRatio", modulationFrequencyRatio.getValue());
    }
}

void IncrediblySimpleFmsynthAudioProcessorEditor::timerCallback()
{
//    modulationFrequencyRatio.setValue(getParameterValue("ModFreqRatio"),
//                                      NotificationType::dontSendNotification);
//    modulationIndex.setValue(getParameterValue("ModIndex"),
//                             NotificationType::dontSendNotification);
}

AudioProcessorParameter* IncrediblySimpleFmsynthAudioProcessorEditor::getParameter (const String& paramId)
{
    if (AudioProcessor* processor = getAudioProcessor())
    {
        const OwnedArray<AudioProcessorParameter>& params = processor->getParameters();
        
        for (int i = 0; i < params.size(); ++i)
        {
            if (AudioProcessorParameterWithID* param = dynamic_cast<AudioProcessorParameterWithID*> (params[i]))
            {
                if (param->paramID == paramId)
                    return param;
            }
        }
    }
    
    return nullptr;
}

float IncrediblySimpleFmsynthAudioProcessorEditor::getParameterValue (const String& paramId)
{
    if (AudioProcessorParameter* param = getParameter (paramId))
        return param->getValue();
    
    return 0.0f;
}

void IncrediblySimpleFmsynthAudioProcessorEditor::setParameterValue (const String& paramId, float value)
{
    if (AudioProcessorParameter* param = getParameter (paramId))
        param->setValueNotifyingHost (value);
}
