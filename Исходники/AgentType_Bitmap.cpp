//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//agenttype_bitmap_notify
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void agenttype_bitmap_notify(agent *a, int notifytype, void *messagedata)
{
	//Get the agent details
	agenttype_bitmap_details *details = (agenttype_bitmap_details *) a->agentdetails;

	styledrawinfo *di;
	int xpos, ypos;

	switch(notifytype)
	{
		case NOTIFY_DRAW:
			di = (styledrawinfo *) messagedata;

			if (details->is_icon)
			{
				HICON load_sysicon(char *filepath, int size);
				HICON hIcon = (HICON)LoadImage(plugin_instance_plugin, details->absolute_path, IMAGE_ICON, details->width, details->height, LR_LOADFROMFILE);
				// this one can retrieve the standard system icons also:
				if (NULL == hIcon) hIcon = load_sysicon(details->absolute_path, details->width);

				if (NULL != hIcon)
				{
					switch (details->halign)
					{
					case 0:
						xpos = ((di->rect.right - di->rect.left) / 2) - (details->width / 2);
						break;
					case 1:
						xpos = 2;
						break;
					case 2:
						xpos = (di->rect.right -  2) - (details->width);
						break;
					}
					switch (details->valign)
					{
					case 0:
						ypos = ((di->rect.bottom - di->rect.top) / 2) - (details->height / 2);
						break;
					case 1:
						ypos = 2;
						break;
					case 2:
						ypos = (di->rect.bottom - 2) - (details->height);
						break;
					}

					drawIcon (xpos, ypos, details->width, (HICON) hIcon, di->buffer, di->apply_sat_hue);
					//DrawIconEx(di->buffer, xpos, ypos, (HICON) hIcon, details->width, details->height, 0, NULL, DI_NORMAL);
					DestroyIcon(hIcon);
				}
			}
			else
			{
			  	WCHAR wTitle[256];
				if(!locale)
					locale = _create_locale(LC_CTYPE,"");
			  	_mbstowcs_l(wTitle, details->absolute_path, strlen(details->absolute_path) + 1,locale);
			  	pImage = new Gdiplus::Image(wTitle);

				if (NULL != pImage)
				{
					details->width = pImage->GetWidth() * ((double)details->scale / 100);
					details->height = pImage->GetHeight() * ((double)details->scale / 100);

					switch (details->halign)
					{
					case 0:
						xpos = ((di->rect.right - di->rect.left) / 2) - (details->width / 2);
						break;
					case 1:
						xpos = 2;
						break;
					case 2:
						xpos = (di->rect.right -  2) - (details->width);
						break;
					}
					switch (details->valign)
					{
					case 0:
						ypos = ((di->rect.bottom - di->rect.top) / 2) - (details->height / 2);
						break;
					case 1:
						ypos = 2;
						break;
					case 2:
						ypos = (di->rect.bottom - 2) - (details->height);
						break;
					}

					imageAttr = new Gdiplus::ImageAttributes();
					imageAttr->SetColorKey(RGB(255,0,255), RGB(255,0,255));

					graphics = new Gdiplus::Graphics(di->buffer);
					graphics->DrawImage(pImage, Gdiplus::Rect(xpos, ypos, details->width, details->height),
                                                            0, 0, pImage->GetWidth(), pImage->GetHeight(),
                                                            Gdiplus::UnitPixel, imageAttr, NULL, NULL);

					delete imageAttr;
					delete graphics;
					delete pImage;
				}
			}
			break;

		case NOTIFY_SAVE_AGENT:
			//Write existance
			config_write(config_get_control_setagent_c(a->controlptr, a->agentaction, a->agenttypeptr->agenttypename, details->filename));
			//Save properties
			if (details->is_icon) config_write(config_get_control_setagentprop_i(a->controlptr, a->agentaction, "Size", &details->width));
			else if (details->filename) config_write(config_get_control_setagentprop_i(a->controlptr, a->agentaction, "Scale", &details->scale));
			config_write(config_get_control_setagentprop_c(a->controlptr, a->agentaction, "VAlign", image_valigns[details->valign]));
			config_write(config_get_control_setagentprop_c(a->controlptr, a->agentaction, "HAlign", image_haligns[details->halign]));
			break;
	}
}