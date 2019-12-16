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
class Process_Timer : public Timer
{
public:
    Process_Timer(ChildProcess* proc, String cmdline) {

        myproc = proc;
        CmdLine = cmdline;
    }
    void timerCallback() {
        String St;
        if (!myproc->isRunning())
            myproc->start(CmdLine, 0);
    }
private:

    String CmdLine;
    ChildProcess* myproc;
};
struct TreeListenerDB : public ValueTree::Listener
{
    TreeListenerDB(ValueTree v)
        : tree(v)
    {
        tree.addListener(this);
    }
    ~TreeListenerDB() { tree.removeListener(this); };
    void valueTreePropertyChanged(ValueTree& vt, const Identifier& id)
    {
        DBG("***valueTreePropertyChanged***" + vt.getType().toString() + "," + id.toString());
        auto fileText = tree.toXmlString();
        DBG(fileText.substring(fileText.indexOf(0, "?>") + 6));	//display, xml header stripped 
    };
    void valueTreeChildAdded(ValueTree&, ValueTree&) {};
    void valueTreeChildRemoved(ValueTree&, ValueTree&, int) {};
    void valueTreeChildOrderChanged(ValueTree&, int, int) {};
    void valueTreeParentChanged(ValueTree&) {};
    //void ValueTree::Listener::valueTreeRedirected(ValueTree&){};

    ValueTree tree;
};
class VstprogLaunchAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VstprogLaunchAudioProcessor();
    ~VstprogLaunchAudioProcessor();

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

    static Identifier mainNodeType; // pre-create an Identifier
    static Identifier ExecutablePathID;
    static Identifier ArgumentsID;


    Value ExecutablePathVal;
    Value ArgumentsVal;
    ValueTree path_args;
    TreeListenerDB* treelisn;

    ChildProcess MyProcess;
    std::unique_ptr < Process_Timer> timer;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VstprogLaunchAudioProcessor)

  
};
  