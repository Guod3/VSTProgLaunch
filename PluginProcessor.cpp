/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Identifier VstprogLaunchAudioProcessor::mainNodeType("Plugstate");
Identifier VstprogLaunchAudioProcessor::ExecutablePathID("ExecutablePath");
Identifier VstprogLaunchAudioProcessor::ArgumentsID("Arguments");


VstprogLaunchAudioProcessor::VstprogLaunchAudioProcessor() 
{
    ValueTree vtree(mainNodeType);		//create valuetree instance
    path_args = vtree;
    treelisn = new TreeListenerDB(path_args);

    vtree.setProperty(ExecutablePathID, "default exec", 0);
    ExecutablePathVal.referTo(vtree.getPropertyAsValue(ExecutablePathID, 0));
    vtree.setProperty(ArgumentsID, "default arg", nullptr);
    ArgumentsVal.referTo(vtree.getPropertyAsValue(ArgumentsID, nullptr));

  
    auto s = path_args.toXmlString();
    DBG("***CONSTR****\n" + s);
}

VstprogLaunchAudioProcessor::~VstprogLaunchAudioProcessor()
{
    delete treelisn;
}

//==============================================================================
const String VstprogLaunchAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VstprogLaunchAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VstprogLaunchAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VstprogLaunchAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VstprogLaunchAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VstprogLaunchAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VstprogLaunchAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VstprogLaunchAudioProcessor::setCurrentProgram (int index)
{
}

const String VstprogLaunchAudioProcessor::getProgramName (int index)
{
    return {};
}

void VstprogLaunchAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VstprogLaunchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    String exe = path_args.getProperty("ExecutablePath", 0);
    String arg = path_args.getProperty("Arguments", 0);
    String CL = exe + " " + arg;

    timer.reset(new Process_Timer(&MyProcess, CL));
    timer->startTimer(1000);
}

void VstprogLaunchAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VstprogLaunchAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VstprogLaunchAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

        // ..do something to the data...
    }
}

//==============================================================================
bool VstprogLaunchAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VstprogLaunchAudioProcessor::createEditor()
{
    auto s = path_args.toXmlString();
    DBG("***CREATE****\n" + s);
    return new VstprogLaunchAudioProcessorEditor (*this,path_args);
}

//==============================================================================
void VstprogLaunchAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(path_args.createXml());

    if (xml != nullptr) {
        copyXmlToBinary(*xml, destData);
        auto s = path_args.toXmlString();
        DBG("***SAVE****\n" + s);
    }
}

void VstprogLaunchAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    ValueTree temp;
    if (xml != nullptr) {
       temp = ValueTree::fromXml(*xml);
       path_args.copyPropertiesFrom(temp, nullptr);//update and replace
       auto s = path_args.toXmlString();
       DBG("***LOAD****\n" + s);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VstprogLaunchAudioProcessor();
}
