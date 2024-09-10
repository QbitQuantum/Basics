void kGUIText::DrawSectionRot(int sstart,int slen,float x,float y,float angle,kGUIColor color,float alpha)
{
	kGUIFace *face=kGUIFont::GetFace(GetFontID());
	int glyph_index;
	int font_height,font_above,font_below;
	FT_Face ftface;
	int size;
	FT_Glyph   glyph2;
	FT_Matrix  matrix;
	FT_BitmapGlyph  bit;
	float dx,dy,adv;
	float advsin,advcos;
	float fax,fay;	/* rotated font above */
	unsigned int ch;	/* current character */
	unsigned int nb;	/* number of bytes for current character */

	ftface=face->GetFace();
	size=GetFontSize();
	if(!size)
		return;
	assert(size>0,"Cannot print size 0\n");

	font_height=face->GetPixHeight(size);
	font_above = face->GetPixAscHeight(size);
	font_below = face->GetPixDescHeight(size);
	kGUI::SelectFont(face,size);

	matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
	matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
	matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
	matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

	adv=0;
	advsin=sin(angle);
	advcos=cos(angle);
	fax=sin(angle-(2*PI)*0.025f)*font_above;
	fay=-(cos(angle-(2*PI)*0.025f)*font_above);

	/* todo, handle underline */

	while(slen>0)
	{
		ch=GetChar(sstart,&nb);
		if(!ch)
			return;
		sstart+=nb;
		slen-=nb;

		/* todo, handle tabs, handle encoding  */
		glyph_index = FT_Get_Char_Index( ftface, ch );
		if(glyph_index>0)
		{
			FT_Load_Glyph(ftface,glyph_index,FT_LOAD_DEFAULT);
			FT_Get_Glyph( ftface->glyph, &glyph2 );
			FT_Glyph_Transform( glyph2, &matrix, 0 );
			FT_Glyph_To_Bitmap( &glyph2, ft_render_mode_normal,0, 1);
			
			/* draw to screen using writepixel */
			bit = (FT_BitmapGlyph)glyph2;

			dx=x+((advcos*adv)+fax);
			dy=y-((advsin*adv)+fay);
			DrawChar( (char *)bit->bitmap.buffer,
						dx + bit->left,
						dy -bit->top,
						bit->bitmap.width, bit->bitmap.rows,
						color,alpha);

			adv+=ftface->glyph->advance.x/64.0f;
			adv+=m_letterspacing;
			FT_Done_Glyph(glyph2);
		}
	}
	if(m_underline)
		kGUI::DrawLine(x+fax,y-fay,x+((advcos*adv)+fax),y-((advsin*adv)+fay),color,alpha);
}