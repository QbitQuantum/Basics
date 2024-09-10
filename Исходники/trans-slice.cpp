bool Asnap::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		control->select();
		case mouseNORMAL:
		case mouseLUP:
		cursor(cursorHANDSEL);
		focus(this);
		{
			if(getKeyboardState()&keyboardLALT)
			{
				if(defpos!=-1)
					set(defpos);
				else
					set(0);
				father->notify(this, nyCHANGE);
				return true;
			}
		}
		switch(event)
		{
			case mouseLDOWN:
			mouseCapture(true);
			return true;
			
			case mouseLUP:
			{
				int	xx=(x-X)/28;
				int	yy=(y-Y)/18;
				if((xx>=0)&&(xx<4)&&(yy>=0)&&(yy<4))
				{
					set(yy*4+xx);
					father->notify(this, nyCHANGE);
					repaint();
				}
				mouseCapture(false);
				return TRUE;
			}
			break;
		}
		break;
	}
	return FALSE;
}