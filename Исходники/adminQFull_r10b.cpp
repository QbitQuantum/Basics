void
AdminQFull_r10b::AdminQFull(uint16_t numASQEntries, uint16_t numACQEntries,
    SharedIdentifyPtr idCmdCtrlr)
{
    uint32_t numCE;
    uint32_t isrCount;
    uint16_t uniqueId;

    if (gCtrlrConfig->SetState(ST_DISABLE_COMPLETELY) == false)
        throw FrmwkEx(HERE);

    // Create Admin Q Objects for test lifetime
    SharedACQPtr acq = CAST_TO_ACQ(SharedACQPtr(new ACQ(mFd)))
    acq->Init(numACQEntries);

    SharedASQPtr asq = CAST_TO_ASQ(SharedASQPtr(new ASQ(mFd)))
    asq->Init(numASQEntries);

    gCtrlrConfig->SetCSS(CtrlrConfig::CSS_NVM_CMDSET);
    if (gCtrlrConfig->SetState(ST_ENABLE) == false)
        throw FrmwkEx(HERE);

    uint32_t nCmdsToSubmit = numASQEntries - 1;
    LOG_NRM("Send #%d cmds to hdw via ASQ", nCmdsToSubmit);
    for (uint32_t nCmds = 0; nCmds < nCmdsToSubmit; nCmds++) {
        LOG_NRM("Sending #%d of #%d Identify Cmds thru ASQ", nCmds + 1,
            nCmdsToSubmit);
        asq->Send(idCmdCtrlr, uniqueId);
        asq->Ring();

        LOG_NRM("Wait for the CE to arrive in ACQ");
        if (acq->ReapInquiryWaitSpecify(DEFAULT_CMD_WAIT_ms, (nCmds + 1), numCE,
            isrCount) == false) {

            // when asq size = acq size + 1, last CE will never arrive.
            if ((numASQEntries == numACQEntries + 1) &&
                (nCmds == nCmdsToSubmit - 1)) {
                // Reap one element from IOCQ to make room for last CE.
                IO::ReapCE(acq, 1, isrCount, mGrpName, mTestName, "ACQCE",
                    CESTAT_SUCCESS);
                if (acq->ReapInquiryWaitSpecify(DEFAULT_CMD_WAIT_ms, nCmds,
                    numCE, isrCount) == false) {
                    acq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName,
                        "acq." + idCmdCtrlr->GetName()), "Dump entire ACQ");
                    throw FrmwkEx(HERE, "Unable to see last CE as expected");
                }
                break;
            }
            acq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName,
                "acq." + idCmdCtrlr->GetName()), "Dump Entire ACQ");
            throw FrmwkEx(HERE, "Unable to see CE for issued cmd #%d", nCmds + 1);

        } else if (numCE != nCmds + 1) {
            acq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName,
                "acq." + idCmdCtrlr->GetName()), "Dump Entire ACQ");
            throw FrmwkEx(HERE, "Missing last CE, #%d cmds of #%d received",
                nCmds + 1, numCE);
        }
    }
}