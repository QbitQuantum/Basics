bool CIntersectionAssistanceUnit::GetHighestScoringLastKnownGoodPosition( const QuatT& baseOrientation, QuatT& outQuat ) const
{
    bool bFlippedIsBest = false;

    if(!m_lastKnownGoodPositions.empty())
        {
            // Higher is better
            float fBestScore = 0.0f;
            int bestIndex = -1;
            Vec3 vBaseUpDir = baseOrientation.q.GetColumn2().GetNormalized();
            for(uint8 i = 0; i < m_lastKnownGoodPositions.size(); ++i)
                {
                    const QuatT& qLastKnownGood = m_lastKnownGoodPositions[i];
                    if(IsPositionWithinAcceptedLimits(qLastKnownGood.t, baseOrientation.t, kDistanceTolerance))
                        {
                            // Generate [0.0f,1.0f] score for distance
                            const Vec3 distVec = (qLastKnownGood.t - baseOrientation.t);

                            const float length = max(distVec.GetLengthFast(),0.0001f);
                            const float distanceScore = max(1.0f - (length * kInverseDistanceTolerance) * kDistanceWeight, 0.0f);

                            Vec3 vUpDir		 = qLastKnownGood.q.GetColumn2();

                            const float regularOrientationScore = vBaseUpDir.Dot(vUpDir);
                            const float flippedOrientationScore = vBaseUpDir.Dot(-vUpDir);

                            float orientationScore = max(regularOrientationScore, flippedOrientationScore);
                            orientationScore *= kOrientationWeight;

                            const float fCandidateScore = distanceScore + orientationScore;

#ifndef _RELEASE
                            if(g_pGameCVars->pl_pickAndThrow.intersectionAssistDebugEnabled == 2)
                                {
                                    CryWatch("[INDEX(%d)] : D[%.3f] O[%.3f] T[%.3f] (%s)", i, distanceScore, orientationScore, fCandidateScore, flippedOrientationScore > regularOrientationScore ? "*F*" : "R");
                                }
#endif //#ifndef _RELEASE

                            if(fCandidateScore > fBestScore)
                                {
                                    bestIndex	 = i;
                                    fBestScore = fCandidateScore;
                                    bFlippedIsBest = (flippedOrientationScore > regularOrientationScore);
                                }
                        }
                }

            if(bestIndex >= 0)
                {
                    outQuat = m_lastKnownGoodPositions[bestIndex];
                    if(bFlippedIsBest)
                        {
                            Matrix34 wMat(outQuat);
                            Vec3 vFlippedUpDir = -outQuat.q.GetColumn2().GetNormalized();
                            Vec3 vForwardDir	 = outQuat.q.GetColumn1().GetNormalized();
                            Vec3 vSideDir			 = -outQuat.q.GetColumn0().GetNormalized();
                            Matrix34 wFlippedMat;
                            wFlippedMat = Matrix34::CreateFromVectors(vSideDir, vForwardDir, vFlippedUpDir, wMat.GetTranslation());
                            outQuat = QuatT(wFlippedMat);

                            // Adjust pos (rotating around OOBB centre effectively)
                            const IEntity* pSubjectEntity = gEnv->pEntitySystem->GetEntity(m_subjectEntityId);
                            if(pSubjectEntity)
                                {
                                    AABB entAABB;
                                    OBB  entOBB;
                                    pSubjectEntity->GetLocalBounds(entAABB);
                                    entOBB.SetOBBfromAABB(Quat(IDENTITY), entAABB);

                                    Vec3 Centre = wMat.TransformPoint(entOBB.c);
                                    Vec3 toCentre = Centre - outQuat.t;
                                    outQuat.t += (toCentre * 2.0f);
                                }
                        }

#ifndef _RELEASE
                    if(g_pGameCVars->pl_pickAndThrow.intersectionAssistDebugEnabled == 2)
                        {
                            m_currentBestIndex = bestIndex;
                            CryWatch("[BEST INDEX] : %d", bestIndex);
                        }
#endif // ifndef _RELEASE

                    return true;
                }
        }

#ifndef _RELEASE
    m_currentBestIndex = -1;
#endif // ifndef _RELEASE

    return false;
}