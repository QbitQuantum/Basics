sc_cor_pkg_fiber::sc_cor_pkg_fiber( sc_simcontext* simc )
: sc_cor_pkg( simc )
{
    if( ++ instance_count == 1 ) {
        // initialize the main coroutine
        assert( main_cor.m_fiber == 0 );
        main_cor.m_fiber = ConvertThreadToFiber( 0 );

        if( !main_cor.m_fiber && GetLastError() == ERROR_ALREADY_FIBER ) {
            // conversion of current thread to fiber has failed, because
            // someone else already converted the main thread to a fiber
            // -> store current fiber
            main_cor.m_fiber = GetCurrentFiber();
        }
        assert( main_cor.m_fiber != 0 );

#       if defined(__GNUC__) && __USING_SJLJ_EXCEPTIONS__
            // initialize the current coroutine
            assert( curr_cor == 0 );
            curr_cor = &main_cor;
#       endif
    }
}