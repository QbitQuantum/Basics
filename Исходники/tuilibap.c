char process_simpletext(tgui_Window *win, tgui_Obj *obj){

int ox, oy, x, maxx, bctr;
unsigned key;

char *buf = malloc (sizeof(char)*(obj->width+1));


    strcpy(buf, obj->data);


    ox = win->x1 + 1 + obj->x;
    oy = win->y1 + 2 + obj->y;
    x=ox;

	revers(0);
	cputsxy(x,oy, buf);
	revers(1);
	cputc(' ');
	revers(0);

	maxx=x+obj->width;
    x=x+strlen(buf);
    bctr=strlen(buf);
	gotoxy(x, oy);
	cursor(1);

	do {
		key = cgetc();
		//gotoxy(3,22); cprintf("%d",key);
		if (isalnum(key) || ispunct(key) || key==32) {
			if (x<=maxx){
				revers(0);
		        cputcxy(x,oy,key);
				buf[bctr]=key;
				++bctr;
				buf[bctr]='\0';
		        ++x;
				revers(1);
				cputc(' ');
				revers(0);

			}
		}
		if (key == CH_CURS_LEFT|| key == CH_DEL){
			if (x>ox) {

			    if (x<=maxx)cputcxy(x, oy, '_');
			    --bctr;
			    buf[bctr]='\0';
			    --x;
				gotoxy(x,oy);
				revers(1);
				cputc(' ');
				revers(0);
			}

		}

	} while (key!=CH_ENTER && key!=CH_F1 );

	cursor(0);

	if (key==CH_ENTER ) {
	    revers(0);
     	if (x<maxx) cputcxy(x,oy, ' ');

		strcpy(obj->data, buf);
	}

	//ESCAPE
	if (key==CH_F1) {
	   revers(1);
	   cputsxy(ox, oy, obj->data);
	}

	//textcolor(win->color);

	free(buf);
	return key;

} // end of process_simple_text