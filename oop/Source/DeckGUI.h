//
//// DeckGUI.h
//#pragma once
////piano
//#include "../JuceLibraryCode/JuceHeader.h"
//#include "DJAudioPlayer.h"
//
////==============================================================================
//class DeckGUI    : public Component,
//                   public Button::Listener,
//                   public Slider::Listener,
//                   public FileDragAndDropTarget,
//                   public Timer
//{
//public:
//    DeckGUI(DJAudioPlayer* player,
//           AudioFormatManager& formatManagerToUse,
//           AudioThumbnailCache& cacheToUse);
//    ~DeckGUI();
//    void setSource(AudioTransportSource* newSource, TimeSliceThread* backgroundThread, double sourceSampleRate);
//
//
//    void paint(Graphics&) override;
//    void resized() override;
//
//    void buttonClicked(Button*) override;
//    void sliderValueChanged(Slider* slider) override;
//
//    bool isInterestedInFileDrag(const StringArray& files) override;
//    void filesDropped(const StringArray& files, int x, int y) override;
//
//    void timerCallback() override;
//    void checkTime(); // Declare the checkTime method
//    
//    void setMute(bool shouldMute);
//        bool isMuted() const;
//    bool isLooping() const;
//    
//  
//
//private:
//    LookAndFeel_V4 customLookAndFeel;
//    Image backgroundImage;  // Add a member variable for the background image
//
//    TextButton playButton{"PLAY"};
//    TextButton stopButton{"STOP"};
//    TextButton loadButton{"LOAD"};
//  
//    Slider volSlider;
//    Slider speedSlider;
//    Slider posSlider;
//
//    Label volLabel;
//    Label speedLabel;
//    Label posLabel;
//    Label statusLabel;
//    FileChooser fChooser{"Select a file..."};
//    juce::TextButton checkTheTimeButton;
////    juce::Label timeLabel;
//    TextButton drumButton;
//    TextButton aButton;
//    TextButton bButton;
//    TextButton cButton;
//    TextButton dButton;
//    TextButton eButton;
//    TextButton fButton;
//    TextButton gButton;
//    AudioFormatManager formatManager;
//    TextButton softButton;
//    DJAudioPlayer* player;
//    File drumFilePath;
//    File aButtonFile;
//    File bButtonFile;
//    File cButtonFile;
//    File dButtonFile;
//    File eButtonFile;
//    File fButtonFile;
//    File gButtonFile;
//
//    File selectedMusicFile;
//    File lastSelectedMusicFile;
//    bool isMusicPlaying;
//    File selectedDrumFile;
//    
//    ToggleButton muteButton;
////    TextButton loopButton;
////    bool looping;
//
//    // Add this declaration in the DeckGUI class
//    TextButton deleteButton;
//    // Add this declaration in the DeckGUI class
//    TextButton setButton;
//
//    TextButton alarmButton;
//       File selectedAlarmFile;
//
//    TextButton clapButton;
//       File selectedclapFile;
//    
//    TextButton boingButton;
//       File selectedboingFile;
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
//};
// DeckGUI.h
#pragma once

// Include necessary JUCE headers and your custom DJAudioPlayer
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"

//==============================================================================
// The DeckGUI class represents the graphical user interface for a music deck.
class DeckGUI    : public Component,
                   public Button::Listener,
                   public Slider::Listener,
                   public FileDragAndDropTarget,
                   public Timer
{
public:
    // Constructor for DeckGUI
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse);

    // Destructor for DeckGUI
    ~DeckGUI();

    // Set the audio source for the deck
    void setSource(AudioTransportSource* newSource, TimeSliceThread* backgroundThread, double sourceSampleRate);

    // Override paint method for custom drawing
    void paint(Graphics&) override;

    // Override resized method for layout adjustments
    void resized() override;

    // Button click callback
    void buttonClicked(Button*) override;

    // Slider value change callback
    void sliderValueChanged(Slider* slider) override;

    // Check if the component is interested in file drag events
    bool isInterestedInFileDrag(const StringArray& files) override;

    // Handle files dropped onto the component
    void filesDropped(const StringArray& files, int x, int y) override;

    // Timer callback for periodic tasks
    void timerCallback() override;

    // Additional method to check and display the current time
    void checkTime();

    // Set the mute state of the deck
    void setMute(bool shouldMute);

    // Check if the deck is currently muted
    bool isMuted() const;

   

private:
    // Custom LookAndFeel for the GUI components
    LookAndFeel_V4 customLookAndFeel;

    // Background image for the deck
    Image backgroundImage;

    // Various GUI components
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    Label volLabel;
    Label speedLabel;
    Label posLabel;
    Label statusLabel;
    FileChooser fChooser{"Select a file..."};
    juce::TextButton checkTheTimeButton;
    TextButton drumButton;
    TextButton aButton;
    TextButton bButton;
    TextButton cButton;
    TextButton dButton;
    TextButton eButton;
    TextButton fButton;
    TextButton gButton;
    AudioFormatManager formatManager;
    TextButton softButton;
    DJAudioPlayer* player;
    File drumFilePath;
    File aButtonFile;
    File bButtonFile;
    File cButtonFile;
    File dButtonFile;
    File eButtonFile;
    File fButtonFile;
    File gButtonFile;
    File selectedMusicFile;
    File lastSelectedMusicFile;
    bool isMusicPlaying;
    File selectedDrumFile;
    ToggleButton muteButton;

    // Additional buttons for functionality
    TextButton deleteButton;
    TextButton setButton;
    TextButton alarmButton;
    File selectedAlarmFile;
    TextButton clapButton;
    File selectedclapFile;
    TextButton boingButton;
    File selectedboingFile;

    // Macro to automatically generate leak detector code
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
