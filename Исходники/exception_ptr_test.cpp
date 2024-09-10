void
join( thread_handle & t )
    {
    t.t_.join();
    assert(t.err_);
    rethrow_exception(t.err_);
    }