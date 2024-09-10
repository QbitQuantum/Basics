void
UnsupportRsvdFields_r11b::SendAsyncEventRequests(SharedASQPtr &asq,
    uint32_t nCmds, bool rsvd)
{
    uint16_t uniqueId;
    string work;

    LOG_NRM("Create aync event request cmd");
    SharedAsyncEventReqPtr asyncEventReqCmd =
        SharedAsyncEventReqPtr(new AsyncEventReq());

    if (rsvd == true) {
        LOG_NRM("Set all cmd's rsvd bits");
        uint32_t work = asyncEventReqCmd->GetDword(0);
        work |= 0x00007c00;      // Set DW0_b14:10 bits
        asyncEventReqCmd->SetDword(work, 0);

        for (uint32_t dw = 2; dw <= 15; dw++)
            asyncEventReqCmd->SetDword(0xffffffff, dw);
    } else {
        LOG_NRM("Reserved bits in the cmd are not set");
    }

    for (uint32_t i = 0; i < nCmds; i++) {
        LOG_NRM("Send the async event request cmd to hdw via ASQ");
        asq->Send(asyncEventReqCmd, uniqueId);
        work = str(boost::format("asyncEventReq.%d") % i);
        asq->Dump(FileSystem::PrepDumpFile(mGrpName, mTestName,
            "asq", work), "Before doorbell ring");
        asq->Ring();
    }
}