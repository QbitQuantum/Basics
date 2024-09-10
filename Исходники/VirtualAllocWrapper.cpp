LPVOID PreReservedVirtualAllocWrapper::AllocPages(LPVOID lpAddress, size_t pageCount,  DWORD allocationType, DWORD protectFlags, bool isCustomHeapAllocation)
{
    if (pageCount > AutoSystemInfo::MaxPageCount)
    {
        return nullptr;
    }
    size_t dwSize = pageCount * AutoSystemInfo::PageSize;
    
    AssertMsg(isCustomHeapAllocation, "PreReservation used for allocations other than CustomHeap?");

    Assert(dwSize != 0);

    {
        AutoCriticalSection autocs(&this->cs);
        //Return nullptr, if no space to Reserve
        if (EnsurePreReservedRegionInternal() == nullptr)
        {
            PreReservedHeapTrace(_u("No space to pre-reserve memory with %d pages. Returning NULL\n"), PreReservedAllocationSegmentCount * AutoSystemInfo::Data.GetAllocationGranularityPageCount());
            return nullptr;
        }

        char * addressToReserve = nullptr;

        uint freeSegmentsBVIndex = BVInvalidIndex;
        size_t requestedNumOfSegments = dwSize / (AutoSystemInfo::Data.GetAllocationGranularityPageSize());
        Assert(requestedNumOfSegments <= MAXUINT32);

        if (lpAddress == nullptr)
        {
            Assert(requestedNumOfSegments != 0);
            AssertMsg(dwSize % AutoSystemInfo::Data.GetAllocationGranularityPageSize() == 0, "dwSize should be aligned with Allocation Granularity");

            do
            {
                freeSegmentsBVIndex = freeSegments.GetNextBit(freeSegmentsBVIndex + 1);
                //Return nullptr, if we don't have free/decommit pages to allocate
                if ((freeSegments.Length() - freeSegmentsBVIndex < requestedNumOfSegments) ||
                    freeSegmentsBVIndex == BVInvalidIndex)
                {
                    PreReservedHeapTrace(_u("No more space to commit in PreReserved Memory region.\n"));
                    return nullptr;
                }
            } while (!freeSegments.TestRange(freeSegmentsBVIndex, static_cast<uint>(requestedNumOfSegments)));

            uint offset = freeSegmentsBVIndex * AutoSystemInfo::Data.GetAllocationGranularityPageSize();
            addressToReserve = (char*) preReservedStartAddress + offset;

            //Check if the region is not already in MEM_COMMIT state.
            MEMORY_BASIC_INFORMATION memBasicInfo;
            size_t bytes = VirtualQuery(addressToReserve, &memBasicInfo, sizeof(memBasicInfo));
            if (bytes == 0) 
            {
                MemoryOperationLastError::RecordLastError();
            }
            if (bytes == 0
                || memBasicInfo.RegionSize < requestedNumOfSegments * AutoSystemInfo::Data.GetAllocationGranularityPageSize()
                || memBasicInfo.State == MEM_COMMIT)
            {
                CustomHeap_BadPageState_fatal_error((ULONG_PTR)this);
            }
        }
        else
        {
            //Check If the lpAddress is within the range of the preReserved Memory Region
            Assert(((char*) lpAddress) >= (char*) preReservedStartAddress || ((char*) lpAddress + dwSize) < GetPreReservedEndAddress());

            addressToReserve = (char*) lpAddress;
            freeSegmentsBVIndex = (uint) ((addressToReserve - (char*) preReservedStartAddress) / AutoSystemInfo::Data.GetAllocationGranularityPageSize());
#if DBG
            uint numOfSegments = (uint)ceil((double)dwSize / (double)AutoSystemInfo::Data.GetAllocationGranularityPageSize());
            Assert(numOfSegments != 0);
            Assert(freeSegmentsBVIndex + numOfSegments - 1 < freeSegments.Length());
            Assert(!freeSegments.TestRange(freeSegmentsBVIndex, numOfSegments));
#endif
        }

        AssertMsg(freeSegmentsBVIndex < PreReservedAllocationSegmentCount, "Invalid BitVector index calculation?");
        AssertMsg(dwSize % AutoSystemInfo::PageSize == 0, "COMMIT is managed at AutoSystemInfo::PageSize granularity");

        char * allocatedAddress = nullptr;
        bool failedToProtectPages = false;

        if ((allocationType & MEM_COMMIT) != 0)
        {
#if defined(ENABLE_JIT_CLAMP)
            AutoEnableDynamicCodeGen enableCodeGen;
#endif

#if defined(_CONTROL_FLOW_GUARD)
            if (AutoSystemInfo::Data.IsCFGEnabled())
            {
                DWORD oldProtect = 0;
                DWORD allocProtectFlags = 0;

                if (AutoSystemInfo::Data.IsCFGEnabled())
                {
                    allocProtectFlags = PAGE_EXECUTE_RW_TARGETS_INVALID;
                }
                else
                {
                    allocProtectFlags = PAGE_EXECUTE_READWRITE;
                }

                allocatedAddress = (char *)VirtualAlloc(addressToReserve, dwSize, MEM_COMMIT, allocProtectFlags);
                if (allocatedAddress != nullptr)
                {
                    BOOL result = VirtualProtect(allocatedAddress, dwSize, protectFlags, &oldProtect);
                    if (result == FALSE)
                    {
                        CustomHeap_BadPageState_fatal_error((ULONG_PTR)this);
                    }
                    AssertMsg(oldProtect == (PAGE_EXECUTE_READWRITE), "CFG Bitmap gets allocated and bits will be set to invalid only upon passing these flags.");
                }
                else
                {
                    MemoryOperationLastError::RecordLastError();
                }
            }
            else
#endif
            {
                allocatedAddress = (char *)VirtualAlloc(addressToReserve, dwSize, MEM_COMMIT, protectFlags);
                if (allocatedAddress == nullptr)
                {
                    MemoryOperationLastError::RecordLastError();
                }
            }
        }
        else
        {
            // Just return the uncommitted address if we didn't ask to commit it.
            allocatedAddress = addressToReserve;
        }

        // Keep track of the committed pages within the preReserved Memory Region
        if (lpAddress == nullptr && allocatedAddress != nullptr)
        {
            Assert(allocatedAddress == addressToReserve);
            Assert(requestedNumOfSegments != 0);
            freeSegments.ClearRange(freeSegmentsBVIndex, static_cast<uint>(requestedNumOfSegments));
        }

        PreReservedHeapTrace(_u("MEM_COMMIT: StartAddress: 0x%p of size: 0x%x * 0x%x bytes \n"), allocatedAddress, requestedNumOfSegments, AutoSystemInfo::Data.GetAllocationGranularityPageSize());
        if (failedToProtectPages)
        {
            return nullptr;
        }
        return allocatedAddress;
    }
}