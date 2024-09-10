void ofxSimpleGuiTitle::draw(float x, float y) {
    setPos(x, y);

    if(hasTitle == false) return;

    glPushMatrix();
    glTranslatef(x, y, 0);

    ofEnableAlphaBlending();
    ofFill();
    //		setTextBGColor(value != NULL);
    //		ofSetHexColor(0, 0, 0);
    ofSetHexColor(config->fullActiveColor);
    if(config->rounded)
    {
        roundedRect(0, 0, width, height,config->rectRadius);
    }
    else
    {
        ofRect(0, 0, width, height);
    }

    // if a toggle
    if(value && (*value) && beToggle) {
        setTextColor();
        //ofLine(0, 0, box.width, box.height);
        //ofLine(box.width, 0, 0, box.height);
    }

    setTextColor(value != NULL);
    ofDrawBitmapString(name, 3, 15);

    ofDisableAlphaBlending();

    glPopMatrix();
}