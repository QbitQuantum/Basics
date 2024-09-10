//------------------------------------------------------------------------
void CParachute::Close(bool drop/*=false*/)
{
    // not used any more
    return;

    CryLog("Closing Parachute..");

    if (m_actorId)
    {
        IEntity* pEnt = m_pEntitySystem->GetEntity(m_actorId);
        if (pEnt && pEnt->GetParent()->GetId() == m_canvasId)
        {
            pEnt->DetachThis();
        }
        m_actorId = 0;
    }

    CActor* pActor = GetOwnerActor();
    if (pActor)
    {
        pActor->LinkToVehicle(0);
        if (IsOpened())
        {
            if (drop)
                pActor->DropItem(GetEntity()->GetId(), 1.0f, false);
        }
    }

    m_isOpened = false;
}