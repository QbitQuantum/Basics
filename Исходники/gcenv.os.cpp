// Sets the calling thread's affinity to only run on the processor specified
// in the GCThreadAffinity structure.
// Parameters:
//  affinity - The requested affinity for the calling thread. At most one processor
//             can be provided.
// Return:
//  true if setting the affinity was successful, false otherwise.
bool GCToOSInterface::SetThreadAffinity(GCThreadAffinity* affinity)
{
    LIMITED_METHOD_CONTRACT;

    assert(affinity != nullptr);
    if (affinity->Group != GCThreadAffinity::None)
    {
        assert(affinity->Processor != GCThreadAffinity::None);
        
        GROUP_AFFINITY ga;
        ga.Group = (WORD)affinity->Group;
        ga.Reserved[0] = 0; // reserve must be filled with zero
        ga.Reserved[1] = 0; // otherwise call may fail
        ga.Reserved[2] = 0;
        ga.Mask = (size_t)1 << affinity->Processor;
        return !!SetThreadGroupAffinity(GetCurrentThread(), &ga, nullptr);
    }
    else if (affinity->Processor != GCThreadAffinity::None)
    {
        return !!SetThreadAffinityMask(GetCurrentThread(), (DWORD_PTR)1 << affinity->Processor);
    }

    // Given affinity must specify at least one processor to use.
    return false;
}