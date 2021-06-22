//
//  ofxTLStreamGraph.h
//  Sonoscopio
//
//  Created by Very Von on 5/29/21.
//

#pragma once

#include "ofMain.h"
#include "ofxTLTrack.h"
#include "MetersPanel.h"

class ofxTLStreamGraph : public ofxTLTrack {
  public:
    
    ofxTLStreamGraph();
    virtual ~ofxTLStreamGraph();

    virtual void draw();
    virtual void update();
        
    MetersPanel* metersPanelPtr;
    
    vector<ofPolyline> previews;
    
};
