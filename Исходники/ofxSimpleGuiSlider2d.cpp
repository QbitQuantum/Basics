void ofxSimpleGuiSlider2d::draw(float x, float y) {
	setPosition(x, y);
	ofPoint	pointv;
	pointv.x = ofMap((*value).x, min.x, max.x, x, x+width);
	pointv.y = ofMap((*value).y, min.y, max.y, y, y+height-config->slider2DTextHeight);
	
	ofEnableAlphaBlending();
	glPushMatrix();
	glTranslatef(x, y, 0);
	
	ofFill();
	setFullColor();
	ofRect(0, 0, width, height - config->slider2DTextHeight);
	
	ofFill();
	setTextBGColor();
	ofRect(0, height-config->slider2DTextHeight, width, config->slider2DTextHeight);
	
	setTextColor();
	ofDrawBitmapString(name+"\nx:"+ofToString(value->x, 2)+"\ny:"+ofToString(value->y, 2), 3, height+15-config->slider2DTextHeight);
	
	setTextColor();
	ofCircle(pointv.x-x, pointv.y-y, 2);
	
	setTextColor();
	ofLine(pointv.x-x, 0, pointv.x-x, height-config->slider2DTextHeight);
	ofLine(0, pointv.y-y,width, pointv.y-y);
	
	glPopMatrix();
	ofDisableAlphaBlending();
	
}