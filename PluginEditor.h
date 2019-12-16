/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class TextListener : public TextEditor, public Value::Listener
{
public:
    TextListener(Value& value, const String& s)
    {
       // myValue.refersToSameSourceAs(value);
        myValue.addListener(this);   //add this texteditor to the Value's listener list
        myValue.referTo(value);		 //make it refer to 	
        setText(s, false);			 //initial text to show	

        onTextChange = [this] {	myValue.setValue(getText()); DBG(">>>" + getText()); };
    }
    ~TextListener() { myValue.removeListener(this); }

    void valueChanged(Value& val) override { setText(val.getValue(), false); };

private:	
    Value myValue;
};

//==============================================================================
/**
*/
class VstprogLaunchAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    VstprogLaunchAudioProcessorEditor (VstprogLaunchAudioProcessor&, ValueTree&);
    ~VstprogLaunchAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VstprogLaunchAudioProcessor& processor;
    
   
  
    std::unique_ptr < TextListener> executableTextBox;
    std::unique_ptr < TextListener> argumentsTextBox;
    std::shared_ptr < TextEditor> statusTextBox;
    std::unique_ptr < Process_Timer> timer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VstprogLaunchAudioProcessorEditor)
};
