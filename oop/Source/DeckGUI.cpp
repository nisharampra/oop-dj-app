
// DeckGUI.cpp
#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"
#include "BinaryData.h"
#include <juce_audio_formats/juce_audio_formats.h>
#include <memory>
#include <juce_audio_utils/juce_audio_utils.h>
#include "PlaylistComponent.h"


//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                AudioFormatManager& formatManagerToUse,
                AudioThumbnailCache& cacheToUse
           ) : player(_player)
{
    //load play stop
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
//vol speed pos
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posLabel);
    addAndMakeVisible(statusLabel);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    volSlider.setSliderStyle(juce::Slider::Rotary);
    speedSlider.setSliderStyle(juce::Slider::Rotary);
    posSlider.setSliderStyle(juce::Slider::Rotary);

    volLabel.setText("Volume", juce::dontSendNotification);
    speedLabel.setText("Speed", juce::dontSendNotification);
    posLabel.setText("Position", juce::dontSendNotification);

    volLabel.setFont(Font(14.0f));
    speedLabel.setFont(Font(14.0f));
    posLabel.setFont(Font(14.0f));

    volLabel.setColour(Label::textColourId, Colours::white);
    speedLabel.setColour(Label::textColourId, Colours::white);
    posLabel.setColour(Label::textColourId, Colours::white);

    // Load the background image
    backgroundImage = ImageFileFormat::loadFrom(BinaryData::bg_png, BinaryData::bg_pngSize);

    startTimer(500);


    setSize(600, 110);

    // Add the aButton
    addAndMakeVisible(aButton);
    aButton.setButtonText("a");
    aButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    aButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    aButton.addListener(this);
    aButton.setComponentID("aButton");

    // Add the bButton
    addAndMakeVisible(bButton);
    bButton.addListener(this);
    bButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    bButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    bButton.setButtonText("b");
    
    
    // Add the cButton
    addAndMakeVisible(cButton);
    cButton.addListener(this);
    cButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    cButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    cButton.setButtonText("c");
    
    
    // Add the dButton
    addAndMakeVisible(dButton);
    dButton.addListener(this);
    dButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    dButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    dButton.setButtonText("d");
    
    // Add the eButton
    addAndMakeVisible(eButton);
    eButton.addListener(this);
    eButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    eButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    eButton.setButtonText("e");
    
    // Add the fButton
    addAndMakeVisible(fButton);
    fButton.addListener(this);
    fButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    fButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    fButton.setButtonText("f");
    // Add the gButton
    addAndMakeVisible(gButton);
    gButton.addListener(this);
    gButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    gButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    gButton.setButtonText("g");
  

    // Add this section to set up AudioFormatManager
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    

    // Add the mute button
    addAndMakeVisible(muteButton);
    muteButton.setButtonText("Mute");
    muteButton.addListener(this);
    muteButton.setToggleState(false, juce::dontSendNotification); // Initialize as not muted



    // Inside DeckGUI constructor
    muteButton.addListener(this);

    //delete button
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    deleteButton.setButtonText("Delete");
    
    
    // Add the drum button
      addAndMakeVisible(drumButton);
      drumButton.addListener(this);
      drumButton.setButtonText("Play Drum");
    drumFilePath = File();
    
    // Add the alarm button
    addAndMakeVisible(alarmButton);
    alarmButton.addListener(this);
    alarmButton.setButtonText("Play Alarm");

    // Add the alarm button
    addAndMakeVisible(clapButton);
    clapButton.addListener(this);
    clapButton.setButtonText("Play clap");
    
    // Add the alarm button
    addAndMakeVisible(boingButton);
    boingButton.addListener(this);
    boingButton.setButtonText("boing");
  
  

}




DeckGUI::~DeckGUI()
{
    checkTheTimeButton.removeListener(this);
    stopTimer();
}


void DeckGUI::buttonClicked(Button* button)
{
    //play button
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
    
    //stop button
    else if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    
    //load button
    else if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
                             {
            player->loadURL(URL{chooser.getResult()});
            statusLabel.setText("Music loaded: " + chooser.getResult().getFileName(), dontSendNotification);
        });
    }

    //drum button
    else if (button == &drumButton)
    {
        if (selectedDrumFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + selectedDrumFile.getFullPathName()});
            player->start();
            std::cout << "Drum music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    selectedDrumFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to drum file: " << selectedDrumFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + selectedDrumFile.getFullPathName()});
                    player->start();
                    std::cout << "Drum music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: Drum music file not found." << std::endl;
                }
            });
        }
    }
    
    
  //a key button
    else if (button == &aButton)
    {
        if (aButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + aButtonFile.getFullPathName()});
            player->start();
            std::cout << "a Button music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    aButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to a Button file: " << aButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + aButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "a button music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: a button music file not found." << std::endl;
                }
            });
        }
    }
  
    //b button
    else if (button == &bButton)
    {
        if (bButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + bButtonFile.getFullPathName()});
            player->start();
            std::cout << "b Button music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    bButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to b Button file: " << bButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + bButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "b button music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: b button music file not found." << std::endl;
                }
            });
        }
    }

