void DelayEventProcessor()
{
    register int i, iSkillNum, iResult;
    DWORD dwTime = timeGetTime();
    int iTemp;
    Unit * unit = NULL;

    for (i = 0; i < MAXDELAYEVENTS; i++)
        if ((DelayEventList[i] != NULL) && (DelayEventList[i]->m_dwTriggerTime < dwTime)) {

            switch (DelayEventList[i]->m_iDelayType)
            {

            case DELAYEVENTTYPE_ANCIENT_TABLET:
                if ((DelayEventList[i]->m_pTarget->m_iStatus & STATUS_REDSLATE) != 0) {
                    iTemp = 1;
                }
                else if ((DelayEventList[i]->m_pTarget->m_iStatus & STATUS_BLUESLATE) != 0) {
                    iTemp = 3;
                }
                else if ((DelayEventList[i]->m_pTarget->m_iStatus & STATUS_GREENSLATE) != 0) {
                    iTemp = 4;
                }

                g_gameCopy->SendNotifyMsg(NULL, DelayEventList[i]->m_pTarget->m_handle, NOTIFY_SLATE_STATUS, iTemp, NULL, NULL, NULL);
                g_gameCopy->SetSlateFlag(DelayEventList[i]->m_pTarget->m_handle, iTemp, FALSE);
                break;

            case DELAYEVENTTYPE_CALCMETEORSTRIKEEFFECT:
                g_gameCopy->CalcMeteorStrikeEffectHandler(DelayEventList[i]->m_cMapIndex);
                break;

            case DELAYEVENTTYPE_DOMETEORSTRIKEDAMAGE:
                g_gameCopy->DoMeteorStrikeDamageHandler(DelayEventList[i]->m_cMapIndex);
                break;

            case DELAYEVENTTYPE_METEORSTRIKE:
                g_gameCopy->MeteorStrikeHandler(DelayEventList[i]->m_cMapIndex);
                break;

            case DELAYEVENTTYPE_USEITEM_SKILL:
            {
                if(DelayEventList[i]->m_pTarget->IsPlayer()) {
                    CClient *player = (CClient*) DelayEventList[i]->m_pTarget;
                    iSkillNum = DelayEventList[i]->m_iEffectType;

                    if ( player == NULL ) break;
                    if ( player->m_bSkillUsingStatus[iSkillNum] == FALSE ) break;
                    if ( player->m_iSkillUsingTimeID[iSkillNum] != DelayEventList[i]->m_iV2) break;

                    player->m_bSkillUsingStatus[iSkillNum] = FALSE;
                    player->m_iSkillUsingTimeID[iSkillNum] = NULL;

                    iResult = g_gameCopy->iCalculateUseSkillItemEffect(player->m_handle, OWNERTYPE_PLAYER,
                              DelayEventList[i]->m_iV1, iSkillNum, DelayEventList[i]->m_cMapIndex, DelayEventList[i]->m_dX, DelayEventList[i]->m_dY);

                    g_gameCopy->SendNotifyMsg(NULL, player->m_handle, NOTIFY_SKILLUSINGEND, iResult, NULL, NULL, NULL);
                }
            }
            break;
            case DELAYEVENTTYPE_KILL_ABADDON:
                g_gameCopy->NpcKilledHandler(DelayEventList[i]->m_pTarget->m_handle, OWNERTYPE_NPC, DelayEventList[i]->m_pTarget->m_handle, 0);
                break;

            case DELAYEVENTTYPE_END_APOCALYPSE:
                g_gameCopy->GlobalEndApocalypseMode(0);
                break;
            case DELAYEVENTTYPE_DAMAGEOBJECT:
                break;

            case DELAYEVENTTYPE_MAGICRELEASE:
                if(DelayEventList[i]->m_pTarget) {
                    DelayEventList[i]->m_pTarget->RemoveMagicEffect(DelayEventList[i]->m_iEffectType);
                }
                break;
            }

            delete DelayEventList[i];
            DelayEventList[i] = NULL;
        }
}