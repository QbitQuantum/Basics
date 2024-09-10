void DragGestureRecognizer::produceDragGestureRecognized(ComponentRefPtr TheComponent, const Pnt2f &DragLocation) const
{
    const DragGestureEventUnrecPtr e = DragGestureEvent::create(TheComponent, getSystemTime(), DragLocation);
	DragGestureListenerSet Listeners(_DragGestureListeners);
    for(DragGestureListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->draqGestureRecognized(e);
    }
}