//c butto n
    else if (button == &cButton)
    {
        if (cButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + cButtonFile.getFullPathName()});
            player->start();
            std::cout << "c Button music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    cButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to c Button file: " << cButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + cButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "c button music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: a button music file not found." << std::endl;
                }
            });
        }
    }


//d button
    else if (button == &dButton)
    {
        if (dButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + dButtonFile.getFullPathName()});
            player->start();
            std::cout << "d Button music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    dButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to a d Button file: " << dButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + dButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "a d button music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: a d button music file not found." << std::endl;
                }
            });
        }
    }

// e button
    else if (button == &eButton)
    {
        if (eButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + eButtonFile.getFullPathName()});
            player->start();
            std::cout << "a eButton music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    eButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to a eButton file: " << eButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + eButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "a e button music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: a e button music file not found." << std::endl;
                }
            });
        }
    }

    //f button
    else if (button == &fButton)
    {
        if (fButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + fButtonFile.getFullPathName()});
            player->start();
            std::cout << "af Button music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    fButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to a  fButton file: " << fButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + fButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "a fbutton music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: a fbutton music file not found." << std::endl;
                }
            });
        }
    }

//g button
    else if (button == &gButton)
    {
        if (gButtonFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + gButtonFile.getFullPathName()});
            player->start();
            std::cout << "a gButton music playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    gButtonFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to a g Button file: " << gButtonFile.getFullPathName() << std::endl;

                    // Load and play the selected music file
                    player->loadURL(URL{"file://" + gButtonFile.getFullPathName()});
                    player->start();
                    std::cout << "a gbutton music loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: ag button music file not found." << std::endl;
                }
            });
        }
    }

    


//mute button
    if (button == &muteButton)
    {
        player->setMute(muteButton.getToggleState());
    }

    // Inside the buttonClicked method
    else if (button == &deleteButton)
       {
           if (selectedDrumFile.exists())
           {
               // Stop the player if it's playing the deleted file
               player->stop();

               // Remove the selected drum file
               selectedDrumFile = File();
               statusLabel.setText("Song removed.", dontSendNotification);
           }
           else
           {
               // Inform the user that there is no song to delete
               statusLabel.setText("No song selected.", dontSendNotification);
           }
       }
  
