	/** Virtual destructor calls Free() to delete the objects contained
	in the linked list, in a thread-safe manner.*/
	virtual ~VCriticalLinkedListManager()
		{ Free(); }