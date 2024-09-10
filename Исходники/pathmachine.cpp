void PathMachine::tryExit(const Exit &possible, RoomRecipient &recipient, const bool out)
{
    for (auto idx : possible.getRange(out)) {
        emit lookingForRooms(recipient, idx);
    }
}