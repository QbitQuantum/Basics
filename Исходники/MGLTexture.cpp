void MGLTexture::Load(char *name)
{  
	// make the texture name all lower case
	texturename = _strlwr(_strdup(name));

	// strip "'s
	if (strstr(texturename, "\""))
		texturename = strtok(texturename, "\"");

	// check the file extension to see what type of texture
	if(strstr(texturename, ".bmp"))	
		LoadBMP(texturename);
	if(strstr(texturename, ".tga"))	
		LoadTGA(texturename);
}