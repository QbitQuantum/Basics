int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    int Status=false;									// Status Indicator
    IMAGE *TextureImage[3];					// Create Storage Space For The Textures

    if ((TextureImage[0]=ImageLoad("Data/Envwall.rgb")) &&// Load The Floor Texture
            (TextureImage[1]=ImageLoad("Data/Ball.rgb")) &&	// Load the Light Texture
            (TextureImage[2]=ImageLoad("Data/Envroll.rgb")))	// Load the Wall Texture
    {
        Status=true;									// Set The Status To true
        glGenTextures(3, &texture[0]);					// Create The Texture
        for (int loop=0; loop<3; loop++)				// Loop Through 5 Textures
        {
            glBindTexture(GL_TEXTURE_2D, texture[loop]);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        }
        for (int loop=0; loop<3; loop++)					// Loop Through 5 Textures
        {
            if (TextureImage[loop])						// If Texture Exists
            {
                if (TextureImage[loop]->data)			// If Texture Image Exists
                {
                    free(TextureImage[loop]->data);		// Free The Texture Image Memory
                }
                free(TextureImage[loop]);				// Free The Image Structure
            }
        }
    }
    return Status;										// Return The Status
}