static DFBResult
system_shutdown( bool emergency )
{
     DFBResult   ret;

     // for now just crash until we implement a clean shutdown
     crashme();

     AndroidDataShared *shared;
     D_ASSERT( m_data != NULL );

     shared = m_data->shared;
     D_ASSERT( shared != NULL );

     dfb_surface_pool_destroy( shared->pool );

     /* cleanup EGL related stuff */
     eglDestroyContext( m_data->dpy, m_data->ctx );
     eglTerminate( m_data->dpy );

     SHFREE( shared->shmpool, shared );

     D_FREE( m_data );
     m_data = NULL;

     return DFB_OK;
}