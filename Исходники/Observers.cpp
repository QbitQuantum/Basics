void
Observers::getReapedSlaves(std::vector<int>& d)
{
    IceUtil::Mutex::Lock sync(_reapedMutex);
    d.swap(_reaped);
}