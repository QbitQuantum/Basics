void BarClass::refresh(void)
{
	Display.drawRect(_x_pos,_y_pos,_width,_height,border_color);
    if (0 != state)
    {
        Display.fillRect(_x_pos+1,_y_pos+1,_width-2,128-state,bg_color);
    }
    if (state < 128)
    {
        Display.fillRect(_x_pos+1,_y_pos+1+128-state,_width-2,state,fill_color);
    }
}