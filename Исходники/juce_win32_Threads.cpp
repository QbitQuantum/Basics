void JUCE_CALLTYPE Thread::setCurrentThreadAffinityMask (const uint32 affinityMask)
{
    SetThreadAffinityMask (GetCurrentThread(), affinityMask);
}