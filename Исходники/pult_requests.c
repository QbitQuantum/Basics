s32 rx_handler_saveTableSegment(PultMessageRx *pMsg)
{
    OUT_DEBUG_2("rx_handler_saveTableSegment\r\n");
    OUT_DEBUG_2("pMsg->part_len = %d\r\n", pMsg->part_len);
    if(4 == pMsg->part_len){
        return RETURN_NO_ERRORS;
    }


    RxConfiguratorPkt pkt;

    pkt.dataType=pMsg->complex_msg_part[0];
    pkt.data=&pMsg->complex_msg_part[4];


    pkt.datalen= pMsg->part_len-4;

    pkt.marker=CONFIGURATION_AUTOSYNC_PACKET_MARKER;
    pkt.pktIdx=0;
    pkt.repeatCounter=0;
    pkt.sessionKey=0;
    pkt.bAppend=TRUE;


    char name[30] = {0};

    switch (pkt.dataType) {
    case OBJ_PHONELIST_SIM1:
        Ql_strcpy(name, FILENAME_PATTERN_PHONELIST_SIM1);
        break;
    case OBJ_PHONELIST_SIM2:
        Ql_strcpy(name, FILENAME_PATTERN_PHONELIST_SIM2);
        break;
    case OBJ_IPLIST_SIM1:
        Ql_strcpy(name, FILENAME_PATTERN_IPLIST_SIM1);
        break;
    case OBJ_IPLIST_SIM2:
        Ql_strcpy(name, FILENAME_PATTERN_IPLIST_SIM2);
        break;
    default:
        break;
    }

    //===================================
    // PREPARE Empty file
    if(0 == pMsg->complex_msg_part[1])
    {
        s32 ret = prepareEmptyDbFileInAutosyncTemporaryDB(name);
        if(ret < RETURN_NO_ERRORS)
        {
            OUT_DEBUG_1("prepareEmptyDbFileInAutosyncTemporaryDB() = %d error. File not create.\r\n", ret);
            return ret;
        }
    }

    //===================================
    // SAVE to AutosyncTemporaryDB
    s32 ret = saveSettingsToAutosyncTemporaryDB(&pkt);
    if(ret < RETURN_NO_ERRORS)
    {
        OUT_DEBUG_1("saveSettingsToAutosyncTemporaryDB() = %d error\r\n", ret);
        return ret;
    }


    //===================================
    // MOVE to work file
    if(pMsg->complex_msg_part[1] == pMsg->complex_msg_part[2])
    {
        if(!copyFilleFromAutosyncTemporaryDBToWorkDB(name))
        {
            OUT_DEBUG_1("copyFilleFromAutosyncTemporaryDBToWorkDB() = %d error. File not move.\r\n");
            return ERR_DB_SAVING_FAILED;
        }

        // ACTUALIZATION
        ret = actualizationSIMCardLists(pkt.dataType);
        if(ret < RETURN_NO_ERRORS)
        {
            OUT_DEBUG_1("actualizationSIMCardLists() = %d error. Actualize error.\r\n", ret);
            return ret;
        }

        SystemInfo *pSysInfo = getSystemInfo(NULL);
        pSysInfo->settings_signature_autosync = pMsg->complex_msg_part[3];

        // save to DB signature autosync
        ret = saveToDbFile(DBFILE(FILENAME_PATTERN_SYSTEMINFO), pSysInfo, sizeof(SystemInfo), FALSE);
        if(ret < RETURN_NO_ERRORS)
        {
            OUT_DEBUG_1("saveToDbFile() = %d error. Save signature autosynce error.\r\n", ret);
            return ret;
        }
        OUT_DEBUG_7("SystemInfo settings_signature_autosync = %d.\r\n", pSysInfo->settings_signature_autosync);
    }

    return RETURN_NO_ERRORS;
}