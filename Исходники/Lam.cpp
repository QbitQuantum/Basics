//------------------------------------------------------------------
void CLam::AdjustLaserFPDirection(CItem* parent, Vec3 &dir, Vec3 &pos)
{
    pos = parent->GetSlotHelperPos(eIGS_FirstPerson,m_laserHelperFP.c_str(),true);
    Quat   lamRot = Quat(parent->GetSlotHelperRotation(eIGS_FirstPerson,m_laserHelperFP.c_str(),true));
    dir = -lamRot.GetColumn0();

    if(!m_lamparams.isLamRifle)
        dir = lamRot.GetColumn1();

    CActor *pActor = parent->GetOwnerActor();
    IMovementController * pMC = pActor ? pActor->GetMovementController() : NULL;
    if (pMC)
    {
        SMovementState info;
        pMC->GetMovementState(info);


        CWeapon* pWep = static_cast<CWeapon*>(parent->GetIWeapon());
        if(pWep && (pWep->IsReloading() || (!pActor->CanFire() && !pWep->IsZoomed())))
            return;

        if(dir.Dot(info.fireDirection)<0.985f)
            return;

        CCamera& camera = gEnv->pSystem->GetViewCamera();
        pos = camera.GetPosition();
        dir = camera.GetMatrix().GetColumn1();
        dir.Normalize();
    }
}