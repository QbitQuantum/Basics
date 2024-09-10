void ofxSimpleGuiToggle::draw(float x, float y) {
//	enabled = true;
	setPos(x, y);

	glPushMatrix();
	glTranslatef(x, y, 0);

	ofEnableAlphaBlending();
	ofFill();

	setTextBGColor();
	if(bLearning){ofSetColor(255,0,0);}
	else if(bLearnt){ofSetColor(0,255,0);}
	ofRect(0, 0, width, height);

	setFullColor(*value);
	ofRect(2, 2, height-4, height-4);

	if((*value)) {
		setTextColor();
		ofLine(2, 2, height-4, height-4);
		ofLine(height-4, 2, 2, height-4);
	}

	//setTextBGColor();
	//ofRect(height, 0, width - height, height);

	setTextColor();
	ofDrawBitmapString(name, height + 15, 12);
	ofDisableAlphaBlending();

	glPopMatrix();
}