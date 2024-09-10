void bt_readlock(BtLatch *latch)
{
ushort prev;

  do {
	//	obtain latch mutex
#ifdef unix
	if( __sync_fetch_and_or((ushort *)latch, Mutex) & Mutex )
		continue;
#else
	if( prev = _InterlockedOr16((ushort *)latch, Mutex) & Mutex )
		continue;
#endif
	//  see if exclusive request is granted or pending

	if( prev = !(latch->exclusive | latch->pending) )
#ifdef unix
		__sync_fetch_and_add((ushort *)latch, Share);
#else
		_InterlockedExchangeAdd16 ((ushort *)latch, Share);
#endif

#ifdef unix
	__sync_fetch_and_and ((ushort *)latch, ~Mutex);
#else
	_InterlockedAnd16((ushort *)latch, ~Mutex);
#endif

	if( prev )
		return;
#ifdef  unix
  } while( sched_yield(), 1 );
#else
  } while( SwitchToThread(), 1 );