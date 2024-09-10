bool FPEnvironmentImpl::isFlagImpl(FlagImpl flag)
{
    return (_statusfp() & flag) != 0;
}