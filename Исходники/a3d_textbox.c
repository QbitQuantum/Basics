static void a3d_textbox_reflow(a3d_widget_t* widget,
                               float w, float h)
{
	assert(widget);
	LOGD("debug w=%f, h=%f", w, h);

	a3d_textbox_t* self = (a3d_textbox_t*) widget;

	// reflow text when changes occur
	if((self->dirty  == 0) &&
	   (self->last_w == w) &&
	   (self->last_h == h))
	{
		return;
	}
	self->dirty  = 0;
	self->last_w = w;
	self->last_h = h;

	// determine maxi
	a3d_font_t* font   = a3d_screen_font(widget->screen);
	float       aspect = a3d_font_aspectRatio(font);
	float       size   = a3d_screen_layoutText(widget->screen,
	                                           self->style_text);
	int         maxi   = (int) (w/(aspect*size)) - 1;

	// maxi does not include null character
	// but max_len does
	// limit to max_len
	if((maxi >= self->max_len) ||
	   (maxi == 0))
	{
		maxi = self->max_len - 1;
	}

	// clear the text
	a3d_listbox_t*  listbox = (a3d_listbox_t*) self;
	a3d_listitem_t* iter    = a3d_list_head(listbox->list);
	while(iter)
	{
		a3d_text_t* text;
		text = (a3d_text_t*) a3d_list_remove(listbox->list, &iter);
		a3d_text_delete(&text);
	}

	// initialize parser
	char tok[256];
	char dst[256];
	int  srci = 0;
	int  toki = 0;
	int  dsti = 0;
	int  type = A3D_TOKEN_END;

	// reflow the string(s)
	iter = a3d_list_head(self->strings);
	while(iter)
	{
		const char* src = (const char*) a3d_list_peekitem(iter);

		srci = 0;
		type = getToken(src, tok, &srci, &toki);
		while(type != A3D_TOKEN_END)
		{
			if(type == A3D_TOKEN_BREAK)
			{
				if(dsti > 0)
				{
					a3d_textbox_printText(self, dst);
					a3d_textbox_printText(self, "");
				}
				else
				{
					a3d_textbox_printText(self, "");
				}
				dsti = 0;
				break;
			}

			if(dsti == 0)
			{
				strncpy(dst, tok, 256);
				dst[255] = '\0';
				dsti = toki;
			}
			else
			{
				if(dsti + toki + 1 <= maxi)
				{
					strcat(dst, " ");
					strcat(dst, tok);
					dst[255] = '\0';
					dsti += toki + 1;
				}
				else
				{
					a3d_textbox_printText(self, dst);

					strncpy(dst, tok, 256);
					dst[255] = '\0';
					dsti = toki;
				}
			}

			type = getToken(src, tok, &srci, &toki);
		}

		iter = a3d_list_next(iter);
	}

	if(dsti > 0)
	{
		a3d_textbox_printText(self, dst);
	}
}