void		key_events(t_env *w)
{
	shape(w);
	move(w);
	choose_mode(w);
	if (w->inkeys[SDL_SCANCODE_MINUS])
		iteration_less(w);
	if (w->inkeys[SDL_SCANCODE_EQUALS])
		iteration_more(w);
	if (w->inkeys[SDL_SCANCODE_M])
		zoomin(w);
	if (w->inkeys[SDL_SCANCODE_N])
		zoomout(w);
	if (w->inkeys[SDL_SCANCODE_V])
		setcursor(w);
	if (w->inkeys[SDL_SCANCODE_P])
	{
		w->posx = 0;
		w->posy = 0;
	}
}