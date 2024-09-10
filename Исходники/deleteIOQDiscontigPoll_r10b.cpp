void
DeleteIOQDiscontigPoll_r10b::DeleteIOSQDiscontigPoll(SharedASQPtr asq,
    SharedACQPtr acq)
{
    uint16_t numCE;

    LOG_NRM("Lookup IOSQ which was created in a prior test within group");
    SharedIOSQPtr iosq = CAST_TO_IOSQ(
        gRsrcMngr->GetObj(IOSQ_DISCONTIG_POLL_GROUP_ID))

    LOG_NRM("Create a Delete IOSQ cmd to perform the IOSQ deletion");
    SharedDeleteIOSQPtr deleteIOSQCmd =
        SharedDeleteIOSQPtr(new DeleteIOSQ(mFd));
    deleteIOSQCmd->Init(iosq);


    LOG_NRM("Send the Delete IOSQ cmd to hdw");
    asq->Send(deleteIOSQCmd);
    asq->Dump(FileSystem::PrepLogFile(mGrpName, mTestName, "asq",
        "deleteIOSQCmd"),
        "Just B4 ringing SQ0 doorbell, dump entire SQ contents");
    asq->Ring();


    LOG_NRM("Wait for the CE to arrive in ACQ");
    if (acq->ReapInquiryWaitSpecify(DEFAULT_CMD_WAIT_ms, 1, numCE) == false) {
        LOG_ERR("Unable to see completion of Delete IOSQ cmd");
        acq->Dump(
            FileSystem::PrepLogFile(mGrpName, mTestName, "acq","deleteIOSQCmd"),
            "Unable to see any CE's in CQ0, dump entire CQ contents");
        throw exception();
    }
    acq->Dump(FileSystem::PrepLogFile(mGrpName, mTestName, "acq",
        "deleteIOSQCmd"), "Just B4 reaping CQ0, dump entire CQ contents");


    {
        uint16_t ceRemain;
        uint16_t numReaped;

        LOG_NRM("Reaping CE from ACQ, requires memory to hold reaped CE");
        SharedMemBufferPtr ceMemIOSQ = SharedMemBufferPtr(new MemBuffer());
        if ((numReaped = acq->Reap(ceRemain, ceMemIOSQ, numCE, true)) != 1) {
            LOG_ERR("Verified there was 1 CE, but reaping produced %d",
                numReaped);
            throw exception();
        }
        LOG_NRM("The reaped identify CE is...");
        ceMemIOSQ->Log();
    }

    // Not explicitly necessary, but is more clean to free what is not needed
    gRsrcMngr->FreeObj(IOSQ_DISCONTIG_POLL_GROUP_ID);
}