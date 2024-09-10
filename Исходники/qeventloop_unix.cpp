void QEventLoop::unregisterSocketNotifier( QSocketNotifier *notifier )
{
    int sockfd = notifier->socket();
    int type = notifier->type();
    if ( sockfd < 0 || type < 0 || type > 2 || notifier == 0 ) {
#if defined(QT_CHECK_RANGE)
	qWarning( "QSocketNotifier: Internal error" );
#endif
	return;
    }

    QPtrList<QSockNot> *list = d->sn_vec[type].list;
    fd_set *fds  =  &d->sn_vec[type].enabled_fds;
    QSockNot *sn;
    if ( ! list )
	return;
    sn = list->first();
    while ( sn && !(sn->obj == notifier && sn->fd == sockfd) )
	sn = list->next();
    if ( !sn ) // not found
	return;

    FD_CLR( sockfd, fds );			// clear fd bit
    FD_CLR( sockfd, sn->queue );
    d->sn_pending_list.removeRef( sn );		// remove from activation list
    list->remove();				// remove notifier found above

    if ( d->sn_highest == sockfd ) {		// find highest fd
	d->sn_highest = -1;
	for ( int i=0; i<3; i++ ) {
	    if ( d->sn_vec[i].list && ! d->sn_vec[i].list->isEmpty() )
		d->sn_highest = QMAX( d->sn_highest,  // list is fd-sorted
				      d->sn_vec[i].list->getFirst()->fd );
	}
    }
}