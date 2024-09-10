QList<int> MythGenericTree::getRouteById()
{
    QList<int> routeByID;

    routeByID.push_front(getInt());

    MythGenericTree *parent = this;
    while( (parent = parent->getParent()) )
    {
        routeByID.push_front(parent->getInt());
    }
    return routeByID;
}