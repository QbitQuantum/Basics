unsigned
PreProcessor::process(ProcessContext& context, PostProcessor& dest, size_t limit)
{
	Event* const head = _head.load();
	if (!head) {
		return 0;
	}

	size_t n_processed = 0;
	Event* ev          = head;
	Event* last        = ev;
	while (ev && ev->is_prepared() && ev->time() < context.end()) {
		if (ev->time() < context.start()) {
			// Didn't get around to executing in time, oh well...
			ev->set_time(context.start());
		}
		ev->execute(context);
		last = ev;
		ev   = ev->next();
		++n_processed;
		if (limit && n_processed >= limit) {
			break;
		}
	}

	if (n_processed > 0) {
		Event* next = (Event*)last->next();
		last->next(NULL);
		dest.append(context, head, last);

		// Since _head was not NULL, we know it hasn't been changed since
		_head = next;

		/* If next is NULL, then _tail may now be invalid.  However, it would cause
		   a race to reset _tail here.  Instead, append() checks only _head for
		   emptiness, and resets the tail appropriately. */
	}

	return n_processed;
}