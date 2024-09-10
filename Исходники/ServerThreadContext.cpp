void ProcessContext::Release()
{
    InterlockedExchangeSubtract(&this->refCount, 1);
}