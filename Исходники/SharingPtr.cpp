    void
    shared_count::release_shared()
    {
#ifdef _MSC_VER
        if (_InterlockedDecrement(&shared_owners_) == -1)
#else
        if (--shared_owners_ == -1)
#endif
        {
            on_zero_shared();
            delete this;
        }
    }