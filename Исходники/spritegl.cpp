void SpriteGL::buildGLTexture() {
    //Do not continue if the image isnt loaded
	if(!getBasicImage())
		return;

    destroyGLTexture();

    m_engineCreationTimestamp = 0;

    if(!g_running)
        return;

	//m_multiplierx = nextpow(this->getWidth()) / this->getWidth();
	//m_multipliery = nextpow(this->getHeight()) / this->getHeight();

	//Stretch(nextpow(this->getWidth()), nextpow(this->getHeight()), true);
	//printf("Stretch %p\n", this);
    printf(".");
	m_multiplierx = 1.;
	m_multipliery = 1.;


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    uint32_t rmask = 0xff000000;
    uint32_t gmask = 0x00ff0000;
    uint32_t bmask = 0x0000ff00;
    uint32_t amask = 0x000000ff;
#else
    uint32_t rmask = 0x000000ff;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x00ff0000;
    uint32_t amask = 0xff000000;
#endif


	
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_texture);
	
	/*
	std::stringstream sbmp;
	sbmp << "gl_debug_"<<m_texture<<".bmp";
	std::string fout = yatc_findfile(sbmp.str().c_str(),"w");
	SDL_SaveBMP(sfc,fout.c_str());
	*/
	
	char* pixels = getBasicImage()->lockSelf();
	
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GLint ret = gluBuild2DMipmaps(GL_TEXTURE_2D,
						GL_RGBA,
						getBasicImage()->getW(), getBasicImage()->getH(),
						(getPixelFormat() == GL_NONE ? (DEBUGPRINT(DEBUGPRINT_WARNING, DEBUGPRINT_LEVEL_OBLIGATORY, "[SpriteGL::SpriteGL] Invalid pixelformat\n"), GL_BGRA) : getPixelFormat()),
						GL_UNSIGNED_BYTE,
			 			pixels);

	if(ret != 0){
		DEBUGPRINT(DEBUGPRINT_ERROR, DEBUGPRINT_LEVEL_OBLIGATORY, "Error [SpriteGL::SpriteGL] Cant build 2DMipmaps: %s\n", gluErrorString(ret));
	}

	glDisable(GL_TEXTURE_2D);
	getBasicImage()->unlockSelf();
	
    m_engineCreationTimestamp = g_engine->m_creationTimestamp;
}