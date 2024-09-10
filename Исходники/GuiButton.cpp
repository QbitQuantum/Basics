void GuiButton::hide()
{
	Display.drawRect(left,top,width,height,RGB(255,255,255));
    Display.fillRect(left+1,top+1,width-2,height-2,RGB(255,255,255));

}