void XProcNumberPageSegmentManager::Integrate()
{
    AutoCriticalSection autoCS(&cs);

    auto temp = this->segmentsList;
    auto prev = &this->segmentsList;
    while (temp)
    {
        if (temp->pageSegment == 0)
        {
            auto leafPageAllocator = recycler->GetRecyclerLeafPageAllocator();
            DListBase<PageSegment> segmentList;
            temp->pageSegment = (intptr_t)leafPageAllocator->AllocPageSegment(segmentList, leafPageAllocator,
                (void*)temp->pageAddress, XProcNumberPageSegmentImpl::PageCount, temp->committedEnd / AutoSystemInfo::PageSize);
            leafPageAllocator->IntegrateSegments(segmentList, 1, XProcNumberPageSegmentImpl::PageCount);

            this->integratedSegmentCount++;
        }

        unsigned int minIntegrateSize = XProcNumberPageSegmentImpl::BlockSize;
        for (; temp->pageAddress + temp->blockIntegratedSize + minIntegrateSize < (unsigned int)temp->allocEndAddress;
            temp->blockIntegratedSize += minIntegrateSize)
        {
            TRACK_ALLOC_INFO(recycler, Js::JavascriptNumber, Recycler, 0, (size_t)-1);

            if (!recycler->IntegrateBlock<LeafBit>((char*)temp->pageAddress + temp->blockIntegratedSize,
                (PageSegment*)temp->pageSegment, XProcNumberPageSegmentImpl::GetSizeCat(), sizeof(Js::JavascriptNumber)))
            {
                Js::Throw::OutOfMemory();
            }
        }

        *prev = (XProcNumberPageSegmentImpl*)temp->nextSegment;
        midl_user_free(temp);
        temp = *prev;
    }
}