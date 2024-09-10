void TabletConnection::genSimpleEvent( Event::Type evtType ,Service::ServiceType servType , float x , float y)
{
    Event::Flags myFlag = (Event::Flags)0;
            
    if( ltClick ) myFlag = Event::Left;
    if( rtClick ) myFlag = Event::Right;
            
    myService->lockEvents();
    Event* evt = myService->writeHead();
	evt->reset(evtType, servType, getConnectionInfo().id);
    evt->setPosition( x , y );
    evt->setFlags(myFlag);
            
    myService->unlockEvents();
}