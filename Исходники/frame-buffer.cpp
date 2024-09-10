boost::shared_ptr<ImmutableVideoFramePacket>
VideoFrameSlot::readPacket(const BufferSlot& slot, bool& recovered)
{
    if (slot.getNameInfo().streamType_ != 
        MediaStreamParams::MediaStreamType::MediaStreamTypeVideo)
        throw std::runtime_error("Wrong slot supplied: can not read video "
            "packet from audio slot");

    // check if recovery is possible
    Name parityKey(NameComponents::NameComponentParity);
    std::map<ndn::Name, boost::shared_ptr<SlotSegment>> 
        dataSegments(slot.fetched_.begin(), slot.fetched_.lower_bound(parityKey));
    std::map<ndn::Name, boost::shared_ptr<SlotSegment>> 
        paritySegments(slot.fetched_.upper_bound(parityKey), slot.fetched_.end());

    if ((!paritySegments.size() && 
        dataSegments.size() < dataSegments.begin()->second->getData()->getSlicesNum()) ||
        dataSegments.size() == 0)
    {
        recovered = false;
        return boost::shared_ptr<ImmutableVideoFramePacket>();
    }

    boost::shared_ptr<WireData<VideoFrameSegmentHeader>> firstSeg = 
            boost::dynamic_pointer_cast<WireData<VideoFrameSegmentHeader>>(dataSegments.begin()->second->getData());
    boost::shared_ptr<WireData<VideoFrameSegmentHeader>> firstParitySeg;

    if (paritySegments.size()) 
        firstParitySeg = boost::dynamic_pointer_cast<WireData<VideoFrameSegmentHeader>>(paritySegments.begin()->second->getData());

    size_t segmentSize = firstSeg->segment().getPayload().size();
    size_t paritySegSize = (paritySegments.size() ? firstParitySeg->segment().getPayload().size() : 0);
    unsigned int nDataSegmentsExpected = firstSeg->getSlicesNum();
    unsigned int nParitySegmentsExpected = (paritySegments.size() ? paritySegments.begin()->second->getData()->getSlicesNum() : 0);

    fecList_.assign(nDataSegmentsExpected+nParitySegmentsExpected, FEC_RLIST_SYMEMPTY);
    storage_->resize(segmentSize*(nDataSegmentsExpected+nParitySegmentsExpected));

    int segNo = 0;
    for (auto it:dataSegments)
    {
        const boost::shared_ptr<WireData<VideoFrameSegmentHeader>> wd = 
            boost::dynamic_pointer_cast<WireData<VideoFrameSegmentHeader>>(it.second->getData());
        
        while (segNo != wd->getSegNo() && segNo < nDataSegmentsExpected)
            storage_->insert(storage_->begin()+segmentSize*segNo++, segmentSize, 0);
        
        if (segNo < nDataSegmentsExpected)
        {
            storage_->insert(storage_->begin()+segmentSize*segNo, 
                wd->segment().getPayload().begin(),
                wd->segment().getPayload().end());
            fecList_[segNo] = FEC_RLIST_SYMREADY;
            segNo++;
        }
    }

    bool frameExtracted = false;
    if (dataSegments.size() < nDataSegmentsExpected)
    {
        segNo = 0;
        for (auto it:paritySegments)
        {
            const boost::shared_ptr<WireData<VideoFrameSegmentHeader>> wd =
            boost::dynamic_pointer_cast<WireData<VideoFrameSegmentHeader>>(it.second->getData());

            while (segNo != wd->getSegNo() && segNo < nParitySegmentsExpected)
                storage_->insert(storage_->begin()+nDataSegmentsExpected*segmentSize + paritySegSize*segNo++, segmentSize, 0);

            if (segNo < nParitySegmentsExpected)
            {
                storage_->insert(storage_->begin()+nDataSegmentsExpected*segmentSize+paritySegSize*segNo, 
                    wd->segment().getPayload().begin(),
                    wd->segment().getPayload().end());            

                fecList_[nDataSegmentsExpected+segNo] = FEC_RLIST_SYMREADY;
                segNo++;
            }
        }
        
        fec::Rs28Decoder dec(nDataSegmentsExpected, nParitySegmentsExpected, segmentSize);
        int nRecovered = dec.decode(storage_->data(),
            storage_->data()+nDataSegmentsExpected*segmentSize,
            fecList_.data());
        recovered = (nRecovered+dataSegments.size() >= nDataSegmentsExpected);
        frameExtracted = recovered;
    }
    else 
        frameExtracted = true;

    storage_->resize(nDataSegmentsExpected*segmentSize);

    return (frameExtracted ? boost::make_shared<ImmutableVideoFramePacket>(storage_) : 
                boost::shared_ptr<ImmutableVideoFramePacket>());
}