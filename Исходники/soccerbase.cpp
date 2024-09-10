bool
SoccerBase::MoveAgent(shared_ptr<Transform> agent_aspect, const Vector3f& pos)
{
    Vector3f agentPos = agent_aspect->GetWorldTransform().Pos();

    shared_ptr<Transform> parent = shared_dynamic_cast<Transform>
            (agent_aspect->FindParentSupportingClass<Transform>().lock());

    if (parent.get() == 0)
    {
        agent_aspect->GetLog()->Error() << "(MoveAgent) ERROR: can't get parent node.\n";
        return false;
    }

    Leaf::TLeafList leafList;

    parent->ListChildrenSupportingClass<Body>(leafList, true);

    if (leafList.size() == 0)
    {
        agent_aspect->GetLog()->Error()
            << "(MoveAgent) ERROR: agent aspect doesn't have "
            << "children of type Body\n";

        return false;
    }

    Leaf::TLeafList::iterator iter = leafList.begin();

    // move all child bodies
    for (iter; iter != leafList.end(); ++iter)
    {
        shared_ptr<Body> childBody =
            shared_dynamic_cast<Body>(*iter);

        Vector3f childPos = childBody->GetPosition();

        childBody->SetPosition(pos + (childPos-agentPos));
        childBody->SetVelocity(Vector3f(0,0,0));
        childBody->SetAngularVelocity(Vector3f(0,0,0));
    }

    return true;
}