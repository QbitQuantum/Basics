void trampoline_push( intptr_t vp)
{
    typedef typename Coro::param_type   param_type;

    BOOST_ASSERT( vp);

    setup< Fn > * from(
        reinterpret_cast< setup< Fn > * >( vp) );

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    Fn fn( forward< Fn >( from->fn) );
#else
    Fn fn( move( from->fn) );
#endif

    coroutine_context caller( * from->caller);
    coroutine_context callee( * from->callee);

    Coro c( & caller, & callee,
            stack_unwind == from->attr.do_unwind,
            fpu_preserved == from->attr.preserve_fpu);
    from = 0;

    {
        param_type * from(
            reinterpret_cast< param_type * >(
                c.callee_->jump(
                    * c.caller_,
                    reinterpret_cast< intptr_t >(  & c),
                    c.preserve_fpu() ) ) );
        if ( ! from->do_unwind)
        {
            BOOST_ASSERT( from->data);

            // create push_coroutine
            typename Self::impl_type b( & callee, & caller, false, c.preserve_fpu(), from->data);
            Self yield( & b);
            try
            { fn( yield); }
            catch ( forced_unwind const&)
            {}
            catch (...)
            { c.except_ = current_exception(); }
        }
    }

    c.flags_ |= flag_complete;
    param_type to;
    c.callee_->jump(
        * c.caller_,
        reinterpret_cast< intptr_t >( & to),
        c.preserve_fpu() );
    BOOST_ASSERT_MSG( false, "push_coroutine is complete");
}