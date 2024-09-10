    virtual int ready()
    {
	if(slotA->ready()){
	    val = op(slotA->val);
	    delete slotA;
	    return 1;
	} else return 0;
    }