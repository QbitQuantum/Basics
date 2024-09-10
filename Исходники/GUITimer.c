/*********************************************************************
*
*       GUI_TIMER_Restart
*/
void GUI_TIMER_Restart(GUI_TIMER_HANDLE hObj) {
  GUI_TIMER_Obj* pObj;
  GUI_LOCK();
  {
    if (hObj == 0) {
      hObj = _hActiveTimer;
    }
   	pObj = GUI_TIMER_H2P(hObj);
    pObj->t0 = GUI_GetTime() +pObj->Period;
		_Unlink(hObj);
		_Link(hObj);
  } GUI_UNLOCK(); 
}