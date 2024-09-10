BOOL CGetPlayerDataCMD::GetData(SGDP::ISDDBConnection* poDBConn, UINT32 dwPlayerID, DT_PLAYER_NOPVP_DATA& stPlayerNoPvpData, DT_PLAYER_PVP_DATA& stPlayerPvpData, UINT16& wErrCode)
{
    //CAutoCycle oAutoCycle(__FUNCTION__);

    wErrCode = FAIL;

    if(!GetPlayerBase(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        wErrCode = GET_NODATA;
        //USR_INFO(_SDT("[%s: %d]: GetPlayerBase failed! playerid:%d"), MSG_MARK, dwPlayerID);    //新增玩家肯定没有
        return FALSE;
    }

    if(!GetPlayerTodayConsume(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        wErrCode = GET_NODATA;
        //USR_INFO(_SDT("[%s: %d]: GetPlayerBase failed! playerid:%d"), MSG_MARK, dwPlayerID);    //新增玩家肯定没有
        return FALSE;
    }

    if(!GetPlayerExt(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetPlayerExt failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetBag(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetBag failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetBuild(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetBuild failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetHeroBase(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetHeroBase failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetHeroExt(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetBag GetHeroExt! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetInstance(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetInstance failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetTask(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetTask failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetRelationData(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetRelationData failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetEvenData(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetEvenData failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetSendFlowerLog(poDBConn, dwPlayerID, stPlayerNoPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetSendFlowerLog failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    if(!GetPvp(poDBConn, dwPlayerID, stPlayerPvpData))
    {
        SYS_CRITICAL(_SDT("[%s: %d]: GetPvp failed! playerid:%d"), MSG_MARK, dwPlayerID);
        return FALSE;
    }

    wErrCode = SUCCESS;

    return TRUE;
}