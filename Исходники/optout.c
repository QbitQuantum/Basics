void showtotals()
{
char headstr[30];
char numstr1[30];
char numstr2[30];
char numstr3[30];
char endstring[30];
coltype col1,col2;
int x;
double y;

if (totalvalue >= 1.0e8 || totalvalue <= -1.0e8)
{
burp();
if (totalvalue > 0.0)
{
makewindow(10,5,60,19,"TOO RICH");
gotoxy(14,8);
cprintf("You are too Rich.");
gotoxy(14,10);
cprintf("This is a free society so you have a choice:");
gotoxy(14,12);
cprintf("1. Make a LARGE DONATION TO CHARITY.");
gotoxy(14,14);
cprintf("2. Buy an EXPENSIVE version of this program.");
gotoxy(14,16);
}
else
{
makewindow(10,5,60,19,"BANKRUPT !");
gotoxy(14,8);
cprintf("You are too Poor.");
gotoxy(14,10);
cprintf("This is a free society so you have a choice:");
gotoxy(14,12);
cprintf("1. Become a charity.");
gotoxy(14,14);
cprintf("2. Buy an EXPENSIVE version of this program.");
gotoxy(14,16);
}
cprintf("NOTE: We cannot guarantee values produced");
gotoxy(14,18);
cprintf("      when such large numbers are used.");
delay(6000);
closewindow(10,5,60,19);
totalvalue = 0.0;
}

switch (sys.screen)
{
case SCREEN1 :
		ltoa(totalputs,numstr3,10);
		ltoa(totalcalls,numstr2,10);
		col1 = HELDC;
		col2 = HELDP;
		if (sys.display == HELDS)
                {
		strcpy(headstr," Tot. Value $  ");
		sprintf(numstr1,"%-12.2f",totalvalue);
		strcpy(endstring," ");
		}
		else
		{
		strcpy(headstr," Tot. Delta    ");
		sprintf(numstr1,"%-12.2f",totaldelta);
		strcpy(endstring,"$/c");
		}
		break;


case SCREEN2 :  break;
case SCREEN3 : if (sys.display == INVVOL || sys.display == OVERVALUED)
		{
		strcpy(headstr," Weighted Vol. ");
		strcpy(endstring," \% ");
		sprintf(numstr1,"%-5.*f",2,weightedvol);
		sprintf(numstr2,"%-4.*f \%",2,weightedvolc);
		sprintf(numstr3,"%-4.*f \%",2,weightedvolp);
		col1 = VOLC;
		col2 = VOLP;
		}
		break;
}