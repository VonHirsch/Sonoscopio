//
//  ofxTLStreamGraph.cpp
//  Sonoscopio
//
//  Created by Very Von on 5/29/21.
//

#include "ofxTLStreamGraph.h"
#include "ofxTimeline.h"
#include "ofxHotKeys.h"

ofxTLStreamGraph::ofxTLStreamGraph(){
    drawingStreamGraphRect = false;
    rectWidth = 120;
    rectHeight = 15;
    mouseDownRect = NULL;
    editingParam = NULL;
    drawingStreamGraphRect = false;
}

ofxTLStreamGraph::~ofxTLStreamGraph(){
    
}

void ofxTLStreamGraph::drawModalContent(){
    return;
}

//draw your keyframes into bounds
void ofxTLStreamGraph::draw(){
    
    //we draw keys our own way

    //ofxTLKeyframes::draw();
    if(bounds.width == 0 || bounds.height < 2){
        return;
    }
    
    if(shouldRecomputePreviews || viewIsDirty){
        recomputePreviews();
    }
    
    ofSetColor(timeline->getColors().disabledColor, 30);
    float currentPercent = sampleAtTime(currentTrackTime());
    ofFill();
    ofRect(bounds.x, bounds.getMaxY(), bounds.width, -bounds.height*currentPercent);
    
    ofPushStyle();
    ofSetColor(timeline->getColors().keyColor);
    preview.draw();
    
    
    for(int i = 0; i < keyframes.size(); i++){
        //make sure it's on screen
        if(isKeyframeIsInBounds(keyframes[i])){
            //we know the type because we created it in newKeyframe()
            //so we can safely cast
            ofxTLStreamGraphKey* StreamGraphKey = (ofxTLStreamGraphKey*)keyframes[i];

            if(isKeyframeSelected(keyframes[i])){
                ofSetLineWidth(2);
                ofSetColor(timeline->getColors().textColor);
            }
            else if(keyframes[i] == hoverKeyframe){
                ofSetLineWidth(4);
                ofSetColor(timeline->getColors().highlightColor);
            }
            else{
                ofSetLineWidth(4);
                ofSetColor(timeline->getColors().keyColor);
            }
            float screenX = millisToScreenX(keyframes[i]->time);
            ofLine(screenX, bounds.y, screenX, bounds.y+bounds.height);
        }
    }
    
    ofPopStyle();
}

bool ofxTLStreamGraph::mousePressed(ofMouseEventArgs& args, long millis){
    if(drawingStreamGraphRect){

    }
    else{
        ofxTLKeyframes::mousePressed(args, millis);
    }
}

void ofxTLStreamGraph::mouseMoved(ofMouseEventArgs& args, long millis){
    if(drawingStreamGraphRect){
    }
    else{
        ofxTLKeyframes::mouseMoved(args, millis);
    }
}

void ofxTLStreamGraph::mouseDragged(ofMouseEventArgs& args, long millis){
    if(drawingStreamGraphRect){
    }
    else{
        ofxTLKeyframes::mouseDragged(args, millis);
    }
}

void ofxTLStreamGraph::mouseReleased(ofMouseEventArgs& args, long millis){
    if(drawingStreamGraphRect){
    }
    else{
        ofxTLKeyframes::mouseReleased(args, millis);
    }
}

//keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
void ofxTLStreamGraph::keyPressed(ofKeyEventArgs& args){
    ofxTLKeyframes::keyPressed(args);
}

string ofxTLStreamGraph::getTrackType(){
    return "StreamGraph";
}

ofxTLKeyframe* ofxTLStreamGraph::newKeyframe(){
    //return our type of keyframe, stored in the parent class
    ofxTLStreamGraphKey* newKey = new ofxTLStreamGraphKey();
    newKey->type = OFXTL_StreamGraph_TYPE_BAR;
    newKey->phaseShift = 0; //in millis
    newKey->phaseMatch = false;
    newKey->amplitude = 1.0;
    newKey->frequency = 100.;
    newKey->center = 0 ; // 0 is middle
    newKey->interpolate = true;
    newKey->expInterpolate = false;
    newKey->seed = 0;
    return newKey;
}

void ofxTLStreamGraph::restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLStreamGraphKey* StreamGraphKey = (ofxTLStreamGraphKey*)key;
    StreamGraphKey->type = (ofxTLStreamGraphType)xmlStore.getValue("type", int(OFXTL_StreamGraph_TYPE_BAR));
    StreamGraphKey->phaseShift = xmlStore.getValue("phaseShift", 0.);
    StreamGraphKey->amplitude = xmlStore.getValue("amplitude", 1.);
    StreamGraphKey->frequency = xmlStore.getValue("frequency", 100.);
    StreamGraphKey->seed = xmlStore.getValue("seed", 0.);
    StreamGraphKey->center = xmlStore.getValue("center", 0.);
    StreamGraphKey->interpolate = xmlStore.getValue("interpolate", true);
    StreamGraphKey->expInterpolate = xmlStore.getValue("expInterpolate", true);
}

void ofxTLStreamGraph::storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLStreamGraphKey* StreamGraphKey = (ofxTLStreamGraphKey*)key;
    ofxTLStreamGraphType type;
    xmlStore.addValue("type", int(StreamGraphKey->type));
    xmlStore.addValue("phaseShift",StreamGraphKey->phaseShift);
    xmlStore.addValue("amplitude",StreamGraphKey->amplitude);
    xmlStore.addValue("frequency",StreamGraphKey->frequency);
    xmlStore.addValue("seed",StreamGraphKey->seed);
    xmlStore.addValue("center",StreamGraphKey->center);
    xmlStore.addValue("interpolate",StreamGraphKey->interpolate);
    xmlStore.addValue("expInterpolate",StreamGraphKey->expInterpolate);
}

void ofxTLStreamGraph::selectedKeySecondaryClick(ofMouseEventArgs& args){

}

void ofxTLStreamGraph::regionSelected(ofLongRange timeRange, ofRange valueRange){
    for(int i = 0; i < keyframes.size(); i++){
        if(timeRange.contains( keyframes[i]->time )){
            selectKeyframe(keyframes[i]);
        }
    }
}

ofxTLKeyframe* ofxTLStreamGraph::keyframeAtScreenpoint(ofVec2f p){
    if(bounds.inside(p.x, p.y)){
        for(int i = 0; i < keyframes.size(); i++){
            float offset = p.x - timeline->millisToScreenX(keyframes[i]->time);
            if (abs(offset) < 5) {
                return keyframes[i];
            }
        }
    }
    return NULL;
}


void ofxTLStreamGraph::willDeleteKeyframe(ofxTLKeyframe* keyframe){
    //do any cleanup before this keyframe gets hosed
}
