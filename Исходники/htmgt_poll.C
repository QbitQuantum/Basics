    // Send a poll command to all OCCs
    errlHndl_t sendOccPoll(const bool i_flushAllErrors)
    {
        errlHndl_t l_err = NULL;
        uint8_t * l_poll_rsp = NULL;

        // Loop through all functional OCCs
        std::vector<Occ*> occList = occMgr::instance().getOccArray();
        for (std::vector<Occ*>::iterator itr = occList.begin();
             (itr < occList.end()) && (NULL == l_err);
             ++itr)
        {
            Occ * occ = (*itr);
            const uint8_t occInstance = occ->getInstance();

            bool continuePolling = false;
            do
            {
                // create 1 byte buffer for poll command data
                const uint8_t l_cmdData[1] = { 0x10 /*version*/ };

                OccCmd cmd(occ, OCC_CMD_POLL, sizeof(l_cmdData), l_cmdData);
                l_err = cmd.sendOccCmd();
                if (l_err != NULL)
                {
                    // Poll failed
                    TMGT_ERR("sendOccPoll: OCC%d poll failed with rc=0x%04X",
                             occInstance, l_err->reasonCode());
                }
                else
                {
                    // Poll succeeded, check response
                    uint32_t l_poll_rsp_size = cmd.getResponseData(l_poll_rsp);
                    if (l_poll_rsp_size >= OCC_POLL_DATA_MIN_SIZE)
                    {
                        if (i_flushAllErrors)
                        {
                            const occPollRspStruct_t *currentPollRsp =
                                (occPollRspStruct_t *) l_poll_rsp;
                            if (currentPollRsp->errorId != 0)
                            {
                                // An error was returned, keep polling OCC
                                continuePolling = true;
                            }
                            else
                            {
                                continuePolling = false;
                            }
                        }
                        occ->pollRspHandler(l_poll_rsp, l_poll_rsp_size);
                    }
                    else
                    {
                        TMGT_ERR("sendOccPoll: OCC%d poll command response "
                                 "failed with invalid data length %d",
                                 occInstance, l_poll_rsp_size);
                        /*@
                         * @errortype
                         * @reasoncode HTMGT_RC_INVALID_LENGTH
                         * @moduleid  HTMGT_MOD_OCC_POLL
                         * @userdata1 OCC instance
                         * @devdesc Invalid POLL response length
                         */
                        bldErrLog(l_err, HTMGT_MOD_OCC_POLL,
                                  HTMGT_RC_INVALID_LENGTH,
                                  occInstance, 0, 0, 0,
                                  ERRORLOG::ERRL_SEV_INFORMATIONAL);
                    }
                }
            }
            while (continuePolling);

        } // for each OCC

        return l_err;

    } // end sendOccPoll()