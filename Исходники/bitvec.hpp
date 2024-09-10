	static size_t* alloc(){
		lock_guard<mutex> guard(*mut);
		return (size_t*)pool->malloc();
	}