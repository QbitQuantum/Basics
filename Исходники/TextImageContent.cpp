void TextImageContent::draw ( )
{
    ofSetColor ( 255 , 255 , 255 ) ;

    maskShader.begin();

	//our shader uses two textures, the top layer and the alpha
	//we can load two textures into a shader using the multi texture coordinate extensions
	glActiveTexture(GL_TEXTURE0_ARB);
	image.getTextureReference().bind();

	glActiveTexture(GL_TEXTURE1_ARB);
	mask.getTextureReference().bind();

	//draw a quad the size of the frame
	glBegin(GL_QUADS);
	ofFill() ;
	ofSetColor ( 255 , 255 , 255 , 255 ) ;

	float maskOffset = -scroll.y ; //15 - mouseY;	/*
	glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, maskOffset);
	glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
	glVertex2f( bounds.x, bounds.y );

	glMultiTexCoord2d(GL_TEXTURE0_ARB, image.getWidth(), maskOffset);
	glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), 0);
	glVertex2f( bounds.x + bounds.width , bounds.y );

	glMultiTexCoord2d(GL_TEXTURE0_ARB, image.getWidth(), mask.getHeight() + maskOffset );
	glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), mask.getHeight() );
	glVertex2f( bounds.x + bounds.width , bounds.y + bounds.height );

	glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, mask.getHeight() + maskOffset );
	glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, mask.getHeight() );
	glVertex2f( bounds.x , bounds.y + bounds.height );

	glEnd() ;

	//deactive and clean up
	glActiveTexture(GL_TEXTURE1_ARB);
	mask.getTextureReference().unbind();

	glActiveTexture(GL_TEXTURE0_ARB);
	image.getTextureReference().unbind();

    maskShader.end();

    //draw scrollbar indicator
    ofEnableAlphaBlending() ;
    ofSetColor ( 15 , 15 , 15 , 200 ) ;
    roundedRect ( bounds.x + bounds.width + 5 , bounds.y + (-scroll.y *.85) , 4 , 40 , 5 ) ;
}