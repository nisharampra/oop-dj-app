/*
  ==============================================================================

    PlaylistComponent.h
    Created: 18 Feb 2024 1:43:25pm
    Author:  Nisha Ramprasath

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

#include "DeckGUI.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public TableListBoxModel, public Button::Listener
{
public:
    PlaylistComponent(DJAudioPlayer* player1, DJAudioPlayer* player2, DeckGUI* deckGUI1, DeckGUI* deckGUI2);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    void paintRowBackground(Graphics & g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    void buttonClicked(Button * button) override;
    void LoadingToDeck1();
    void LoadingToDeck2();
    void DeleteFromPlaylist();
    
private:

    int rowChosen;

    TableListBox tableComponent;
    
    juce::Array<juce::String> trackTitles;

    juce::Array<juce::URL> songs;

    TextButton loadButton{ "LOAD" };


    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;

    FileChooser fChooser{ "Select a song..",juce::File(),"*.mp3,*.wav,*.aiff" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
