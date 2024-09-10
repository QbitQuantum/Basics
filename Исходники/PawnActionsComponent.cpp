EPawnActionAbortState::Type UPawnActionsComponent::ForceAbortAction(UPawnAction& ActionToAbort)
{
    return ActionToAbort.Abort(EAIForceParam::Force);
}