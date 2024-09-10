bool DVBevents::tableEIT( unsigned char* buffer )
{
	unsigned char* buf = buffer;
	unsigned int length, loop, sid, tid, eid, tsid, sn, lsn, nid;
	int i, sec;
	EventDesc *desc=0, *itdesc=0;
	EventSid *slist;
	QPtrList<EventDesc> *currentEvents;
	bool nodesc, parse;
	QDateTime start, cur, dt;
	unsigned int cdt = QDateTime::currentDateTime().toTime_t();

	tid = getBits(buf,0,8);
	length = getBits(buf,12,12);
	sid = getBits(buf,24,16);
	sn = getBits(buf,48,8);
	lsn = getBits(buf,56,8);
	tsid = getBits(buf,64,16);
	nid = getBits(buf,80,16);
	length -=11;
	buf +=14;

	slist = currentSrc->getEventSid( nid, tsid, sid );
	if ( !slist )
		return false;
	slist->lock();
	currentEvents = slist->getEvents();
	QPtrListIterator<EventDesc> it( *currentEvents );

	while ( length>4 ) {
		nodesc=parse=false;
		if ( !safeLen( buf+2 ) )
			goto stop;
		eid = getBits(buf,0,16);
		if ( !safeLen( buf+2+5 ) )
			goto stop;
		start = getDateTime( buf+2 );
		nodesc=parse=true;

		it.toFirst();
		while ( (desc=it.current())!=0 ) {
			if ( desc->sid==sid ) {
				if ( desc->startDateTime==start || desc->eid==eid ) {
					if ( desc->tid==0x4e && tid!=0x4e ) {
						parse = false;
						nodesc = false;
						break;
					}
					else {
						nodesc = false;
						if ( (cdt-desc->loop)<300 ) { // only reparse events every 300 seconds
							parse = false;
						}
						else {
							desc->extEvents.clear();
							desc->shortEvents.clear();
							desc->title=desc->subtitle="";
						}
						break;
					}
				}
			}
			++it;
		}

		if ( nodesc )
			desc = new EventDesc();
		if ( parse ) {
			if ( !safeLen( buf+10 ) )
				goto stop;
			desc->duration = getTime( buf+7 );
			if ( !safeLen( buf+11 ) )
				goto stop;
			desc->running = getBits(buf,80,3);
			desc->sid = sid;
			desc->tid = tid;
			desc->tsid = tsid;
			desc->nid = nid;
			desc->lsn = lsn;
			desc->sn = sn;
			desc->eid = eid;
			desc->loop = cdt;
		}

		if ( desc->sn != sn ) {
			slist->unlock();
			return false;
		}
		if ( !safeLen( buf+12 ) )
			goto stop;
		loop = getBits(buf,84,12);
		buf +=12;
		length -=(12+loop);
		while ( loop>0 ) {
			if ( parse ) {
				if ( !safeLen( buf+1 ) )
					goto stop;
				switch ( getBits(buf,0,8) ) {
					case 0x4D :
						if ( !shortEventDesc( buf, desc ) )
							goto stop;
						break;
					case 0x4E :
						if ( !extEventDesc( buf, desc ) )
							goto stop;
						break;
					default :
						break;
				}
			}
			if ( !safeLen( buf+2 ) )
				goto stop;
			loop -=( getBits(buf,8,8)+2 );
			buf +=( getBits(buf,8,8)+2 );
		}
//out:
		if ( parse ) {
			if ( !nodesc ) {
				if ( start==desc->startDateTime )
					goto ifend;
				currentEvents->take( currentEvents->find( desc ) );
			}
			desc->startDateTime = start;
			for ( i=0; i<(int)currentEvents->count(); i++ ) {
				itdesc = currentEvents->at(i);
				if ( desc->startDateTime<itdesc->startDateTime ) {
					currentEvents->insert( i, desc );
					break;
				}
				itdesc = 0;
			}
			if ( !itdesc )
				currentEvents->append( desc );
		}
ifend:
		if ( parse )
			++(desc->sn);
		if ( nodesc ) {
			cur = QDateTime::currentDateTime();
			dt = desc->startDateTime;
			sec = desc->duration.hour()*3600+desc->duration.minute()*60+desc->duration.second();
			if ( dt.addSecs( sec )<cur || desc->title.length()<3 ) {
				currentEvents->remove( desc );
			}
			else
				desc->source = currentSrc->getSource();
		}

	}
	slist->unlock();
	return true;
stop:
	slist->unlock();
	fprintf( stderr, "Stop parsing EIT (%d:%d)\n", adapter, tuner );
	if ( nodesc )
		delete desc;
	return false;
}