void main(void)
{
   PASSWORD();           	//Identication ROUTING
   Dsta();               	//Splesh Screen
   SCAN();               	//Animation ROUTING for LOADING
   clrscr();             	//Clear the screen
   Window(1,1,80,25,LIGHTGRAY); //CREATE LIGHT GRAY screen
   status_bar();         	//CREAT Status Bar
   Window(1,1,80,23,1);  	//CREAT Foure Ground Window
   MAINMENU(1);          	//CALLING Mainmenu_ROUTING
}