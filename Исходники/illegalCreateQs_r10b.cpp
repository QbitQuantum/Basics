void
IllegalCreateQs_r10b::SendToxicCmd(SharedASQPtr asq, SharedACQPtr acq,
    SharedCmdPtr cmd, uint8_t dw, uint32_t mask, uint32_t val, CEStat status)
{
    uint16_t uniqueId;
    uint32_t isrCnt;
    uint32_t numCE;
    string work;

    LOG_NRM("Send the cmd to hdw via ASQ");
    asq->Send(cmd, uniqueId);

    work = str(boost::format("%s.pure.%d") % cmd->GetName().c_str() % uniqueId);
    asq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "asq"
        + cmd->GetName(), work), "Just B4 modifying, dump ASQ");

    ASQCmdToxify(asq, dw, mask, val);
    work = str(boost::format("%s.toxic.%d") % cmd->GetName().c_str() % uniqueId);
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

    work = str(boost::format("acq.%d") % uniqueId);
    IO::ReapCE(acq, 1, isrCnt, mGrpName, mTestName, work, status);
}