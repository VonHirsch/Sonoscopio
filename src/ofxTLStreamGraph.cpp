//
//  ofxTLStreamGraph.cpp
//  Sonoscopio
//
//  Created by Very Von on 5/29/21.
//

#include "ofxTLStreamGraph.h"
#include "ofxTimeline.h"
#include "PanelsBridge.h"

ofxTLStreamGraph::ofxTLStreamGraph(){
    metersPanelPtr = PanelsBridge::getInstance().metersPanelPtr;
}

ofxTLStreamGraph::~ofxTLStreamGraph(){
}

void ofxTLStreamGraph::draw(){
    ofPushStyle();
    ofSetColor(120);//arbitrary color
    for(int i=0; i<previews.size(); i++){
        previews[i].draw();
    }
    ofPopStyle();
}

void ofxTLStreamGraph::update(){

    // use code from OscSender.cpp
    //auto metersValues = metersPanelPtr->getMetersValues();
    
}
