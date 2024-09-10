vm_status vm_affinity_thread_get(vm_thread *pthr, vm_affinity_mask *mptr)
{
    DWORD processmask = 0;

    if(!mptr)
        return VM_NULL_PTR;

    if(mptr[0].msklen)
    {
        /* only one way to obtain thread affinity mask - set it again */
        if (pthr[0].preset_affinity_mask)
        {
            mptr[0].mskbits[0] = (unsigned long)SetThreadAffinityMask(pthr[0].handle, pthr[0].preset_affinity_mask);
            return VM_OK;
        }
        else
        {
            if(GetProcessAffinityMask(pthr[0].handle, (PDWORD_PTR)&processmask, (PDWORD_PTR)mptr[0].mskbits))
                return VM_OK;
        }
    }

    return VM_OPERATION_FAILED;
}