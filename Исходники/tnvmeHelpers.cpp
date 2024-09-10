bool SetFeaturesNumberOfQueues(Queues &queues, int fd)
{
    uint16_t numCE;
    uint16_t ceRemain;
    uint16_t numReaped;

    try {   // The objects to perform this work throw exceptions
        LOG_NRM("Setting number of Q's; ncqr=0x%04X, nsqr=0x%04X",
            queues.ncqr, queues.nsqr);
        if (gCtrlrConfig->SetState(ST_DISABLE_COMPLETELY) == false)
            throw exception();

        LOG_NRM("Prepare the admin Q's to setup this request");
        SharedACQPtr acq = SharedACQPtr(new ACQ(fd));
        acq->Init(2);
        SharedASQPtr asq = SharedASQPtr(new ASQ(fd));
        asq->Init(2);
        if (gCtrlrConfig->SetState(ST_ENABLE) == false)
            throw exception();

        LOG_NRM("Create the cmd to carry this data to the DUT");
        SharedSetFeaturesPtr sfNumOfQ =
            SharedSetFeaturesPtr(new SetFeatures(fd));
        sfNumOfQ->SetFID(BaseFeatures::FID_NUM_QUEUES);
        sfNumOfQ->SetNumberOfQueues(queues.ncqr, queues.nsqr);

        LOG_NRM("Send the cmd to the ASQ, wait for it to complete");
        asq->Send(sfNumOfQ);
        asq->Ring();
        if (acq->ReapInquiryWaitSpecify(2000, 1, numCE) == false) {
            LOG_ERR("Unable to see completion of Set Features cmd");
            throw exception();
        } else if (numCE != 1) {
            LOG_ERR("The ACQ should only have 1 CE as a result of a cmd");
            throw exception();
        }

        LOG_NRM("The CQ's metrics before reaping holds head_ptr needed");
        struct nvme_gen_cq acqMetrics = acq->GetQMetrics();
        KernelAPI::LogCQMetrics(acqMetrics);

        LOG_NRM("Reaping CE from ACQ, requires memory to hold reaped CE");
        SharedMemBufferPtr ceMemIOCQ = SharedMemBufferPtr(new MemBuffer());
        if ((numReaped = acq->Reap(ceRemain, ceMemIOCQ, numCE, true)) != 1) {
            LOG_ERR("Verified there was 1 CE, but reaping produced %d",
                numReaped);
            throw exception();
        }
        LOG_NRM("The reaped get features CE is...");
        acq->LogCE(acqMetrics.head_ptr);

        union CE ce = acq->PeekCE(acqMetrics.head_ptr);
        if (ce.n.status != 0) {
            LOG_ERR("CE shows cmd failed: status = 0x%02X", ce.n.status);
            throw exception();
        }
        printf("The operation succeeded to set number of queues\n");
    } catch (...) {
        printf("Operation failed to set number of queues\n");
        return false;
    }

    return true;
}