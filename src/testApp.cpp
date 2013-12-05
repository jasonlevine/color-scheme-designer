#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    primary.set(1.0, 0.0, 0.0);
    hue = saturation = brightness = 0.85;
    angle = 0.1;
    mode = 0;
    
    vector<string> names;
    names.push_back("mono");
    names.push_back("complement");
    names.push_back("triad");
    names.push_back("tetrad");
    names.push_back("analogic");
    names.push_back("accented");
    
    
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float dim = 32;
    float length = 320-xInit;
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    gui->addSlider("primary hue", 0.0, 1.0, &hue, length-xInit, dim);
    gui->addSlider("primary brightness", 0.0, 1.0, &brightness, length-xInit, dim);
    gui->addSlider("primary saturation", 0.0, 1.0, &saturation, length-xInit, dim);
    gui->addSlider("angle", 0.01, 0.25, &angle, length-xInit, dim);
    gui->addSlider("distance", 0.1, 0.5, &distance, length-xInit, dim);
    

    gui->addSpacer(length-xInit, 1);
    gui->addRadio("RADIO VERTICAL", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::update(){
    primary.setHsb(hue, saturation, brightness);
    
    ofFloatColor primaryHB, primaryHS, primaryLB, primaryLS;
    primaryHB = primaryHS = primaryLB = primaryLS = primary;
    
    primaryHB.setBrightness(primary.getBrightness() + distance);
    primaryLB.setBrightness(primary.getBrightness() - distance);
    primaryHS.setSaturation(primary.getSaturation() + distance);
    primaryLS.setSaturation(primary.getSaturation() - distance);
   
    primaries.clear();
    primaries.push_back(primary);
    primaries.push_back(primaryHB);
    primaries.push_back(primaryLB);
    primaries.push_back(primaryHS);
    primaries.push_back(primaryLS);
    
    if (mode == 1 || mode == 5) {
        
        
        ofFloatColor complement, complementHB, complementHS, complementLB, complementLS;
        complement = primary;
        float cHue = primary.getHue() - 0.5;
        if ( cHue < 0.0 ) cHue += 1.0;
        complement.setHue(cHue);
        complementHB = complementHS = complementLB = complementLS = complement;
        
        complementHB.setBrightness(complement.getBrightness() + distance);
        complementLB.setBrightness(complement.getBrightness() - distance);
        complementHS.setSaturation(complement.getSaturation() + distance);
        complementLS.setSaturation(complement.getSaturation() - distance);
        
        complements.clear();
        complements.push_back(complement);
        complements.push_back(complementHB);
        complements.push_back(complementLB);
        complements.push_back(complementHS);
        complements.push_back(complementLS);
    }

    if (mode == 2 || mode == 4 || mode == 5) {
        
        
        ofFloatColor second, secondHB, secondHS, secondLB, secondLS;
        ofFloatColor third, thirdHB, thirdHS, thirdLB, thirdLS;
        
        float mod = (mode == 2) ? 0.5 : 0.0;
        
        second = third = primary;
        float sHue = primary.getHue() - mod + angle;
        if ( sHue < 0.0 ) sHue += 1.0;
        second.setHue(sHue);
        
        float tHue = primary.getHue() - mod - angle;
        if ( tHue < 0.0 ) tHue += 1.0;
        third.setHue(tHue);
        
        secondHB = secondHS = secondLB = secondLS = second;
        
        secondHB.setBrightness(second.getBrightness() + distance);
        secondLB.setBrightness(second.getBrightness() - distance);
        secondHS.setSaturation(second.getSaturation() + distance);
        secondLS.setSaturation(second.getSaturation() - distance);
        
        seconds.clear();
        seconds.push_back(second);
        seconds.push_back(secondHB);
        seconds.push_back(secondLB);
        seconds.push_back(secondHS);
        seconds.push_back(secondLS);
        
        //thirds
        thirdHB = thirdHS = thirdLB = thirdLS = third;
        
        thirdHB.setBrightness(third.getBrightness() + distance);
        thirdLB.setBrightness(third.getBrightness() - distance);
        thirdHS.setSaturation(third.getSaturation() + distance);
        thirdLS.setSaturation(third.getSaturation() - distance);
        
        thirds.clear();
        thirds.push_back(third);
        thirds.push_back(thirdHB);
        thirds.push_back(thirdLB);
        thirds.push_back(thirdHS);
        thirds.push_back(thirdLS);
    }

    if (mode == 3) {
        ofFloatColor complement, complementHB, complementHS, complementLB, complementLS;
        complement = primary;
        float cHue = primary.getHue() - 0.5;
        if ( cHue < 0.0 ) cHue += 1.0;
        complement.setHue(cHue);
        complementHB = complementHS = complementLB = complementLS = complement;
        
        complementHB.setBrightness(complement.getBrightness() + distance);
        complementLB.setBrightness(complement.getBrightness() - distance);
        complementHS.setSaturation(complement.getSaturation() + distance);
        complementLS.setSaturation(complement.getSaturation() - distance);
        
        complements.clear();
        complements.push_back(complement);
        complements.push_back(complementHB);
        complements.push_back(complementLB);
        complements.push_back(complementHS);
        complements.push_back(complementLS);
        
        ofFloatColor second, secondHB, secondHS, secondLB, secondLS;
        ofFloatColor third, thirdHB, thirdHS, thirdLB, thirdLS;
        
        second = primary;
        float sHue = primary.getHue() + angle;
        if ( sHue > 1.0 ) sHue -= 1.0;
        second.setHue(sHue);
        
        third = complement;
        float tHue = complement.getHue() + angle;
        if ( tHue > 1.0 ) tHue -= 1.0;
        third.setHue(tHue);
        
        secondHB = secondHS = secondLB = secondLS = second;
        
        secondHB.setBrightness(second.getBrightness() + distance);
        secondLB.setBrightness(second.getBrightness() - distance);
        secondHS.setSaturation(second.getSaturation() + distance);
        secondLS.setSaturation(second.getSaturation() - distance);
        
        seconds.clear();
        seconds.push_back(second);
        seconds.push_back(secondHB);
        seconds.push_back(secondLB);
        seconds.push_back(secondHS);
        seconds.push_back(secondLS);
        
        //thirds
        thirdHB = thirdHS = thirdLB = thirdLS = third;
        
        thirdHB.setBrightness(third.getBrightness() + distance);
        thirdLB.setBrightness(third.getBrightness() - distance);
        thirdHS.setSaturation(third.getSaturation() + distance);
        thirdLS.setSaturation(third.getSaturation() - distance);
        
        thirds.clear();
        thirds.push_back(third);
        thirds.push_back(thirdHB);
        thirds.push_back(thirdLB);
        thirds.push_back(thirdHS);
        thirds.push_back(thirdLS);
    }

    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(primaries[0]);
    ofRect(420,0, 200, 100);
    
    ofSetColor(primaries[1]);
    ofRect(320,0, 100, 50);
    
    ofSetColor(primaries[2]);
    ofRect(620,50, 100, 50);
    
    ofSetColor(primaries[3]);
    ofRect(320,50, 100, 50);
    
    ofSetColor(primaries[4]);
    ofRect(620,0, 100, 50);
    
    if (mode == 1) {
        
        ofSetColor(complements[0]);
        ofRect(420,100, 200, 100);
        
        ofSetColor(complements[1]);
        ofRect(320,100, 100, 50);
        
        ofSetColor(complements[2]);
        ofRect(620,150, 100, 50);
        
        ofSetColor(complements[3]);
        ofRect(320,150, 100, 50);
        
        ofSetColor(complements[4]);
        ofRect(620,100, 100, 50);
        
    }
    
    if (mode == 2 || mode == 4 || mode == 5) {
        
        ofSetColor(seconds[0]);
        ofRect(420,100, 200, 100);
        
        ofSetColor(seconds[1]);
        ofRect(320,100, 100, 50);
        
        ofSetColor(seconds[2]);
        ofRect(620,150, 100, 50);
        
        ofSetColor(seconds[3]);
        ofRect(320,150, 100, 50);
        
        ofSetColor(seconds[4]);
        ofRect(620,100, 100, 50);
        
        ofSetColor(thirds[0]);
        ofRect(420,200, 200, 100);
        
        ofSetColor(thirds[1]);
        ofRect(320,200, 100, 50);
        
        ofSetColor(thirds[2]);
        ofRect(620,250, 100, 50);
        
        ofSetColor(thirds[3]);
        ofRect(320,250, 100, 50);
        
        ofSetColor(thirds[4]);
        ofRect(620,200, 100, 50);

        
    }
    
    
    if (mode == 3) {
        ofSetColor(seconds[0]);
        ofRect(420,100, 200, 100);
        
        ofSetColor(seconds[1]);
        ofRect(320,100, 100, 50);
        
        ofSetColor(seconds[2]);
        ofRect(620,150, 100, 50);
        
        ofSetColor(seconds[3]);
        ofRect(320,150, 100, 50);
        
        ofSetColor(seconds[4]);
        ofRect(620,100, 100, 50);
        
        
        ofSetColor(complements[0]);
        ofRect(420,200, 200, 100);
        
        ofSetColor(complements[1]);
        ofRect(320,200, 100, 50);
        
        ofSetColor(complements[2]);
        ofRect(620,250, 100, 50);
        
        ofSetColor(complements[3]);
        ofRect(320,250, 100, 50);
        
        ofSetColor(complements[4]);
        ofRect(620,200, 100, 50);
        
        
        
        ofSetColor(thirds[0]);
        ofRect(420,300, 200, 100);
        
        ofSetColor(thirds[1]);
        ofRect(320,300, 100, 50);
        
        ofSetColor(thirds[2]);
        ofRect(620,350, 100, 50);
        
        ofSetColor(thirds[3]);
        ofRect(320,350, 100, 50);
        
        ofSetColor(thirds[4]);
        ofRect(620,300, 100, 50);
        
        
    }

    if (mode == 5) {
        ofSetColor(complements[0]);
        ofRect(420,300, 200, 100);
        
        ofSetColor(complements[1]);
        ofRect(320,300, 100, 50);
        
        ofSetColor(complements[2]);
        ofRect(620,350, 100, 50);
        
        ofSetColor(complements[3]);
        ofRect(320,350, 100, 50);
        
        ofSetColor(complements[4]);
        ofRect(620,300, 100, 50);
    }

    

}

void testApp::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(kind == OFX_UI_WIDGET_TOGGLE)
    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        cout << name << "\t value: " << toggle->getValue() << endl;
        if (name == "mono") mode = 0;
        else if (name == "complement") mode = 1;
        else if (name == "triad") mode = 2;
        else if (name == "tetrad") mode = 3;
        else if (name == "analogic") mode = 4;
        else if (name == "accented") mode = 5;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
