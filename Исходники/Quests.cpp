//LMA: exporting QSD Actions
void CWorldServer::ExportQSDDataA(byte* dataorg,int size,int opcode)
{
    char buffero[20];
    char buffera[20];
    char buffer[100];
    UINT itemtype=0;
    UINT itemnum=0;


    //Update quest
    if(opcode==0)
    {
        STR_REWD_000 * data = (STR_REWD_000 *)dataorg;

        //0 remove, 1 start, 2 replace quest keep items, 3 replace quest delete items, 4 select
        switch(data->btOp)
        {
            case 0:
            {
                sprintf(buffer,"delete");
            }
            break;
            case 1:
            {
                sprintf(buffer,"start");
            }
            break;
            case 2:
            {
                sprintf(buffer,"replace (keep items)");
            }
            break;
            case 3:
            {
                sprintf(buffer,"replace (delete items)");
            }
            break;
            case 4:
            {
                sprintf(buffer,"select");
            }
            break;
            default:
            {
                sprintf(buffer,"?%i?",data->btOp);
            }
            break;
        }

        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: %s quest %i (%s)",opcode,buffer,data->iQuestSN,GServer->GetSTLQuestByID(data->iQuestSN));


        return;
    }

    //Update quest items
    if(opcode==1)
    {
        STR_REWD_001 * data = (STR_REWD_001 *)dataorg;

        //0 remove, 1 start, 2 replace quest keep items, 3 replace quest delete items, 4 select
        switch(data->btOp)
        {
            case 0:
            {
                sprintf(buffer,"delete");
            }
            break;
            case 1:
            {
                sprintf(buffer,"add");
            }
            break;
            default:
            {
                sprintf(buffer,"?%i?",data->btOp);
            }
            break;
        }

        itemtype=gi(data->uiItemSN,0);
        itemnum=gi(data->uiItemSN,1);

        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: current quest: %s %i items %u (%i:%i, %s %s), (partyop %u)",opcode,buffer,data->nDupCNT,data->uiItemSN,itemtype,itemnum,GServer->GetSTLItemPrefix(itemtype,itemnum),GServer->GetSTLObjNameByID(itemtype,itemnum),data->btPartyOpt);


        return;
    }

    //Set quest variable
    if(opcode==2)
    {
        STR_REWD_002 * data = (STR_REWD_002 *)dataorg;

        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: set %i Quest Variables",opcode,data->iDataCnt);

        for(dword i = 0; i < data->iDataCnt; i++)
        {
            dword address = i * sizeof(STR_QUEST_DATA);
            address += (dword)dataorg;
            address += 4;
            STR_QUEST_DATA* curQst = (STR_QUEST_DATA*)address;
            LogSp(MSG_INFO,"\t\t\t\t\t\t |-> Set Quest Var[0x%04x (%u)][%i] %s %i",curQst->m_wVarTYPE,curQst->m_wVarTYPE,curQst->m_wVarNO,Operators(curQst->btOp,buffero),curQst->nValue);
        }


        return;
    }


    //Udapte Stats
    if(opcode==3)
    {
        STR_REWD_003 * data = (STR_REWD_003 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Update %i Stats",opcode,data->iDataCnt);

        for(dword i = 0; i < data->iDataCnt; i++)
        {
            dword address = i * 0x0C;
            address += (dword)dataorg;
            address += 4;
            STR_ABIL_DATA* curAbil = (STR_ABIL_DATA*)address;
            LogSp(MSG_INFO,"\t\t\t\t\t\t |-> Set Stat %s  %s %i",Abilities(curAbil->iType,buffera),Operators(curAbil->btOp,buffero),curAbil->iValue);
        }


        return;
    }

    //Set quest variable
    if(opcode==4)
    {
        STR_REWD_004 * data = (STR_REWD_004 *)dataorg;

        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: set %i Quest Variables",opcode,data->iDataCnt);

        for(dword i = 0; i < data->iDataCnt; i++)
        {
            dword address = i * sizeof(STR_QUEST_DATA);
            address += (dword)dataorg;
            address += 4;
            STR_QUEST_DATA* curQst = (STR_QUEST_DATA*)address;
            LogSp(MSG_INFO,"\t\t\t\t\t\t |-> Set Quest Var[0x%04x (%u)][%i] %s %i",curQst->m_wVarTYPE,curQst->m_wVarTYPE,curQst->m_wVarNO,Operators(curQst->btOp,buffero),curQst->nValue);
        }

        return;
    }

    //Give reward
    if(opcode==5)
    {
        STR_REWD_005 * data = (STR_REWD_005 *)dataorg;

        switch(data->btTarget)
        {
            case 0://EXP
                {
                    LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Give %u Exp, (partyop %u, itemopt %u, nPartyOpt %u)",opcode,data->iValue,data->btPartyOpt,data->nItemOpt,data->nPartyOpt);
                }
                break;
            case 1://Zuly
                {
                    LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Give %u Zuly, (partyop %u, itemopt %u, nPartyOpt %u)",opcode,data->iValue,data->btPartyOpt,data->nItemOpt,data->nPartyOpt);
                }
                break;
            case 2://Item
                {
                    CItem nItem;
                    itemtype=gi(data->iItemSN,0);
                    itemnum=gi(data->iItemSN,1);

                    nItem.itemtype = itemtype;
                    nItem.itemnum = itemnum;

                    if(nItem.IsStackable())
                    {
                        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Give %i (+formula()) item %u (%i:%i, %s %s), (partyop %u, itemopt %u, nPartyOpt %u)",opcode,data->iValue,data->iItemSN,nItem.itemtype,nItem.itemnum,GServer->GetSTLItemPrefix(itemtype,itemnum),GServer->GetSTLObjNameByID(nItem.itemtype,nItem.itemnum),data->btPartyOpt,data->nItemOpt,data->nPartyOpt);
                    }
                    else
                    {
                        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Give 1 item %u (%i:%i, %s %s), (partyop %u, itemopt %u, nPartyOpt %u)",opcode,data->iItemSN,nItem.itemtype,nItem.itemnum,GServer->GetSTLItemPrefix(itemtype,itemnum),GServer->GetSTLObjNameByID(nItem.itemtype,nItem.itemnum),data->btPartyOpt,data->nItemOpt,data->nPartyOpt);
                    }

                }
                break;
            default:
            {
                LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Give Unknown reward %i, item %u, count / value %u, (partyop %u, itemopt %u, nPartyOpt %u)",opcode,data->btTarget,data->iItemSN,data->iValue,data->btPartyOpt,data->nItemOpt,data->nPartyOpt);
            }
            break;

        }

        return;
    }

    //restore HP / MP
    if(opcode==6)
    {
        STR_REWD_006 * data = (STR_REWD_006 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Restore %i%% HP, %i%% MP (partyop %u)",opcode,data->iPercentOfHP, data->iPercentOfMP,data->btPartyOpt);
        return;
    }

    //teleport
    if(opcode==7)
    {
        STR_REWD_007 * data = (STR_REWD_007 *)dataorg;
        if(data->btPartyOpt!=0)
        {
            LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Teleport to map %i (%s) at (%.2f,%.2f), with party members. (partyop %u)",opcode,data->iZoneSN,GServer->GetSTLZoneNameByID(data->iZoneSN),(float)(data->iX/100),(float)(data->iY/100),data->btPartyOpt);
        }
        else
        {
            LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Teleport to map %i (%s) at (%.2f,%.2f), (partyop %u)",opcode,data->iZoneSN,GServer->GetSTLZoneNameByID(data->iZoneSN),(float)(data->iX/100),(float)(data->iY/100),data->btPartyOpt);
        }

        return;
    }

    //Spawn monster
    if(opcode==8)
    {
        STR_REWD_008 * data = (STR_REWD_008 *)dataorg;

        if(data->iX==0||data->iY==0||data->iZoneSN==0)
        {
            LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Spawn %i monsters %i (%s) near me (team %i), (btwho)",opcode,data->iHowMany,data->iMonsterSN,GServer->GetSTLMonsterNameByID(data->iMonsterSN),data->iTeamNo,data->btWho);
        }
        else
        {
            LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Spawn %i monsters %i (%s) to map %i (%s) at (%.2f,%.2f) (team %i), (btwho %u)",opcode,data->iHowMany,data->iMonsterSN,GServer->GetSTLMonsterNameByID(data->iMonsterSN),data->iZoneSN,GServer->GetSTLZoneNameByID(data->iZoneSN),(float)(data->iX/100),(float)(data->iY/100),data->iTeamNo,data->btWho);
        }

        return;
    }

    //Execute Quest Trigger
    if(opcode==9)
    {
        STR_REWD_009 * data = (STR_REWD_009 *)dataorg;
        char* tempName = reinterpret_cast<char*>(&data->szNextTriggerSN) - 2;
        dword hash = MakeStrHash(tempName);
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Execute Quest Trigger %s (%u)",opcode,tempName,hash);
        return;
    }

    //Reset Stats.
    if(opcode==10)
    {
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Reset Stats to default values",opcode);
        return;
    }

    //Update Object Var..
    if(opcode==11)
    {
        STR_REWD_011 * data = (STR_REWD_011 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Update variable",opcode);
        if(data->btWho==0)
        {
            LogSp(MSG_INFO,"\t\t\t\t\t\t |-> Update ObjVar[%i] %s %i, who=%i (NPC)",data->nVarNo,Operators(data->btOp,buffero),data->iValue,data->btWho);
        }
        else if (data->btWho==1)
        {
            LogSp(MSG_INFO,"\t\t\t\t\t\t |-> Update ObjVar[%i] %s %i, who=%i (Event Object)",data->nVarNo,Operators(data->btOp,buffero),data->iValue,data->btWho);
        }
        else
        {
            LogSp(MSG_INFO,"\t\t\t\t\t\t |-> Update ObjVar[%i] %s %i, who=?(%i)?",data->nVarNo,Operators(data->btOp,buffero),data->iValue,data->btWho);
        }


        return;
    }

    //NPC Speak...
    if(opcode==12)
    {
        //Log(MSG_INFO, "NPC trying to speak");

        STR_REWD_012 * data = (STR_REWD_012 *)dataorg;
        //Log(MSG_INFO,"\t\t\t\t\t ACT %.3i: NPC Speak (NOT CODED for Client) (CODED for Monsters / NPC)",opcode);

        if(data->btMsgType == 1)
        {
            //Log(MSG_INFO,"\t\t\t\t\t\t |-> NPC Shouts LTB string %i, %s",data->iStrID,GServer->LtbstringQSD[data->iStrID]->LTBstring);
        }
        else if(data->btMsgType == 2)
        {
            //Log(MSG_INFO,"\t\t\t\t\t\t |-> NPC Announces LTB string %i, %s",data->iStrID,GServer->LtbstringQSD[data->iStrID]->LTBstring);
        }
        else
        {
            //Log(MSG_INFO,"\t\t\t\t\t\t |-> NPC ?(%i)? LTB string %i, %s",data->btMsgType,data->iStrID,GServer->LtbstringQSD[data->iStrID]->LTBstring);
        }


        return;
    }

    //Unknown (execute quest trigger?)
    if(opcode==13)
    {
        STR_REWD_013 * data = (STR_REWD_013 *)dataorg;
        char* tempName = reinterpret_cast<char*>(&data->szTriggerName) - 2;
        dword hash = MakeStrHash(tempName);
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Execute Quest Trigger %s (%u) (who %u, isec %u, nexttrigger %u)",opcode,tempName,hash,data->btWho,data->iSec,data->m_HashNextTrigger);

        return;
    }

    //Learn Skill
    if(opcode==14)
    {
        STR_REWD_014 * data = (STR_REWD_014 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Learn Skill %i (%s), (op %u)",opcode,data->iSkillNo,GServer->GetSTLSkillByID(data->iSkillNo),data->btOp);
        return;
    }

    //Set Quest Flag
    if(opcode==15)
    {
        STR_REWD_015 * data = (STR_REWD_015 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Set Quest Flag[%u]=%i",opcode,data->nSN,data->btOp);
        return;
    }

    //Unknown...
    if(opcode==16)
    {
        STR_REWD_016 * data = (STR_REWD_016 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Unknown (NOT CODED), (op %u)",opcode,data->nGroupSN);
        return;
    }

    //reset all quest flags...
    if(opcode==17)
    {
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Reset All Quest Flags",opcode);
        return;
    }

    //Send Announcment...
    if(opcode==18)
    {
        STR_REWD_018 * data = (STR_REWD_018 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Send Announcment (NOT CODED), (strid %u, ncnt %u)",opcode,data->iStrID,data->nCnt);
        return;
    }

    //Execute Quest Trigger in Other Map...
    if(opcode==19)
    {
        STR_REWD_019 * data = (STR_REWD_019 *)dataorg;
        char* tempName = reinterpret_cast<char*>(&data->TriggerName) - 2;
        dword hash = MakeStrHash(tempName);
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Execute Quest %s (hash %u) in Other Map %i (%s) for team %i (NOT CODED for Client) (CODED for Monsters / NPC), (triggerlength %u)",opcode,tempName,hash,data->nZoneNo,GServer->GetSTLZoneNameByID(data->nZoneNo),data->nTeamNo,data->nTriggerLength);
        return;
    }

    //PvP Status...
    if(opcode==20)
    {
        STR_REWD_020 * data = (STR_REWD_020 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: PvP Status set to %i (for maps mainly) (CODED FOR PLAYERS)",opcode,data->btNoType);
        return;
    }

    //Set Respawn Position...
    if(opcode==21)
    {
        STR_REWD_021 * data = (STR_REWD_021 *)dataorg;
        float X=(float)(data->iX)/((float)100);
        float Y=(float)(data->iY)/((float)100);
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Set Respawn Position to current map [%.2f;%.2f].",opcode,X,Y);
        return;
    }

    //Unknown...
    if(opcode==22)
    {
        STR_REWD_022 * data = (STR_REWD_022 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Unknown (NOT CODED), (op %u)",opcode,data->btOp);
        return;
    }

    //Raise Clan Grade
    if(opcode==23)
    {
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Raise clan grade (+1) (NOT FULLY CODED) ",opcode);
        return;
    }

    //Clan Money...
    if(opcode==24)
    {
        STR_REWD_024 * data = (STR_REWD_024 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Clan Money btop=%i, money %i (NOT CODED)",opcode,data->btOP,data->iMONEY);
        return;
    }

    //Clan Points...
    if(opcode==25)
    {
        STR_REWD_025 * data = (STR_REWD_025 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Clan Points %s %i",opcode,Operators(data->btOP,buffero),data->nPOINT);
        return;
    }

    //Clan Skill...
    if(opcode==26)
    {
        STR_REWD_026 * data = (STR_REWD_026 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Clan Skill (NOT CODED), (skill %u,op %u)",opcode,data->nSkillNo,data->btOP);
        return;
    }

    //Clan Contribution...
    if(opcode==27)
    {
        STR_REWD_027 * data = (STR_REWD_027 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Clan Contribution (NOT CODED), (cont %u,op %u)",opcode,data->nCONT,data->btOP);
        return;
    }

    //Clan teleport
    if(opcode==28)
    {
        STR_REWD_028 * data = (STR_REWD_028 *)dataorg;

        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Teleport all me and my clan members to map %i at (%.2f,%.2f) random range %i ",opcode,data->nZoneNo,(float)(data->iX/100),(float)(data->iY/100),data->iRange);
        return;
    }

    //LMA: Lua?
    if(opcode==29)
    {
        STR_REWD_029 * data = (STR_REWD_029 *)dataorg;
        char* tempName = reinterpret_cast<char*>(&data->luaName)-2;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: execute Lua %s (luaLen=%u) (NOT CODED, CLIENT SIDE ONLY?)",opcode,tempName,data->luaLen);
        return;
    }

    //Unspawn a NPC
    if(opcode==34)
    {
        STR_REWD_034 * data = (STR_REWD_034 *)dataorg;
        LogSp(MSG_INFO,"\t\t\t\t\t ACT %.3i: Removing previously selected NPC. (op %u)",opcode,data->btOP);
        return;
    }

    //Really unknown :)
    LogSp(MSG_WARNING,"\t\t\t\t\t ACT %.3i: Impossible to export QSD opcode, size %u",opcode,size-8);


    return;
}