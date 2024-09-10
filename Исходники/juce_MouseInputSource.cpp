void MouseInputSource::handleEvent (ComponentPeer* peer, const Point<int>& positionWithinPeer, const int64 time, const ModifierKeys& mods)
{
    pimpl->handleEvent (peer, positionWithinPeer, Time (time), mods.withOnlyMouseButtons());
}