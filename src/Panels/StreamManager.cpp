//
//  StreamManager.cpp
//  Sonoscopio
//
//  Created by Very Von on 5/28/21.
//

#include "ofApp.h"
#include "StreamManager.h"
#include "SettingsManager.h"
#include "AnalysisDataSaver.h"

StreamManager::StreamManager(){
    samplerate = 44100;
    channels = 2;
}

void StreamManager::setupStream(){
    
    timelinePanelPtr->setupStreaming();
    
    bIsStreaming = true;
    mainPanelPtr->setAudioFileInfo("Streaming Mode");
    timelinePanelPtr->setEnabled(true);
    metersPanelPtr->setEnabled(true);

    metersPanelPtr->resetAnalyzer(samplerate);
    SettingsManager::getInstance().loadSettings();
    AnalysisDataSaver::getInstance().reset();

}
