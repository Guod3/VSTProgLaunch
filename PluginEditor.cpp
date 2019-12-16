/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VstprogLaunchAudioProcessorEditor::VstprogLaunchAudioProcessorEditor (VstprogLaunchAudioProcessor& p, ValueTree& vts)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    auto s = vts.toXmlString();
    DBG("***EDITORCONS****\n" + s);
    setSize (400,300);
    executableTextBox.reset( new TextListener(p.ExecutablePathVal,  vts.getProperty("ExecutablePath", 0)));
    argumentsTextBox.reset(new TextListener(p.ArgumentsVal, vts.getProperty("Arguments", 0)));
    statusTextBox.reset(new TextEditor());
    addAndMakeVisible(executableTextBox.get());
    addAndMakeVisible(argumentsTextBox.get());
    addAndMakeVisible(statusTextBox.get());
    resized();

    statusTextBox->setText("Save and restart project after change of exe or target!!!");
}

VstprogLaunchAudioProcessorEditor::~VstprogLaunchAudioProcessorEditor()
{
    processor.MyProcess.kill();
}

//==============================================================================
void VstprogLaunchAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Executable path:", getLocalBounds(), Justification::centredTop, 1);
    g.drawFittedText("Arguments:", getLocalBounds(), Justification::centred, 1);
}

void VstprogLaunchAudioProcessorEditor::resized()
{
    if(executableTextBox!=nullptr)
        executableTextBox->setBounds(10, 20, 380, 30);
    if (argumentsTextBox != nullptr)
         argumentsTextBox->setBounds(10, 110, 380, 30);
    if (statusTextBox != nullptr)
        statusTextBox->setBounds(10, 180, 380, 100);
}
