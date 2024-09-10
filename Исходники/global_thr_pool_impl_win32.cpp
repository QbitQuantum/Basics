void
worker_thread_impl::wakeup( )
{
  QueueUserAPC( []( ULONG_PTR ) {}, get_internals( ).thr.native_handle( ), 0 );
}