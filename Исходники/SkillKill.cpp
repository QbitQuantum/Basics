bool SkillKill::IsGotYourBackKill(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer)
{
    //To use the new actor manager stuff when merged back to postalpha
    const float maxDistSq = sqr(g_pGameCVars->g_gotYourBackKill_targetDistFromFriendly);
    const float fovRange = cry_cosf(DEG2RAD(g_pGameCVars->g_gotYourBackKill_FOVRange));

    IActorIteratorPtr pActorIterator = g_pGame->GetIGameFramework()->GetIActorSystem()->CreateActorIterator();

    Vec3 targetLocation = pTargetPlayer->GetEntity()->GetWorldPos();
    SMovementState targetMovementState;
    pTargetPlayer->GetMovementController()->GetMovementState(targetMovementState);

    Vec3 targetAimDirection = targetMovementState.aimDirection;

    while(CActor* pActor = static_cast<CActor*>(pActorIterator->Next()))
        {
            if(pActor != pShooterPlayer && !pActor->IsDead() && pShooterPlayer->IsFriendlyEntity(pActor->GetEntityId()))
                {
                    Vec3 actorLocation = pActor->GetEntity()->GetWorldPos();
                    Vec3 distance = actorLocation - targetLocation;

                    if(distance.GetLengthSquared() < maxDistSq)
                        {
                            distance.Normalize();
                            if(distance.Dot(targetAimDirection) > fovRange)
                                {
                                    SMovementState actorMovementState;
                                    pActor->GetMovementController()->GetMovementState(actorMovementState);
                                    Vec3 actorAimDirection = actorMovementState.aimDirection;

                                    if(actorAimDirection.Dot(-distance) < fovRange)
                                        {
                                            return true;
                                        }
                                }
                        }
                }
        }

    return false;
}