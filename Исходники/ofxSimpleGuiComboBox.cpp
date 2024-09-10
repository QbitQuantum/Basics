void ofxSimpleGuiComboBox::draw(float x, float y) {
	//we assume a max of 256 characters.
	char choiceBuf[512];
	
	setPos(x, y);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	
	ofEnableAlphaBlending();
	ofFill();
	setTextBGColor();
	ofRect(0, 0, width, height);
	
	setTextColor();
//	sprintf(choiceBuf, "%s: %s", m_title, m_choices.size() ? m_choices[m_selectedChoice] : "(No Choices Available)");
	
	ofDrawBitmapString(m_title + " : " + (m_choices.size() ? m_choices[m_selectedChoice] : "N/A"), kSGCBTextPaddingX, kSGCBTextPaddingY);
	//draw a combobox down triangle icon so the users know to click
	ofTriangle(width - (kSGCBTriangleWidth + KSGCBTrianglePadding), kSGCBTextPaddingY/2,
			   width - (KSGCBTrianglePadding), kSGCBTextPaddingY/2,
			   width - (kSGCBTriangleWidth/2 + KSGCBTrianglePadding), kSGCBTextPaddingY);
	
	if ( ignoresXML() ){
		ofSetHexColor(config->noXmlColor);
		ofRect(width-config->noXmlBarWidth, 0, config->noXmlBarWidth, height);
	}

	if(m_hasFocus) {
		setCBTextBGColor();
		ofRect(0, height, width, config->comboBoxTextHeight * m_choices.size());
		setTextColor();
		ofLine(0, config->comboBoxHeight-1, width, config->comboBoxHeight-1);
		
		for(int i=0; i < m_choices.size(); i++) {
			setCBTextColor();
			//invert for selected choice
			float curY = height + i*config->comboBoxTextHeight; 
			if(i==m_mouseChoice){
				//draw a text colored rect so we can see the inverse
				ofRect(0, curY, width, config->comboBoxTextHeight);
				setCBTextBGColor();
			}
			
			ofDrawBitmapString(m_choices[i], kSGCBTextPaddingX, curY + kSGCBTextPaddingY);
		}
	}
	ofDisableAlphaBlending();
	
	glPopMatrix();
}