GLuint TextureHandler::loadTexture(const std::string& strFilename)
{
  GLuint textureId=0;

  int i; 
  for (i = 0; i < (int) lookup.size(); i++)
  {
	if (lookup[i].first == strFilename)
		return lookup[i].second;
  }

  std::string::size_type dot_pos = strFilename.rfind('.');
  std::string suff = strFilename.substr(dot_pos+1);
  std::transform(suff.begin(), suff.end(), suff.begin(), tolower);
  if(suff == "raw")
  //if(stricmp(strrchr(strFilename.c_str(),'.'),".raw")==0)
  {

     // open the texture file
     std::ifstream file;
     file.open(strFilename.c_str(), std::ios::in | std::ios::binary);
     if(!file)
     {
		 Piavca::Error(_T("Texture file '") + StringToTString(strFilename) + _T("' not found."));
       return 0;
     }

     // load the dimension of the texture
     int width;
     file.read((char *)&width, 4);
     int height;
     file.read((char *)&height, 4);
     int depth;
     file.read((char *)&depth, 4);

     // allocate a temporary buffer to load the texture to
     unsigned char *pBuffer;
     pBuffer = new unsigned char[2 * width * height * depth];
     if(pBuffer == 0)
     {
	   Piavca::Error(_T("Memory allocation for texture '") + StringToTString(strFilename) + _T("' failed."));
       return 0;
     }

     // load the texture
     file.read((char *)pBuffer, width * height * depth);

     // explicitely close the file
     file.close();

     // flip texture around y-axis (-> opengl-style)
     int y;
     for(y = 0; y < height; y++)
     {
       memcpy(&pBuffer[(height + y) * width * depth], &pBuffer[(height - y - 1) * width * depth], width * depth);
     }
     
     // generate texture
     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

     glGenTextures(1, &textureId);
     glBindTexture(GL_TEXTURE_2D, textureId);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
	 glTexImage2D(GL_TEXTURE_2D, 0, (depth == 3) ? GL_RGB : GL_RGBA, width, height, 0, (depth == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, &pBuffer[width * height * depth]);
     // free the allocated memory

     delete [] pBuffer;  
  }
  //else if(stricmp(strrchr(strFilename.c_str(),'.'),".tga")==0)  
  else if(suff == "tga")
  {
	  CTga *Tga;
	  Tga = new CTga();
	  std::cout << "reading texture file" << strFilename << std::endl;
	  if(Tga->ReadFile(strFilename.c_str())==0)
	  {
		  Tga->Release();
		  return 0;
	  }
	  std::cout << "finished reading texture file" << strFilename << std::endl;

	  if(Tga->Bpp()!=32)
	  {
		  Tga->Release();
		  return 0;
	  }

     //Flip texture
     int width = Tga->GetSizeX();
     int height = Tga->GetSizeY();
     //int depth = Tga->Bpp() / 8;    

     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

     glGenTextures(1, &textureId);

     glBindTexture(GL_TEXTURE_2D, textureId);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
	 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA , GL_UNSIGNED_BYTE, (char*)Tga->GetPointer() );

	 Tga->Release();

  }
  if (textureId > 0)
  {
	  lookup.push_back(std::make_pair(strFilename, textureId));
  }
  return textureId;
}