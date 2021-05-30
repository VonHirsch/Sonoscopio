//
//  ofxTLStreamGraph.h
//  Sonoscopio
//
//  Created by Very Von on 5/29/21.
//

#pragma once

#include "ofMain.h"
#include "ofxTLKeyframes.h"

enum ofxTLStreamGraphType {
    OFXTL_StreamGraph_TYPE_BAR  = 0,
    OFXTL_StreamGraph_TYPE_LINE = 1,
};

//custom keyframe container
//inherits time and value from the super class
class ofxTLStreamGraphKey : public ofxTLKeyframe {
  public:
    //an example of how to add more information into this keyframe
    //just make some random colors
    ofxTLStreamGraphType type;
    float phaseShift; //in millis
    bool  phaseMatch;
    float amplitude;
    float frequency;
    float seed; // for noise
    float center; // 0 is middle
    float freqDeviation;
    bool interpolate;
    bool expInterpolate;
};

//Just a simple useless random color keyframer
//to show how to create a custom keyframer
class ofxTLStreamGraph : public ofxTLKeyframes {
  public:
    ofxTLStreamGraph();
    virtual ~ofxTLStreamGraph();

    //draw your keyframes
    //some default style is done before this
    virtual void draw();
    virtual void drawModalContent();
    //you can implement custom behavior here, but can get tricky
    //with when to call the super class.
    //see some of the other tracks for interesting patterns on how to
    //extend default interaction behavior
    virtual bool mousePressed(ofMouseEventArgs& args, long millis);
    virtual void mouseMoved(ofMouseEventArgs& args, long millis);
    virtual void mouseDragged(ofMouseEventArgs& args, long millis);
    virtual void mouseReleased(ofMouseEventArgs& args, long millis);
    
    //keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
    virtual void keyPressed(ofKeyEventArgs& args);
    
    //time range contains MIN and MAX time in milliseconds
    //valueRange is 0 at the bottom of the track, and 1 at the top
    //if you have anything other than small dots keyframes you'll want to override
    //the default behavior
    virtual void regionSelected(ofLongRange timeRange, ofRange valueRange);

    //return a custom name for this keyframe
    virtual string getTrackType();

  protected:
            
    virtual ofxTLKeyframe* keyframeAtScreenpoint(ofVec2f p);
    //always return the type for your track, in our case ofxTLEmptyKeyframe;
    //this will enusre that all keyframe objects passed to this class are of this type
    virtual ofxTLKeyframe* newKeyframe();
    
    //load this keyframe out of xml, which is alraedy pushed to the right level
    //only need to save custom properties that our subclass adds
    virtual void restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);
    //save custom properties into the xml
    virtual void storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);

    //responde to right clicks on keyframes
    virtual void selectedKeySecondaryClick(ofMouseEventArgs& args);
    
    //you can responde to a keyframe about to be killed with this function right before the parent class deletes it
    virtual void willDeleteKeyframe(ofxTLKeyframe* keyframe);

    int rectWidth;
    int rectHeight;
    bool drawingStreamGraphRect;
    ofRectangle StreamGraphRect;
    ofRectangle sineTypeRect;
    ofRectangle noiseTypeRect;
    ofRectangle phaseShiftRect;
    ofRectangle amplitudeRect;
    ofRectangle frequencyRect;
    ofRectangle seedRect;
    ofRectangle centerRect;
    ofRectangle interpolateRect;
    ofRectangle expInterpolateRect;
//    ofRectangle phaseMatchRect;
    ofRectangle* mouseDownRect;
    float* editingParam;
    float editingStartValue;
    ofRange editingRange;
    float editingSensitivity;
    float editingExponent;
    float editingClickX;
    bool draggedValue;
    
};
