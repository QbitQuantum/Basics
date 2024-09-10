void
nsLayoutHistoryState::RemoveState(const nsCString& aKey)
{
    mStates.Remove(aKey);
}