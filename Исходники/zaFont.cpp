int  zaFont::load_font(char * instr,int len)
{

		char * pin  = NULL;
		char * pout = NULL;
		char *p = NULL;

		char* inbuf = pin ; // m_filepos,  file head
		char* outbuf = pout;

		if (len==0)// utf8,
		{
			int ll= strlen(instr);
			size_t inbytesleft= ll+1;
			size_t outbytesleft = inbytesleft*2;

			pin = (char *)malloc(inbytesleft);
			pout = (char *)malloc(outbytesleft);

			inbuf = pin ; // m_filepos,  file head
			outbuf = pout;

			fprintf(stderr,"zaFont::load_font load begin length  %d\n",ll);
			strcpy(pin,instr);

			iconv_t tt;
			tt = iconv_open("UTF-16LE","UTF-8");
			int ret = iconv(tt,&inbuf,&inbytesleft,&outbuf,&outbytesleft);
			if ( ret < 0)
			{
				fprintf(stderr,"zaFont::load_font load error  errno %d\n",errno);
				throw CException(__FILE__,__LINE__,"zaFont::load_font convert error ,filename %s","NULL");
			}
			fprintf(stderr,"zaFont::load_font sucess.%d--%d:\n",ll*2,outbytesleft);
			iconv_close(tt);
			len = ll*2- outbytesleft;
			p= pout;
		}
		else
			p = instr;

			FT_Library library;
		    FT_Face face;
		    int c;
		    int i, j;
		    font_t* font = NULL;

		    if(FT_Init_FreeType(&library)) {
		        fprintf(stderr, "Error loading Freetype library\n");
		        return NULL;
		    }

		    if (FT_New_Face(library, m_path,0,&face)) {
		        fprintf(stderr, "Error loading font %s\n", m_path);
		        return NULL;
		    }

		    if(FT_Set_Char_Size ( face, m_size * 64, m_size * 64, m_dpi, m_dpi)) {
		        fprintf(stderr, "Error initializing character parameters\n");
		        return NULL;
		    }

		    unsigned int charcode = 0;

for (int cci =0 ; cci < len ; cci +=2)
{

charcode = ((unsigned char)*(p+1))*256+(unsigned char)*p ;
if (charcode == 601)
{
	charcode --;
	charcode ++;
}
if (this->m_map.find(charcode)==m_map.end())
{

		    font = (font_t*) malloc(sizeof(font_t));
		    font->initialized = 0;

		    glGenTextures(1, &(font->font_texture));

		    //Let each glyph reside in 32x32 section of the font texture
		    int segment_size_x = 0, segment_size_y = 0;
		    int num_segments_x = 1;//16
		    int num_segments_y = 1;//8

		    FT_GlyphSlot slot;
		    FT_Bitmap bmp;
		    int glyph_width, glyph_height;

		    //First calculate the max width and height of a character in a passed font
		    for(c = 0; c < 1; c++) {
		    	//
		        if(FT_Load_Char(face,0x4E2D+charcode-0x4E2D , FT_LOAD_RENDER)) {
		            fprintf(stderr, "FT_Load_Char failed\n");
		            free(font);
		            return NULL;
		        }

		        slot = face->glyph;
		        bmp = slot->bitmap;

		        //glyph_width = nextp2(bmp.width);
		        //glyph_height = nextp2(bmp.rows);

		        glyph_width = bmp.width;
		        glyph_height = bmp.rows;

		        if (glyph_width > segment_size_x) {
		            segment_size_x = glyph_width;
		        }

		        if (glyph_width > m_max_x)
		        	m_max_x = glyph_width;

		        if (glyph_height > segment_size_y) {
		            segment_size_y = glyph_height;
		        }

		        if (glyph_height > m_max_y)
		 		     m_max_y = glyph_height;
		    }

		    int font_tex_width = nextp2(num_segments_x * segment_size_x);
		    int font_tex_height = nextp2(num_segments_y * segment_size_y);

		    int bitmap_offset_x = 0, bitmap_offset_y = 0;

		    GLubyte* font_texture_data = (GLubyte*) malloc(sizeof(GLubyte) * 2 * font_tex_width * font_tex_height);
		    memset((void*)font_texture_data, 0, sizeof(GLubyte) * 2 * font_tex_width * font_tex_height);

		    if (!font_texture_data) {
		        fprintf(stderr, "Failed to allocate memory for font texture\n");
		        free(font);
		        return NULL;
		    }

		    // Fill font texture bitmap with individual bmp data and record appropriate size, texture coordinates and offsets for every glyph
		    for(c = 0; c < 1; c++)
		    {
		    	   if(FT_Load_Char(face,0x4E2D+charcode-0x4E2D , FT_LOAD_RENDER)) {
		            fprintf(stderr, "FT_Load_Char failed\n");
		            free(font);
		            return NULL;
		        }

		        slot = face->glyph;
		        bmp = slot->bitmap;

		        glyph_width = nextp2(bmp.width);
		        glyph_height = nextp2(bmp.rows);

		        div_t temp = div(c, num_segments_x);

		        bitmap_offset_x = segment_size_x * temp.rem;
		        bitmap_offset_y = segment_size_y * temp.quot;

		        for (j = 0; j < glyph_height; j++) {
		            for (i = 0; i < glyph_width; i++) {
		                font_texture_data[2 * ((bitmap_offset_x + i) + (j + bitmap_offset_y) * font_tex_width) + 0] =
		                font_texture_data[2 * ((bitmap_offset_x + i) + (j + bitmap_offset_y) * font_tex_width) + 1] =
		                    (i >= bmp.width || j >= bmp.rows)? 0 : bmp.buffer[i + bmp.width * j];
		            }
		        }

		        font->advance[c] = (float)(slot->advance.x >> 6);
		        font->tex_x1[c] = (float)bitmap_offset_x / (float) font_tex_width;
		        font->tex_x2[c] = (float)(bitmap_offset_x + bmp.width) / (float)font_tex_width;
		        font->tex_y1[c] = (float)bitmap_offset_y / (float) font_tex_height;
		        font->tex_y2[c] = (float)(bitmap_offset_y + bmp.rows) / (float)font_tex_height;
		        font->width[c] = bmp.width;
		        font->height[c] = bmp.rows;
		        font->offset_x[c] = (float)slot->bitmap_left;
		        font->offset_y[c] =  (float)((slot->metrics.horiBearingY-face->glyph->metrics.height) >> 6);
		    }


		    glBindTexture(GL_TEXTURE_2D, font->font_texture);
		    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, font_tex_width, font_tex_height, 0, GL_LUMINANCE_ALPHA , GL_UNSIGNED_BYTE, font_texture_data);

		  //  fprintf(stderr, "charcode %d %d\n",charcode, cci);
		    fflush(stderr);
		    free(font_texture_data);
		    font->initialized = 1;
m_map[charcode] = font;
}
p += 2;
}