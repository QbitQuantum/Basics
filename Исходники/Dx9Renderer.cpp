void C_Renderer::DrawText(IResource* font, const wchar_t* text, int dx, int dy, int dr, int db, unsigned int color, unsigned int style, float scale, int Drawonly)
{
	if(font==0) return;
#ifdef USE_BITMAPFONT
	Sprite* Font = CAST_RES(Sprite*, font);
	FontResource* rc = (FontResource*)font;
#else
	LPD3DXFONT Font = CAST_RES(LPD3DXFONT, font);
#endif

	if(Font==0) return;

#ifdef USE_BITMAPFONT
#else
	D3DXMatrixScaling(&mat, scale, scale, 1.0f);
	m_sprite->GetTransform(&m2);
	m_sprite->SetTransform(&(mat * m2));

	rect.left = (LONG)(dx/scale);
	rect.top = (LONG)(dy/scale);
	rect.right = (LONG)(dr/scale);
	rect.bottom = (LONG)(db/scale);
#endif


#ifdef USE_BITMAPFONT
	float sw = 0.0f;
	RectangleI* rct = 0;
	RectangleF rect;
	rect.left = (float)dx;
	rect.top = (float)dy;
	rect.right = (float)dr;
	rect.bottom = (float)db;

	unsigned int txtsize = wcslen(text);

	float fsize = (float)rc->GetSize();

	float fwidth = 0.0f;
	float fheight = 0.0f;
	for(unsigned int i=0; i<txtsize; i++)
	{
		rct = Font->GetSpriteRect((unsigned int)text[i]);

		if(rct!=0)
		{
			float scale2 = fsize / (rct->bottom - rct->top);
			fwidth += ((rct->right - rct->left - BFONTSPACEW) * scale2) * scale;
			fheight = ((rct->bottom - rct->top) * scale2) * scale;
		}
	}

	if(style&FONT_STYLE_MULTILINE)
	{
		rect.left -= BFONTSPACE;
		rect.right -= BFONTSPACE;
	}
	else
	{
		if(style&FONT_STYLE_CENTERALIGN)
		{
			float hfwidth = fwidth / 2.0f;
			float hwidth = (rect.right - rect.left) / 2.0f;
			rect.left = (rect.left + hwidth) - hfwidth - BFONTSPACEW;
			rect.right = rect.left + fwidth - BFONTSPACEW;
		}
		else if(style&FONT_STYLE_RIGHTALIGN)
		{
			rect.left = rect.right - fwidth - BFONTSPACE;
			rect.right = rect.left + fwidth - BFONTSPACE;
		}
		else
		{
			rect.left -= BFONTSPACE;
			rect.right = rect.left + fwidth - BFONTSPACE;
		}

	
		if(style&FONT_STYLE_VCENTERALIGN)
		{
			float hfheight = fheight / 2.0f;
			float hheight = (rect.bottom - rect.top) / 2.0f;
			rect.top = (rect.top + hheight) - hfheight;
			rect.bottom = rect.top + fheight;
		}
		else if(style&FONT_STYLE_BOTTOMALIGN)
		{
			rect.top = rect.bottom - fheight;
			rect.right = rect.top + fheight;
		}
		else
		{
			rect.bottom = rect.top + fheight;
		}
	}


	float ty = 0.0f;
	float tx = 0;

	for(unsigned int i=0; i<txtsize; i++)
	{
		rct = Font->GetSpriteRect((unsigned int)text[i]);

		if(rct!=0)
		{
			float scale2 = fsize / (rct->bottom - rct->top);
			if(style&FONT_STYLE_MULTILINE)
			{
				RectangleF rect2 = rect;
				rect2.left = rect.left + tx;
				rect2.right = (rect2.left + (rct->right - rct->left) * scale2  * scale);
				if(rect2.right>rect.right || text[i] == L'\n' || text[i] == L'\r')
				{
					ty += fsize * scale + BFONTVSPACE;
					tx = 0;

					rect2.left = rect.left + tx;
					rect2.right = (rect2.left + (rct->right - rct->left) * scale2  * scale);
				}

				rect2.top = rect.top + ty;
				rect2.bottom = (rect2.top + fsize * scale);

				if(!(text[i] == L'\n' || text[i] == L'\r'))
				{
					Font->SetIndex((unsigned int)text[i]);
					if(Drawonly==-1 || Drawonly==i) Font->Draw(this, rect2, color, 0.0f, 0.0f);
					tx += ((rct->right - rct->left - BFONTSPACEW) * scale2) * scale;
				}
			}
			else
			{
				rect.right = (rect.left + (rct->right - rct->left) * scale2  * scale);
				rect.bottom = (rect.top + fsize  * scale);
				Font->SetIndex((unsigned int)text[i]);
				if(Drawonly==-1 || Drawonly==i) Font->Draw(this, rect, color, 0.0f, 0.0f);
				rect.left += ((rct->right - rct->left - BFONTSPACEW) * scale2) * scale;
			}
		}
	}	
#else
	Font->DrawTextW(m_sprite, text, -1, (LPRECT)&rect, style, color);
	m_sprite->SetTransform(&m2);
#endif
}