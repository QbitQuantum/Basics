void Homework02App::keyDown(KeyEvent event)
{	
	//Handles if the user wishes to toggle the instructions on and off. 
	switch(event.getChar()) {
		case '?':
			if (toggleOn)
			{
			mFont = Font(mFont.getName(), mFont.getSize());
			mTextureFont = gl::TextureFont::create(mFont);
			toggleOn = false;
			}

			else if (toggleOn == false) 
			{
			tempFont = Font("", 0);
			mTextureFont = gl::TextureFont::create(tempFont);
			toggleOn = true;
			}
		break;
		
		// Handles if the user wishes to reverse the items 
		case 'R':
		case 'r':
			reverse(sentinel);
		break;

		case 'A':
		case 'a':
	
		break;
	}
}