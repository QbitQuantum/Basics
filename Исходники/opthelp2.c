int choosefunction()
{
char ch;
makewindow(11,7,68,13,"Function Keys");
window(13,8,67,12);
gotoxy(1,1);
cprintf("\nPress the function key that you require help with\n"
        "or any other key to return to the help menu");
window(1,1,80,25);
ch = getch();
closewindow(11,7,68,13);
if (ch != 0) return(0);
ch = getch();
return(ch);
}