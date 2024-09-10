void vis_lyrics_draw(HDC dc)
{
	vis_lyrics_timercall();

	if(vis_lyric_current_text_len && vis_lyric_current_action == 1)
	{
		int      bkmod;
		COLORREF col;
		RECT     rct;
		WINDOWPLACEMENT  wp;
		HFONT    oldfont;

		GetWindowPlacement(window_vis, &wp);

		GetClientRect(window_vis, &rct);

		bkmod = GetBkMode(dc);
		col = GetTextColor(dc);

		SetBkMode(dc, TRANSPARENT);


		if(wp.showCmd != SW_MAXIMIZE)
		{
			rct.top     = rct.bottom - 13 -  (vis_lyrics_font_size + 10) ;
			rct.bottom  -= 13;
			rct.left    =  20;
			rct.right   -= 28;
		}else{
			rct.top     = rct.bottom -  (vis_lyrics_font_size + 10) ;
		}

		//SetTextColor(dc, 0x0);
		//oldfont = (HFONT)SelectObject(dc, vis_lyric_font_b);
		//DrawText(dc, vis_lyric_current_text, vis_lyric_current_text_len, &rct, DT_CENTER | DT_END_ELLIPSIS | DT_VCENTER | DT_SINGLELINE);
		//SelectObject(dc, oldfont);

		rct.left    += 1;
		rct.right   += 1;

		SetTextColor(dc, 0xffffff);
		oldfont = (HFONT)SelectObject(dc, vis_lyric_font);
		DrawText(dc, vis_lyric_current_text, vis_lyric_current_text_len, &rct, DT_CENTER | DT_END_ELLIPSIS | DT_VCENTER | DT_SINGLELINE);
		SelectObject(dc, oldfont);



		SetBkMode(dc, bkmod);
		SetTextColor(dc, col);

		//vis_lyric_current_laction = vis_lyric_current_action;
		//vis_lyric_current_action = 0;
	}

	if(vis_lyric_current_action == 2)
	{
		RECT     rct;
		WINDOWPLACEMENT  wp;

		GetWindowPlacement(window_vis, &wp);


		GetClientRect(window_vis, &rct);

		if(wp.showCmd != SW_MAXIMIZE)
		{
			BitBlt(dc, 10, rct.bottom - 13 - 20, rct.right - (10 + 12), 20, 0, 0, 0, BLACKNESS);
		}else{
			BitBlt(dc, 0, rct.bottom - 20, rct.right, 20, 0, 0, 0, BLACKNESS);
		}

		vis_lyric_current_laction = vis_lyric_current_action;
		vis_lyric_current_action = 0;
	}
}