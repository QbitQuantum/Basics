    void ReplicatedStore::StateMachine::PostChangeRoleEvent(
        ::FABRIC_REPLICA_ROLE newRole, 
        StateMachineCallback const & callback,
        ComponentRootSPtr const & root)
    {
        ReplicatedStoreEvent::Enum event;
        switch (newRole)
        {
            case ::FABRIC_REPLICA_ROLE_PRIMARY:
                event = ReplicatedStoreEvent::ChangePrimary;
                break;

            case ::FABRIC_REPLICA_ROLE_IDLE_SECONDARY:
            case ::FABRIC_REPLICA_ROLE_ACTIVE_SECONDARY:
                event = ReplicatedStoreEvent::ChangeSecondary;
                break;

            default:
                Assert::CodingError(
                    "{0} unrecognized ::FABRIC_REPLICA_ROLE = {1}", 
                    this->TraceId, 
                    static_cast<int>(newRole));
        }

        Threadpool::Post([this, root, event, callback]{ ProcessEvent(event, callback); });
    }