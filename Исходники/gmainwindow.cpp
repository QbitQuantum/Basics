bool gMainWindow::doClose()
{
	if (_closing)
		return false;
	
	if (opened)
	{
		if (isModal() && !gApplication::hasLoop(this))
			return true;
		
		_closing = true;
		if (onClose) 
		{
			if (!onClose(this))
				opened = false;
		}
		else
			opened = false;
		_closing = false;
		
		if (!opened && isModal())
			gApplication::exitLoop(this);
  }
  
  if (!opened) // && !modal())
  {
		if (_active == this)
			setActiveWindow(NULL);
		
  	if (!isModal())
  	{
			if (persistent)
				hide();
			else
				destroy();
		}
		return false;
	}
	else
		return opened;
}