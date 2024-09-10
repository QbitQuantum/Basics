WheelEventDispatchMediator::WheelEventDispatchMediator(const PlatformWheelEvent& event, PassRefPtr<AbstractView> view)
{
    if (!(event.deltaX() || event.deltaY()))
        return;

    setEvent(WheelEvent::create(FloatPoint(event.wheelTicksX(), event.wheelTicksY()), FloatPoint(event.deltaX(), event.deltaY()),
        deltaMode(event), view, event.globalPosition(), event.position(),
        event.ctrlKey(), event.altKey(), event.shiftKey(), event.metaKey(), event.directionInvertedFromDevice()));
}