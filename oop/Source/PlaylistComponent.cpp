/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 18 Feb 2024 1:43:25pm
    Author:  Nisha Ramprasath

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player1, DJAudioPlayer* _player2,DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
    : player1(_player1), player2(_player2), deckGUI1(_deckGUI1) , deckGUI2(_deckGUI2)
{

    addAndMakeVisible(loadButton);

    loadButton.addListener(this);

    /*
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");*/
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    tableComponent.getHeader().addColumn("Track title", 1, 500);
    tableComponent.getHeader().addColumn("Deck1", 2, 100);
    tableComponent.getHeader().addColumn("Deck2", 3, 100);
    tableComponent.getHeader().addColumn("Delete", 4, 100);
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
   
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 50, getWidth(), getHeight()-10);


    loadButton.setBounds(0, 0, getWidth(), 50);
    
    
   

}

int PlaylistComponent::getNumRows(){
    return trackTitles.size();
}
void PlaylistComponent::paintRowBackground(Graphics & g, int rowNumber, int width, int height, bool rowIsSelected){
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    }else{
        g.fillAll(Colours::darkgrey);
    }
}
void PlaylistComponent::paintCell(Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected){
    g.drawText(trackTitles[rowNumber],2,0,width-4, height, Justification::centredLeft,true);
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) {
    if(columnId == 2){
        if(existingComponentToUpdate==nullptr){
            TextButton* btn = new TextButton{"deck1"};
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            
            btn->addListener(this);
            existingComponentToUpdate=btn;
            btn->onClick = [this] {LoadingToDeck1(); };
        }
    }
    if (columnId == 3) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "deck2" };
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
            btn->onClick = [this] {LoadingToDeck2(); };
        }
    }
    if (columnId == 4) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "delete" };
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
            btn->onClick = [this] {DeleteFromPlaylist(); };
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(Button * button) {
    //std::cout<<"PlaylistComponent::buttonClicked trackTitles id: "<< trackTitles[id] << std::endl;
    if (button == &loadButton)
    {
       // auto fileChooserFlags =
            //FileBrowserComponent::canSelectFiles;
        //fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            //{
                //songs.add(URL{ chooser.getResult() });

                //trackTitles.add(URL::removeEscapeChars(URL{ chooser.getResult() }.getFileName()));

                //tableComponent.updateContent();
            //});
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles | FileBrowserComponent::canSelectMultipleItems;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                // Handle multiple file results
                auto files = chooser.getResults();
                for (auto& file : files) {
                    songs.add(URL{ file });
                   trackTitles.add(URL::removeEscapeChars(file.getFileName()));
                }

                tableComponent.updateContent();
            });
        
       
    }
    rowChosen = button->getComponentID().getDoubleValue();
}

void PlaylistComponent::LoadingToDeck1() {
    player1->loadURL(songs[rowChosen]);
  

}
void PlaylistComponent::LoadingToDeck2() {
    player2->loadURL(songs[rowChosen]);

}
void PlaylistComponent::DeleteFromPlaylist() {
    songs.remove(rowChosen);
    trackTitles.remove(rowChosen);
    tableComponent.updateContent();
}
