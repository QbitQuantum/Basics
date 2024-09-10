void CZMQNotificationInterface::BlockChecked(const CBlock& block, const CValidationState& state)
{
    if (state.IsInvalid()) {
        return;
    }

    for (std::list<CZMQAbstractNotifier*>::iterator i = notifiers.begin(); i!=notifiers.end(); )
    {
        CZMQAbstractNotifier *notifier = *i;
        if (notifier->NotifyBlock(block))
        {
            i++;
        }
        else
        {
            notifier->Shutdown();
            i = notifiers.erase(i);
        }
    }
}