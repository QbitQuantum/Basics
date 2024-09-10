void CMountedGunController::Update(EntityId mountedGunID, float frameTime)
{
    CRY_ASSERT_MESSAGE(m_pControlledPlayer, "Controlled player not initialized");

    CItem* pMountedGun = static_cast<CItem*>(gEnv->pGame->GetIGameFramework()->GetIItemSystem()->GetItem(mountedGunID));

    bool canUpdateMountedGun = (pMountedGun != NULL) && (pMountedGun->GetStats().mounted);

    if (canUpdateMountedGun)
        {
            IMovementController * pMovementController = m_pControlledPlayer->GetMovementController();
            assert(pMovementController);

            SMovementState info;
            pMovementController->GetMovementState(info);

            IEntity* pMountedGunEntity = pMountedGun->GetEntity();
            const Matrix34& lastMountedGunWorldTM = pMountedGunEntity->GetWorldTM();

            Vec3 desiredAimDirection = info.aimDirection.GetNormalized();

            // AI can switch directions too fast, prevent snapping
            if(!m_pControlledPlayer->IsPlayer())
                {
                    const Vec3 currentDir = lastMountedGunWorldTM.GetColumn1();
                    const float dot = clamp(currentDir.Dot(desiredAimDirection), -1.0f, 1.0f);
                    const float reqAngle = cry_acosf(dot);
                    const float maxRotSpeed = 2.0f;
                    const float maxAngle = frameTime * maxRotSpeed;
                    if(fabs(reqAngle) > maxAngle)
                        {
                            const Vec3 axis = currentDir.Cross(desiredAimDirection);
                            if(axis.GetLengthSquared() > 0.001f) // current dir and new dir are enough different
                                {
                                    desiredAimDirection = currentDir.GetRotated(axis.GetNormalized(),sgn(reqAngle)*maxAngle);
                                }
                        }
                }

            bool isUserClient = m_pControlledPlayer->IsClient();

            IEntity* pMountedGunParentEntity = pMountedGunEntity->GetParent();
            IVehicle *pVehicle = NULL;
            if(pMountedGunParentEntity && m_pControlledPlayer)
                pVehicle = m_pControlledPlayer->GetLinkedVehicle();

            CRecordingSystem* pRecordingSystem = g_pGame->GetRecordingSystem();

            //For client update always, for others only when there is notable change
            if (!pVehicle && (isUserClient || (!desiredAimDirection.IsEquivalent(lastMountedGunWorldTM.GetColumn1(), 0.003f))))
                {
                    Quat rotation = Quat::CreateRotationVDir(desiredAimDirection, 0.0f);
                    pMountedGunEntity->SetRotation(rotation);

                    if (isUserClient && pRecordingSystem)
                        {
                            // Only record the gun position if you're using the gun.
                            pRecordingSystem->OnMountedGunRotate(pMountedGunEntity, rotation);
                        }
                }

            const Vec3 vInitialAimDirection = GetMountDirection(pMountedGun, pMountedGunParentEntity);
            assert( vInitialAimDirection.IsUnit() );

            //Adjust gunner position and animations
            UpdateGunnerLocation(pMountedGun, pMountedGunParentEntity, vInitialAimDirection);

            const float aimrad = Ang3::CreateRadZ(Vec2(vInitialAimDirection),Vec2(-desiredAimDirection));
            const float pitchLimit = sin_tpl(DEG2RAD(30.0f));
            const float animHeight = fabs_tpl(clamp(desiredAimDirection.z * (float)__fres(pitchLimit), -1.0f, 1.0f));

            const float aimUp = (float)__fsel(-desiredAimDirection.z, 0.0f, animHeight);
            const float aimDown = (float)__fsel(desiredAimDirection.z, 0.0f, animHeight);

            if (pRecordingSystem)
                {
                    pRecordingSystem->OnMountedGunUpdate(m_pControlledPlayer, aimrad, aimUp, aimDown);
                }

            if(!m_pControlledPlayer->IsThirdPerson())
                {
                    UpdateFirstPersonAnimations(pMountedGun, desiredAimDirection);
                }

            if(m_pMovementAction)
                {
                    const float aimUpParam = aimUp;
                    const float aimDownParam = aimDown;
                    const float aimMovementParam = CalculateAnimationTime(aimrad);

                    m_pMovementAction->SetParam(MountedGunCRCs.aimUpParam, aimUpParam);
                    m_pMovementAction->SetParam(MountedGunCRCs.aimDownParam, aimDownParam);
                    m_pMovementAction->SetParam(MountedGunCRCs.aimMovementParam, aimMovementParam);
                }

            UpdateIKMounted(pMountedGun);
        }
}