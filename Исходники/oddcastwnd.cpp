void OddcastWnd::timerCallback(int id)
{
  switch (id)
  {
	case myThirdTimer:
		if (reconnectServer()) {
			killTimer(myThirdTimer);
		}
	  break;
    case myTimer:  
      invalidate();
      break;

    default:
      ODDCASTWND_PARENT::timerCallback(id);
      break;
  };
}