//alarmbutton
    else if (button == &alarmButton)
    {
        if (selectedAlarmFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + selectedAlarmFile.getFullPathName()});
            player->start();
            std::cout << "Alarm playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    selectedAlarmFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to alarm file: " << selectedAlarmFile.getFullPathName() << std::endl;

                    // Load and play the selected alarm file
                    player->loadURL(URL{"file://" + selectedAlarmFile.getFullPathName()});
                    player->start();
                    std::cout << "Alarm loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: Alarm file not found." << std::endl;
                }
            });
        }
    }
    
    //clapbutton
    else if (button == &clapButton)
    {
        if (selectedAlarmFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + selectedAlarmFile.getFullPathName()});
            player->start();
            std::cout << "clap playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    selectedAlarmFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to clap file: " << selectedAlarmFile.getFullPathName() << std::endl;

                    // Load and play the selected alarm file
                    player->loadURL(URL{"file://" + selectedAlarmFile.getFullPathName()});
                    player->start();
                    std::cout << "clap loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: clap file not found." << std::endl;
                }
            });
        }
    }
    
    //boingbutton
    else if (button == &boingButton)
    {
        if (selectedAlarmFile.exists())
        {
            // The file is already loaded, play it
            player->loadURL(URL{"file://" + selectedAlarmFile.getFullPathName()});
            player->start();
            std::cout << "boing playing." << std::endl;
        }
        else
        {
            // The file is not loaded, show the file chooser
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                if (chooser.getResult().existsAsFile())
                {
                    // Get the selected file
                    selectedAlarmFile = chooser.getResult();

                    // Debugging: Print the full path to the console
                    std::cout << "Full path to boing file: " << selectedAlarmFile.getFullPathName() << std::endl;

                    // Load and play the selected alarm file
                    player->loadURL(URL{"file://" + selectedAlarmFile.getFullPathName()});
                    player->start();
                    std::cout << "boing loaded and playing." << std::endl;
                }
                else
                {
                    std::cerr << "Error: boing file not found." << std::endl;
                }
            });
        }
    }
    



}
    void DeckGUI::paint(Graphics& g)
    {
        g.drawImage(backgroundImage, getLocalBounds().toFloat());
        // Your painting code goes here...
    }
    
    void DeckGUI::resized()
    {
        
        // for play stop load button
        double rowH = getHeight() / 8;
        int circleButtonSize = std::min(static_cast<int>(getWidth()), static_cast<int>(rowH)) / 2;
        
        playButton.setBounds(getWidth() / 4 - circleButtonSize, rowH / 2 - circleButtonSize, circleButtonSize * 2, circleButtonSize * 2);
        stopButton.setBounds(3 * getWidth() / 4 - circleButtonSize, rowH / 2 - circleButtonSize, circleButtonSize * 2, circleButtonSize * 2);
        int loadButtonSize = circleButtonSize * 2;
        loadButton.setBounds(getWidth() / 2 - loadButtonSize / 2, rowH / 2 - loadButtonSize / 2, loadButtonSize, loadButtonSize);

        //for volume speed pos
        int sliderWidth = getWidth() / 3;
        int sliderHeight = rowH * 1.5;
        int yPosition = rowH * 1; // Set a common Y-axis position for all sliders

        volSlider.setBounds(0, yPosition, sliderWidth, sliderHeight);
        speedSlider.setBounds(sliderWidth, yPosition, sliderWidth, sliderHeight);
        posSlider.setBounds(2 * sliderWidth, yPosition, sliderWidth, sliderHeight);

/// volume speed speed lable
        
        int labelHeight = 20;
        int newRowY = 120;

        int newX = 100;
        volLabel.setBounds(newX, newRowY, sliderWidth, labelHeight);

        int newSpeedX = 270;  // Set the desired x-coordinate for speedLabel
        speedLabel.setBounds(newSpeedX, newRowY, sliderWidth, labelHeight);

        int newPosX = 430;  // Set the desired x-coordinate for posLabel
        posLabel.setBounds(newPosX, newRowY, sliderWidth, labelHeight);
        
        
        //status button
        int newXPositionForStatusLabel = getWidth() / 2 - 50; // Adjust the value as needed
        statusLabel.setBounds(newXPositionForStatusLabel, rowH * 2+10, 200, 20);


        //drum button
        int buttonWidth = 100;
        int buttonHeight = 30;
        drumButton.setBounds(getWidth() / 2 - buttonWidth / 2, rowH * 6-40, buttonWidth, buttonHeight);
        
        //alarm button
        int alarmButtonWidth = 100;
        int alarmButtonHeight = 30;

        int newXPositionForAlarmButton = getWidth() / 2 - alarmButtonWidth / 2 - 160;
        int newYPositionForAlarmButton = rowH * 6-40;
        alarmButton.setBounds(newXPositionForAlarmButton, newYPositionForAlarmButton, alarmButtonWidth, alarmButtonHeight);
        
        //clap
        int clapButtonWidth = 100;
        int clapButtonHeight = 30;

        int newXPositionForclapButton = getWidth() / 2 - clapButtonWidth / 2 - 160;
        int newYPositionForclapButton = rowH * 6;
        clapButton.setBounds(newXPositionForclapButton, newYPositionForclapButton, clapButtonWidth, clapButtonHeight);

        //boing
        int boingbuttonWidth = 100;
        int boingbuttonHeight = 30;

        boingButton.setBounds(getWidth() / 2 - buttonWidth / 2, rowH * 6, boingbuttonWidth, boingbuttonHeight);


        //for piano
        int miniButtonWidth = 50;
        int miniButtonHeight = 90;
        
        
        int leftMargin = 10; // Adjust this value as needed
        int spacing = -1;    // Adjust this value as needed

        aButton.setBounds(leftMargin, rowH * 7, miniButtonWidth, miniButtonHeight);
        bButton.setBounds(leftMargin + miniButtonWidth + spacing, rowH * 7, miniButtonWidth, miniButtonHeight);
        cButton.setBounds(leftMargin + 2 * (miniButtonWidth + spacing), rowH * 7, miniButtonWidth, miniButtonHeight);
        dButton.setBounds(leftMargin + 3 * (miniButtonWidth + spacing), rowH * 7, miniButtonWidth, miniButtonHeight);
        eButton.setBounds(leftMargin + 4 * (miniButtonWidth + spacing), rowH * 7, miniButtonWidth, miniButtonHeight);
        fButton.setBounds(leftMargin + 5 * (miniButtonWidth + spacing), rowH * 7, miniButtonWidth, miniButtonHeight);
        gButton.setBounds(leftMargin + 6 * (miniButtonWidth + spacing), rowH * 7, miniButtonWidth, miniButtonHeight);
        
        //mute button
        int newY = 730;
        muteButton.setBounds(leftMargin + 7 * (miniButtonWidth + spacing), newY, miniButtonWidth, miniButtonHeight);

        //delete button
        int newDeleteButtonX = 360;
        int newDeleteButtonY = 720;
        int deleteButtonWidth = 70; // Adjust the width as needed
        int deleteButtonHeight = 30; // Adjust the height as needed

        deleteButton.setBounds(newDeleteButtonX, newDeleteButtonY, deleteButtonWidth, deleteButtonHeight);

       
    }

//slider
void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    else if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(URL{File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
}


