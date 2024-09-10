PRIVATE int HTFileSave_free (HTStream * me)
{
    if (me) {
	(*me->target->isa->_free)(me->target);
#ifdef HAVE_SYSTEM
	if (me->end_command) system(me->end_command);    /* SECURITY HOLE!!! */
#endif
	if (me->callback) (*me->callback)(me->request, me->filename);
	if (me->remove_on_close) REMOVE(me->filename);
	HT_FREE(me->end_command);
	HT_FREE(me->filename);
	HT_FREE(me);
    }
    return HT_OK;
}