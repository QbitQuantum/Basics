void ofxSimpleGuiButton::draw(float x, float y) {
	setPos(x, y);
	
	ofPushStyle();
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	
	ofEnableAlphaBlending();
	ofFill();
	setTextBGColor();
	ofRect(0, 0, width, height);
	
	// if a toggle
	if((*value) && beToggle) {
		setTextColor();
		//ofLine(0, 0, box.width, box.height);
		//ofLine(box.width, 0, 0, box.height);
	}
	
	setTextColor();
	ofDrawBitmapString(name, 3, 15);
	
	//ofDisableAlphaBlending();
	
	glPopMatrix();
	ofPopStyle();
}