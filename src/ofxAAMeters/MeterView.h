/*
 * Copyright (C) 2016 Leo Zimmerman [http://www.leozimmerman.com.ar]
 *
 * Sonoscopio is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation (FSF), either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the Affero GNU General Public License
 * version 3 along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ExtendedDatGuiComponents.h"
#include "Macros.h"
#include "View.h"
//#include "ofxAudioAnalyzerAlgorithms.h"
#include "ofxAudioAnalyzerUnit.h"

class OnOffEventData{
public:
    //string name;
    ofxAAAlgorithmType type;
    bool state;
    int panelId;
};



//-:Meters Colors
//#define COLOR_MAIN_A ofColor::darkSeaGreen
//#define COLOR_MAIN_B ofColor::darkKhaki


#define COLOR_MAIN_A ofColor::paleTurquoise
#define COLOR_MAIN_B ofColor::paleGoldenRod

#define COLOR_PEAKS ofColor::crimson
#define COLOR_SMTH_LABEL ofColor::mediumOrchid

//#define COLOR_ONOFF_ON ofColor::chartreuse
#define COLOR_ONOFF_OFF ofColor::dimGray

#define COLOR_RECT_METER ofColor::white
#define COLOR_RECT_METER_ALPHA 40


class MeterView : public View {
public:
    
    MeterView(ofxAAAlgorithmType algorithmType, int panelId,  ofxAudioAnalyzerUnit * aaPtr);
    virtual ~MeterView();

    virtual void update();
    virtual void draw();

    void initDefaultValues();
    void initComponents();
    
    virtual void updateComponents();
    virtual void updateValues();
    virtual void updatePeak();
    
    void drawBounds();
    virtual void drawLabel();
    virtual void drawMeter();
    virtual void drawValueDisplay();
    
    virtual void resize(int x, int y, int w, int h);
    virtual void setComponentsPositions();
    virtual void setComponentsWidth();
    
    void resetPeak();
    
    string getName(){return _name;}
    ofColor getMainColor(){return _mainColor;}

    float getValue(){return _value;}
    int getPositionX(){return _x;}
    int getPositionY(){return _y;}
    int getWidth(){return _w;}
    int getHeight(){return _h;}
    float getMinEstimatedValue(){return _minEstimatedValue;}
    float getMaxEstimatedValue(){return _maxEstimatedValue;}
    
    float getSmoothAmnt(){return _smoothAmnt;}
    bool getEnabled(){return _enabled;}
    ofxAAAlgorithmType getType(){return _algorithmType;}
    
    void setMainColor(ofColor col);
    void setValue(float val);
    void setNormalizedValue(float val);
    void setMinEstimatedValue(float val){_minEstimatedValue = val;}
    void setMaxEstimatedValue(float val){_maxEstimatedValue = val;}
    void setSmoothAmnt(float val);
    void setEnabled(bool state);
    
    virtual void onSliderEvent(ofxDatGuiSliderEvent e);
    virtual void onButtonEvent(ofxDatGuiButtonEvent e);
    
    static ofEvent<OnOffEventData> onOffEventGlobal;//this is a shared event for all the instances of this class, so any instance of this class will broadcast to the same event,
    
    CustomSlider * smoothSlider;
    OnOffToggle* onOffToggle;
    PeakMeterButton* peakButton;
    
    //TODO: Esto aca?? 
    static MeterView* createMeterView(ofxAAAlgorithmType algorithmType, int panelId,  ofxAudioAnalyzerUnit * aaPtr);
    
    static int height;
    
    
protected:
    void adjustFontLetterSpacing(int width);
    
    ofxAudioAnalyzerUnit* _audioAnalyzer;
    ofxAAAlgorithmType _algorithmType;
    float _minEstimatedValue, _maxEstimatedValue;
    int _panelId; //for OnOff Event Listeners
    ofColor _mainColor;
    ofTrueTypeFont*	font;
    
    float _smoothAmnt;
    string  _name;
    bool    _enabled;
    float   _line_h;
    int     _label_x, _label_w;
    
private:
    float _value;
    float _valueNorm;
    float _maxValueRegistered;//peak
};
