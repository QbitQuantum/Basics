void Joiner::GetJoinerId(Mac::ExtAddress &aJoinerId) const
{
    otPlatRadioGetIeeeEui64(&GetInstance(), aJoinerId.m8);
    ComputeJoinerId(aJoinerId, aJoinerId);
}