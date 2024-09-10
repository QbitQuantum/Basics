ColladaTexture::ColladaTexture(FCDImage * _image)
{
	image = _image;
//
//	// Create an image container in DevIL.
//	ILuint imageId;
//
//	ilGenImages(1, &imageId);
//	ilBindImage(imageId);

	// do it square
	// reduce it if it is necessaryt
	// test this
	//GL_MAX_TEXTURE_SIZE.

	// initializate some variables
	hasOpacity = false;

	wchar_t orig[512];
	const size_t newsize = 256;
	char nstring[newsize];
#ifdef _WIN32
	// convert fstring to char*, amazing code based on http://msdn2.microsoft.com/en-us/library/ms235631(vs.80).aspx
	size_t convertedChars = 0;
	
	swprintf(orig, 512,L"%S", image->GetFilename().c_str() );
	size_t origsize = wcslen(orig) + 1;
	for(int i = 0; i < (int)origsize; ++i)
	{
		if(orig[i] == '\\')
		{
			orig[i] = '/';
		}
	}
	
	//wcstombs_s(&convertedChars, nstring, origsize, orig+2/*remove C:*/, _TRUNCATE);
	wcstombs_s(&convertedChars, nstring, origsize, orig, _TRUNCATE);
#else
	swprintf(orig, 512,L"%s", image->GetFilename().c_str() );
	const wchar_t * origTmp = &orig[0];
	wcsnrtombs( nstring, &origTmp, 512, 256, NULL);
#endif
	texturePathName =  nstring;
    
    TextureDescriptorUtils::CreateDescriptorIfNeed(String(texturePathName));
    
 	/*try 
	{
        std::vector<Magick::Image> layers;
		Magick::readImages(&layers, fileName);
		
		if (layers.size() != 1)
		{
			Logger::Error("Number of layers is wrong: %s", fileName.c_str());
		}
        
        Magick::Image & magickImage = layers[0];
        Magick::Geometry geo = magickImage.size();
        //magickImage.magick("RGBA");
		magickImage.modifyImage();
        
        bool opacityFound = false;
        if (magickImage.type() == Magick::TrueColorMatteType)
        {  
//        magickImage.type(Magick::TrueColorMatteType);
            Magick::PixelPacket *pixelCache = magickImage.getPixels(0, 0, geo.width(), geo.height());

            
            int32 height = geo.height();
            int32 width = geo.width();
            
            int32 size = sizeof(pixelCache[0].opacity);
            int32 opaqueValue = 255;
            if (size == 2)opaqueValue = 65535;
            
            for (int32 y = 0; y < height; ++y)
            {
                for (int32 x = 0; x < width; ++x)
                {
                    
                    if (pixelCache[y * width + x].opacity != opaqueValue)
                    {
                        opacityFound = true;
                        break;
                    }
                }
                if (opacityFound)break;
            }
        }
        Logger::FrameworkDebug("Image opened: %s - %d x %d - opacity: %s", fileName.c_str(), geo.width(), geo.height(), (opacityFound) ? ("yes"):("no"));
		
	}
	catch( Magick::Exception &error_ )
    {
        Logger::Error("Caught exception: %s file: %s", error_.what(), fileName.c_str());
		//std::cout << "Caught exception: " << error_.what() << " file: "<< psdPathname << std::endl;
    }*/
    
    
//	
//	wprintf(L"* added texture: %s", (wchar_t*)(image->GetFilename().c_str()));
//	printf(" name: %s\n", image->GetDaeId().c_str());
//
//	// Read in the image file into DevIL.
//	if (!ilLoadImage(nstring))	
//	{
//		wchar_t error_message[256];
//		swprintf(error_message, 256, L"This texture could not be opened: %s\n", (wchar_t*)(image->GetFilename().c_str()));
//		wprintf(error_message);
//		
//		ilDeleteImages(1, &imageId);
//		textureId = -1;
//	} else 
//	{
//		// resize if necessary
//		ProcessDevilImage();
//
//
//		// gl work
//		glGenTextures(1, &textureId); /* Texture name generation */
//		GLenum error;
//		if ((error = glGetError()) != GL_NO_ERROR)
//		{
//			printf("OpenGL Error: %x\n", error);
//		}
//
//		glBindTexture(GL_TEXTURE_2D, textureId); /* Binding of texture name */
//
//		// if 4 channels, the last one is the alpha channel
//		if (ilGetInteger(IL_IMAGE_CHANNELS) == 4) 
//			hasAlphaChannel = true;
//
//		// create mipmaps and upload texture to video card memory
//		gluBuild2DMipmaps
//		(
//			GL_TEXTURE_2D,
//			ilGetInteger(IL_IMAGE_CHANNELS),
//			ilGetInteger(IL_IMAGE_WIDTH),
//			ilGetInteger(IL_IMAGE_HEIGHT), 
//			ilGetInteger(IL_IMAGE_FORMAT), 
//			GL_UNSIGNED_BYTE,
//			ilGetData()
//		); 
//
//
//
//
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//
//		printf("texture size: %d x %d\n", ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
//
//		// release memory, now opengl have it !
//		ilDeleteImages(1, &imageId); 
//	}
	
}