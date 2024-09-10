void proc()
{
	// 初始化&声明
	int l = strlen(str);
	int i, t, type;
	int basey = 0, yt = 0;
	int count = 0, start = 0;
	char tstr[500];
	tstr[0] = 0;
	proc_ret = SDL_CS(1, 1);
	SDL_FR(proc_ret);
	SDL_Surface *sf, *bkup, *f1, *f2;
	// start
	for (i = 0; i < l; i++)
	{
		switch (str[i])
		{
		case '+':
		case '-':
		case '*':
		case '/':
			if (tstr[0])
			{
				if (isDigit(tstr[0]))

					sf = TTF_RenderUTF8_Blended(fontBig, tstr, NUMCOLOR);
				else
					sf = TTF_RenderUTF8_Blended(fontBig, tstr, VARCOLOR);
				basey = _append(sf, basey, 0);
			}
			char tt[2];
			tt[0] = str[i];
			tt[1] = 0;
			sf = TTF_RenderUTF8_Blended(fontBig, tt, OPERCOLOR);
			basey = _append(sf, basey, 0);
			tstr[0] = 0;
			break;
		case '|':
			cursor = 1;
			break;
		case '_':
			if (str[++i] == 'p' && str[++i] == 'i')
			{
				sf = TTF_RenderUTF8_Blended(fontBig, "π", NUMCOLOR);
				basey = _append(sf, basey, 0);
			}
			break;
		case '(':
			start = i;
			bkup = proc_ret;
			for (;; i++)
			{
				if (str[i] == '(')
					count++;
				else if (str[i] == ')')
				{
					count--;
					if (!count)
					{
						break;
					}
				}
			}
			_proc(start + 1, i, 0, 1);
			SDL_Surface *bk2;
			bk2 = proc_ret;
			sf = TTF_RenderUTF8_Blended(fontSmall, "(", BRCOLOR);
			rDst.x = rDst.y = 0;
			rDst.w = sf->w;
			rDst.h = bk2->h;
			proc_ret = SDL_CS(bk2->w + 2 * sf->w, bk2->h);
			SDL_FillRect(proc_ret, NULL, BGCOLOR);
			SDL_BlitScaled(sf, NULL, proc_ret, &rDst);
			rDst.x = sf->w;
			SDL_FreeSurface(sf);
			rDst.y = 0;
			rDst.w = bk2->w;
			rDst.h = bk2->h;
			SDL_BlitSurface(bk2, NULL, proc_ret, &rDst);
			SDL_FreeSurface(bk2);
			sf = TTF_RenderUTF8_Blended(fontSmall, ")", BRCOLOR);
			rDst.x = proc_ret->w - sf->w;
			rDst.y = 0;
			rDst.w = sf->w;
			rDst.h = proc_ret->h;
			SDL_BlitScaled(sf, NULL, proc_ret, &rDst);
			SDL_FreeSurface(sf);
			sf = proc_ret;
			proc_ret = bkup;
			_append(sf, basey, 0);
			i++;
			break;
		case '{':
			// 初始化及备份
			{
				count = 0;
				start = i;
				if (tstr[0])
				{
					if (isDigit(tstr[0]))
						sf = TTF_RenderUTF8_Blended(fontBig, tstr, NUMCOLOR);
					else
						sf = TTF_RenderUTF8_Blended(fontBig, tstr, VARCOLOR);
					basey = _append(sf, basey, 0);
					tstr[0] = 0;
				}
				bkup = proc_ret;
				// start
				for (;; i++)
				{
					if (str[i] == '{')
						count++;
					else if (str[i] == '}')
					{
						count--;
						if (!count)
						{
							break;
						}
					}
				}
				if (str[++i] == '^')
					type = 1;
				else
					type = 2;
				_proc(start + 1, i - 1, type == 1 ? 0 : 1, 0);
				f1 = proc_ret;
				i++;
				start = i;
				count = 0;
				for (;; i++)
				{
					if (str[i] == '{')
						count++;
					else if (str[i] == '}')
					{
						count--;
						if (!count)
						{
							break;
						}
					}
				}
				_proc(start + 1, i, 1, 0);
				f2 = proc_ret;
				if (type == 1)
					yt = _draw_power(f1, f2, 0);
				else
					yt = _draw_frac(f1, f2, 0);
				f2 = proc_ret;
				proc_ret = bkup;
				basey = _append(f2, basey, yt);
			}
			break;
		default:
			t = strlen(tstr);
			tstr[t] = str[i];
			tstr[t + 1] = 0;
			break;
		}
	}
	if (tstr[0])
	{
		if (isDigit(tstr[0]))
			sf = TTF_RenderUTF8_Blended(fontBig, tstr, NUMCOLOR);
		else
			sf = TTF_RenderUTF8_Blended(fontBig, tstr, VARCOLOR);
		basey = _append(sf, basey, 0);
		tstr[0] = 0;
	}
}