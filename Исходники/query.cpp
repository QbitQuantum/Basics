/*!	\brief Tells the BQuery to start fetching entries satisfying the predicate.
	After Fetch() has been called GetNextEntry(), GetNextRef() and
	GetNextDirents() can be used to retrieve the enties. Live query updates
	may be sent immediately after this method has been called.
	Fetch() fails, if it has already been called. To reuse a BQuery object it
	has to be reset via Clear().
	\return
	- \c B_OK: Everything went fine.
	- \c B_NO_INIT: The predicate or the volume aren't set.
	- \c B_BAD_VALUE: The predicate is invalid.
	- \c B_NOT_ALLOWED: Fetch() has already been called.
*/
status_t
BQuery::Fetch()
{
    if (_HasFetched())
        return B_NOT_ALLOWED;

    _EvaluateStack();

    if (!fPredicate || fDevice < 0)
        return B_NO_INIT;

    BString parsedPredicate;
    _ParseDates(parsedPredicate);

    fQueryFd = _kern_open_query(fDevice, parsedPredicate.String(),
                                parsedPredicate.Length(), fLive ? B_LIVE_QUERY : 0, fPort, fToken);
    if (fQueryFd < 0)
        return fQueryFd;

    // set close on exec flag
    fcntl(fQueryFd, F_SETFD, FD_CLOEXEC);

    return B_OK;
}