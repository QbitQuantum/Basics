    static void updateComponent (ComponentBuilder& builder, const ValueTree& state)
    {
        if (Component* topLevelComp = builder.getManagedComponent())
        {
            ComponentBuilder::TypeHandler* const type = builder.getHandlerForState (state);
            const String uid (getStateId (state));

            if (type == nullptr || uid.isEmpty())
            {
                // ..handle the case where a child of the actual state node has changed.
                if (state.getParent().isValid())
                    updateComponent (builder, state.getParent());
            }
            else
            {
                if (Component* const changedComp = findComponentWithID (*topLevelComp, uid))
                    type->updateComponentFromState (changedComp, state);
            }
        }
    }