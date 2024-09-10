void EventDispatcherBase<TDerived>::leaveStatesInExitSet(event_type event)
{
    for (auto atomicState = derived().atomic_begin();
         atomicState != derived().atomic_end(); ++atomicState)
    {
        if (!(atomicState->m_flags & state_type::InExitSet))
            continue;

        state_type* state = &*atomicState;
        state_type* parent = state->parent();
        while (parent && (parent->m_flags & state_type::InExitSet))
        {
            if (parent->m_flags
                & (state_type::ShallowHistory | state_type::DeepHistory))
            {
                using history_state_type = ShallowHistoryState<TDerived>;
                history_state_type* historyState
                        = static_cast<history_state_type*>(parent);
                historyState->m_latestActiveChild = state;
            }
            state = parent;
            parent = state->parent();
        }
    }

    for (auto iter = derived().post_order_begin();
         iter != derived().post_order_end(); ++iter)
    {
        if (iter->m_flags & state_type::InExitSet)
        {
            derived().invokeStateExitCallback(&*iter);

            iter->m_flags &= ~state_type::StartInvoke;

            if (iter->m_flags & state_type::Invoked)
            {
                iter->m_flags &= ~state_type::Invoked;
                try
                {
                    iter->exitInvoke();
                }
                catch (...)
                {
                    derived().invokeStateExceptionCallbackOrThrow();
                }
            }

            iter->m_flags &= ~(state_type::Active | state_type::InExitSet);

            try
            {
                iter->onExit(event);
            }
            catch (...)
            {
                derived().invokeStateExceptionCallbackOrThrow();
            }
        }
    }
}