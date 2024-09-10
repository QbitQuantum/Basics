void  MainEventLoopPass()
{
    EventRecord evt;
	Boolean		notHandled = true;

    if (!gDone)	 /* after cx switch back ensure not done */
    {
		if(WaitNextEvent(everyEvent, &evt, 1, gMouseRgn))
		{
			if (gMouseRgn)
				SetRectRgn(gMouseRgn, evt.where.h, evt.where.v, evt.where.h + 1, evt.where.v + 1);
					
			HandleNextEvent(&evt);
		}
	}
}