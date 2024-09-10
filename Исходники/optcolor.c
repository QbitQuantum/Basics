void showcell(int row,coltype col)
{
int back,fore,curs;
switch(row)
	{
	case 0 :
	case 1 :
	case 2 :
	case 3 :
	case 4 :
	case 5 :
	case 7 :
	case 9 :
	case 14 :
	case 15 :
	case 16 :
	case 17 :
	case 18 :
	case 19 :
	case 20 :
		 back = data[col][6];
		 fore = data[col][row];
		 curs = data[col][11];
		 break;
	case 6  :
	case 8  :
	case 10 :
	case 13 :
		 back = data[col][row];
		 fore = data[col][5];
		 curs = data[col][11];
		 break;
	case 11 :
	case 12 :
		 back = data[col][6];
		 fore = data[col][5];
		 curs = data[col][row];
		 break;
	}
gotoxy(row+2,40+col*8);
textcolor(fore);
textbackground(back);
setcursor(curs);
cputs("       ");
gotoxy(row+2,40+col*8);
}