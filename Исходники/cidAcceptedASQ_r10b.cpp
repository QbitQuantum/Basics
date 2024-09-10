void
CIDAcceptedASQ_r10b::RunCoreTest()
{
    /** \verbatim
     * Assumptions:
     * 1) Test CreateResources_r10b has run prior.
     * \endverbatim
     */
    uint32_t isrCount;
    // Lookup objs which were created in a prior test within group
    SharedASQPtr asq = CAST_TO_ASQ(gRsrcMngr->GetObj(ASQ_GROUP_ID))
    SharedACQPtr acq = CAST_TO_ACQ(gRsrcMngr->GetObj(ACQ_GROUP_ID))

    LOG_NRM("Verifying that the ACQ is empty");
    if (acq->ReapInquiry(isrCount, true) != 0) {
        acq->Dump(
            FileSystem::PrepDumpFile(mGrpName, mTestName, "acq",
            "notEmpty"), "Test assumption have not been met");
        throw FrmwkEx(HERE, 
            "The ACQ should not have any CE's waiting before testing");
    }

    LOG_NRM("Create identify cmd and assoc some buffer memory");
    SharedIdentifyPtr idCmdCap = SharedIdentifyPtr(new Identify());
    LOG_NRM("Force identify to request ctrlr capabilities struct");
    idCmdCap->SetCNS(CNS_Controller);
    SharedMemBufferPtr idMemCap = SharedMemBufferPtr(new MemBuffer());
    idMemCap->InitAlignment(Identify::IDEAL_DATA_SIZE, PRP_BUFFER_ALIGNMENT,
        false, 0);
    send_64b_bitmask idPrpCap =
        (send_64b_bitmask)(MASK_PRP1_PAGE | MASK_PRP2_PAGE);
    idCmdCap->SetPrpBuffer(idPrpCap, idMemCap);

    LOG_NRM("Learn initial unique command id assigned by dnvme.");
    uint16_t currCID;
    asq->Send(idCmdCap, currCID);
    uint16_t prevCID = currCID;
    for (uint32_t nCmds = 0; nCmds < MAX_CMDS; nCmds++) {
        asq->Ring();
        LOG_NRM("Verify unique CID #%d for Cmd #%d", currCID, nCmds + 1);
        ReapVerifyCID(asq, acq, currCID);

        asq->Send(idCmdCap, currCID);
        if (currCID != (uint16_t)(prevCID + 1)) {
            asq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "asq.fail"),
                "Dump Entire ASQ");
            acq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName, "acq.fail"),
                "Dump Entire ACQ");
            throw FrmwkEx(HERE, "Current CID(%d) != prev + 1(%d)", currCID,
                prevCID);
        }

        prevCID = currCID;
    }
}