void ButcherView::DoChangedEvent(ButcherViewChangedEvent::change_t change, long movex, long movey)
{
    ButcherViewChangedEvent event(change);
    event.SetMove(movex, movey);
    event.SetEventObject(this);

    ProcessEvent(event);
}