DrawButton(int ButtonIndex)
{
	button_t *Button=&(ButtonArray[ButtonIndex]);
	
	Fill(Button->Status[Button->NoStatus].Color.r, Button->Status[Button->NoStatus].Color.g, Button->Status[Button->NoStatus].Color.b, 1);
	 Roundrect(Button->x,Button->y,Button->w,Button->h, Button->w/10, Button->w/10);
	Fill(255, 255, 255, 1);				   // White text
	TextMid(Button->x+Button->w/2, Button->y+Button->h/2, Button->Status[Button->NoStatus].Text, SerifTypeface, Button->w/strlen(Button->Status[Button->NoStatus].Text)/*25*/);	

}