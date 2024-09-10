void SimComponent::onRemove()
{
    _unregisterComponents();

    // Delete all components
    VectorPtr<SimComponent *>&componentList = lockComponentList();
    while(componentList.size() > 0)
    {
        SimComponent *c = componentList[0];
        componentList.erase( componentList.begin() );

        if( c->isProperlyAdded() )
            c->deleteObject();
        else if( !c->isRemoved() && !c->isDeleted() )
            delete c;
        // else, something else is deleting this, don't mess with it
    }
    unlockComponentList();

    Parent::onRemove();
}