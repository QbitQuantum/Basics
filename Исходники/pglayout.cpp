void PG_Layout::GetParamRect(const char **Source, const char *What, PG_Rect& Rect, PG_Widget* parent) {
	char *c = PG_Layout::GetParamStr(Source,What);

	if(c == NULL) {
		return;
	}

	if(strlen(c) == 0) {
		return;
	}

	SDL_Surface *screen = PG_Application::GetScreen();
	char* parm;
	char *d;
	char tmp[16];
	int i=0;
	int mx;
	int r[4];

	r[0] = r[1] = r[2] = r[3] = 0;
	parm = strdup(c);

	for(d = strtok(parm,","); d != NULL; d = strtok(NULL,",")) {
		if(parent == NULL) {
			mx = ((i%2)==0) ? screen->w : screen->h;
		} else {
			mx = ((i%2)==0) ? parent->w : parent->h;
		}

		if(  sscanf(d, "%d%[%]", & r[i], tmp) == 2 )
			r[i] = (int)  ((float)r[i]*mx/100);

		if(r[i]<0)
			r[i] = mx+r[i];

		i++;
	}
	Rect.SetRect(r[0], r[1], r[2], r[3]);
	free(parm);
}