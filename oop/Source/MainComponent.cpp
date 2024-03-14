/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1000, 800);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }  

    addAndMakeVisible(deckGUI1); 
    addAndMakeVisible(deckGUI2);  
    // Add a button to trigger the popup
       addAndMakeVisible(openPopupButton);
       openPopupButton.setButtonText("instruction");
       openPopupButton.onClick = [this] { showPopupMessage(); };

    formatManager.registerBasicFormats();
    showWelcomePopup();
    addAndMakeVisible(deckGUI1);
       addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);


}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

 }

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
    g.drawText("PlaylistComponent", getLocalBounds(), Justification::centred, true);

}




void MainComponent::resized()
{
    deckGUI1.setBounds(0, 0, getWidth()/2, getHeight());
    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight());
    openPopupButton.setBounds(450, 60, 100, 30);

    
    playlistComponent.setBounds(0, getHeight() - 550, getWidth(), 300);




}


void MainComponent::showPopupMessage()
{
    // Create and show an AlertWindow
    AlertWindow::showMessageBoxAsync(
        AlertWindow::InfoIcon,
        "dj app",
        "You can load, play, stop, increase and decrease the volume, speed, and position of music. "
        "To play the piano keys, drum, alarm, clap, and boing, you have to load the music manually first from the playlist on the computer. Once you have added it, you can play the piano or the buttons without any hassle.",
        "OK"
    );
}


void MainComponent::showWelcomePopup()
{
    // Create and show an AlertWindow
    AlertWindow::showMessageBoxAsync(
        AlertWindow::InfoIcon,
        "Welcome to the DJ app",
        "You can load, play, stop, increase and decrease the volume, speed, and position of music. "
        "To play the piano keys, drum, alarm, clap, and boing, you have to load the music manually first from the playlist on the computer. Once you have added it, you can play the piano or the buttons without any hassle.",
        "OK"
    );
}

