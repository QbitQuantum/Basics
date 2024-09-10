			AtomicType Atomic (Args &&... args) {
			
				lock.Acquire();
				auto guard=AtExit([&] () {	lock.Release();	});
				
				AtomicType retr;
				atomic(retr,std::forward<Args>(args)...);
				
				return retr;
			
			}