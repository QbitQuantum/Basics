void
InvalidMSIXIRQ_r10b::SendToxicCmd(SharedASQPtr asq, SharedACQPtr acq,
    SharedCmdPtr cmd, uint16_t illegalIrqVec)
{
    string work;
    uint16_t uniqueId;
    uint32_t isrCnt;
    uint32_t numCE;

    LOG_NRM("Send the cmd to hdw via ASQ with illegal IRQ vec %d",
        illegalIrqVec);
    asq->Send(cmd, uniqueId);
    work = str(boost::format("pure.%d") % illegalIrqVec);
    asq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "asq", work),
        "Just B4 modifying, dump ASQ");

    ASQCmdToxify(asq, illegalIrqVec);
    work = str(boost::format("toxic.%d") % illegalIrqVec);
    asq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "asq", work),
        "Just B4 ringing doorbell, dump ASQ");

    asq->Ring();

    LOG_NRM("Wait for the CE to arrive in CQ %d", acq->GetQId());
    if (acq->ReapInquiryWaitSpecify(DEFAULT_CMD_WAIT_ms, 1, numCE, isrCnt)
        == false) {
        acq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "acq.fail"),
            "Dump Entire ACQ");
        asq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "asq.fail"),
            "Dump Entire ASQ");
        throw FrmwkEx(HERE, "Unable to see CEs for issued cmd");
    }

    IO::ReapCE(acq, 1, isrCnt, mGrpName, mTestName, "acq",
        CESTAT_INVAL_INT_VEC);
}