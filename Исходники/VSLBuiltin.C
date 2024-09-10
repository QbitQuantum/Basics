// Cons lists
static Box *op_cons(ListBox *args)
{
    ListBox *ret = 0;

    for (ListBox *b = args; !b->isEmpty(); b = b->tail())
    {
	Box *box = b->head();

	if (!box->isListBox())
	{
	    VSLLib::eval_error("invalid argument -- argument is list");
	    if (ret)
		ret->unlink();
	    return 0;
	}

	if (!((ListBox *)box)->isEmpty())
	{
	    // Create list to append
	    // If box is last arg, a link suffices
	    ListBox *box2;
	    if (b->tail()->isEmpty())
		box2 = (ListBox *)box->link();
	    else
		box2 = (ListBox *)box->dup();

	    // Append list: 
	    // If box is first arg, copy box
	    if (ret == 0)
		ret = box2;
	    else
	    {
		ret->cons(box2);
		box2->unlink();
	    }
	}
    }

    // No args? return []
    if (ret == 0)
	ret = new ListBox;

    return ret;
}