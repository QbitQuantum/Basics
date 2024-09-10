int kGUIFace::LoadFont(const char *filename,bool bold)
{
	int size,glyph_index;
	int advance;
	unsigned int c;
	unsigned long fontfilesize;

	m_haskerning=false;
	m_bold=bold;
	/* handle bigfile based fonts */
	m_memfile=kGUI::LoadFile(filename,&fontfilesize);
	assert(m_memfile!=0,"Couldn't find font!");

#if defined(WIN32) || defined(MINGW)
	//windows only, this is so that when printing, reports can use these fonts too!
	AddFontMemResourceEx(m_memfile, fontfilesize,0,&kGUIFont::m_numreg);
#elif defined(LINUX) || defined(MACINTOSH)
#else
#error
#endif

	if(FT_New_Memory_Face( kGUIFont::GetLibrary(),
							m_memfile,	/* first byte in memory */
							fontfilesize,	/* size in bytes */
							0,				/* face_index */
							GetFacePtr() ))
		return(-1);

	/* make a name for this font */
	if(!strcmp(m_ftface->style_name, "Regular"))
		m_name.Sprintf("%s", m_ftface->family_name);
    else
        m_name.Sprintf("%s %s",m_ftface->family_name, m_ftface->style_name);

	/* calculate pixel heights for different sizes of this font */
	for(size=1;size<=MAXFONTSIZE;++size)
	{
		kGUI::SelectFont(this,size);
		m_pixabove[size]=-1;
		m_pixbelow[size]=-1;

		/* pre-calculate character widths */
		if(size<=MAXQUICKSIZE)
		{
			for(c=0;c<MAXCCACHE;++c)
			{
				advance=0;
				glyph_index = FT_Get_Char_Index( m_ftface, c );
				if(glyph_index>0)
				{
					if(FT_Load_Glyph(m_ftface, glyph_index, FT_LOAD_DEFAULT)==0)
					{
						if(bold)
						{
							if(!FT_Render_Glyph( m_ftface->glyph, ft_render_mode_normal ))
								FT_GlyphSlot_Embolden(m_ftface->glyph);
						}
						advance=m_ftface->glyph->advance.x >> 6;
					}
				}
				m_quickwidths[size][c]=advance;
			}
		}
	}
	m_haskerning = FT_HAS_KERNING( m_ftface )!=0; 

	return(0);	/* ok */
}