void trampoline( typename worker_fiber::coro_t::yield_type & yield)
{
    BOOST_ASSERT( yield);

    void * p( yield.get() );
    BOOST_ASSERT( p);
    setup< Fn > * from( static_cast< setup< Fn > * >( p) );

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    Fn fn_( forward< Fn >( from->fn) );
#else
    Fn fn_( move( from->fn) );
#endif

    worker_fiber f( & yield);
    from->f = & f;

    f.set_running();
    f.suspend();

    try
    {
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        Fn fn( forward< Fn >( fn_) );
#else
        Fn fn( move( fn_) );
#endif
        BOOST_ASSERT( f.is_running() );
        fn();
        BOOST_ASSERT( f.is_running() );
    }
    catch ( coro::detail::forced_unwind const&)
    {
        f.set_terminated();
        f.release();
        throw;
    }
    catch ( fiber_interrupted const&)
    { f.set_exception( current_exception() ); }
    catch (...)
    { std::terminate(); }

    f.set_terminated();
    f.release();
    f.suspend();

    BOOST_ASSERT_MSG( false, "fiber already terminated");
}