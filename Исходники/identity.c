/***************************************************************************
 *      input_string()
 * Read input from the user ... on the widget layer. 
 *********************************************************************PROTO*/
char *
input_string(SDL_Surface *screen, int x, int y, int opaque)
{
    int pos;
    char c;
    char retval[1024];
    SDL_Surface *text, *ctext;
    SDL_Color tc, cc;
    SDL_Rect rect;
    SDL_Event event;
    Uint32 text_color = int_input_color0;
    Uint32 cursor_color = int_input_color1;
    Uint32 our_black = opaque ? int_solid_black : int_black;

    memset(retval, 0, sizeof(retval));
    retval[0] = ' ';
    pos = 1;

    SDL_GetRGB(text_color, screen->format, &tc.r, &tc.g, &tc.b);
    SDL_GetRGB(cursor_color, screen->format, &cc.r, &cc.g, &cc.b);

    ctext = TTF_RenderText_Blended(font, "_", cc); Assert(ctext);

    while (1) {
	int changed = 0;	/* did they change the text string? */
	int blink = 1;		/* toggle the blinking the cursor */
	Uint32  flip_when = SDL_GetTicks();
	/* display the current string */

	text = TTF_RenderText_Blended(font, retval, tc); Assert(text);

	rect.x = x;
	rect.y = y;
	rect.w = text->w;
	rect.h = text->h;

	SDL_BlitSurface(text, NULL, widget_layer, &rect);
	/* OK to ignore the intervening flame layer */
	SDL_BlitSurface(text, NULL, screen, &rect);
	SDL_UpdateSafe(screen, 1, &rect);

	rect.x += rect.w;
	rect.w = ctext->w;
	rect.h = ctext->h;

	changed = 0;
	while (!changed) { 
	    if (SDL_GetTicks() > flip_when) {
		if (blink) {
		    SDL_BlitSurface(ctext, NULL, screen, &rect);
		    SDL_BlitSurface(ctext, NULL, widget_layer, &rect);
		} else {
		    SDL_FillRect(widget_layer, &rect, our_black);
		    SDL_FillRect(screen, &rect, our_black);
		    SDL_BlitSurface(flame_layer, &rect, screen, &rect);
		    SDL_BlitSurface(widget_layer, &rect, screen, &rect);
		}
		SDL_UpdateSafe(screen, 1, &rect);
		flip_when = SDL_GetTicks() + 400;
		blink = !blink;
	    }
	    if (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
		    changed = 1;
		    switch (event.key.keysym.sym) {
			case SDLK_RETURN:
			    return strdup(retval + 1);

			case SDLK_BACKSPACE:
			    if (pos > 1) pos--;
			    retval[pos] = 0;

			    rect.x = x;
			    rect.w = text->w + ctext->w;
			    SDL_FillRect(widget_layer, &rect, our_black);
			    SDL_FillRect(screen, &rect, our_black);
			    SDL_BlitSurface(flame_layer, &rect, screen, &rect);
			    SDL_BlitSurface(widget_layer, &rect, screen, &rect);
			    SDL_UpdateSafe(screen, 1, &rect);
			    break;

			default:
			    c = event.key.keysym.unicode;
			    if (c == 0) break;

			    SDL_FillRect(widget_layer, &rect, our_black);
			    SDL_FillRect(screen, &rect, our_black);
			    SDL_BlitSurface(flame_layer, &rect, screen, &rect);
			    SDL_BlitSurface(widget_layer, &rect, screen, &rect);
			    SDL_UpdateSafe(screen, 1, &rect);

			    if (isalpha(c) || isdigit(c) || isspace(c) || ispunct(c))
				retval[pos++] = c;
			    break;
		    }
		}
	    } else atris_run_flame();
	}
	SDL_FreeSurface(text);
    }
}