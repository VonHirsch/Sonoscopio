//
//  StreamManager.h
//  Sonoscopio
//
//  Created by Very Von on 5/28/21.
//

#pragma once

#include "ofMain.h"

#include "MainPanel.h"
#include "TimelinePanel.h"
#include "MetersPanel.h"

class StreamManager {

public:
    static StreamManager& getInstance(){
        static StreamManager instance;
        return instance;
    }

    void setupStream();
    
    void setMainPanelPtr(MainPanel* panelPtr){
        mainPanelPtr = panelPtr;
    }
    void setMetersPanelPtr(MetersPanel* panelPtr){
        metersPanelPtr = panelPtr;
    }
    void setTimelinePanelPtr(TimelinePanel* panelPtr){
        timelinePanelPtr = panelPtr;
    }
    
    bool isStreaming(){return bIsStreaming;}
                
private:
    StreamManager();
    
    int samplerate;    
    int channels;
    
    bool bIsStreaming;
    
    MainPanel* mainPanelPtr;
    MetersPanel* metersPanelPtr;
    TimelinePanel* timelinePanelPtr;

};

