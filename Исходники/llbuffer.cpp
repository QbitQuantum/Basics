U8* LLBufferArray::seek(
	S32 channel,
	U8* start,
	S32 delta) const
{
	LLMemType m1(LLMemType::MTYPE_IO_BUFFER);
	const_segment_iterator_t it;
	const_segment_iterator_t end = mSegments.end();
	U8* rv = start;
	if(0 == delta)
	{
		if((U8*)npos == start)
		{
			// someone is looking for end of data. 
			segment_list_t::const_reverse_iterator rit = mSegments.rbegin();
			segment_list_t::const_reverse_iterator rend = mSegments.rend();
			while(rit != rend)
			{
				if(!((*rit).isOnChannel(channel)))
				{
					++rit;
					continue;
				}
				rv = (*rit).data() + (*rit).size();
				break;
			}
		}
		else if(start)
		{
			// This is sort of a weird case - check if zero bytes away
			// from current position is on channel and return start if
			// that is true. Otherwise, return NULL.
			it = getSegment(start);
			if((it == end) || !(*it).isOnChannel(channel))
			{
				rv = NULL;
			}
		}
		else
		{
			// Start is NULL, so return the very first byte on the
			// channel, or NULL.
			it = mSegments.begin();
			while((it != end) && !(*it).isOnChannel(channel))
			{
				++it;
			}
			if(it != end)
			{
				rv = (*it).data();
			}
		}
		return rv;
	}
	if(start)
	{
		it = getSegment(start);
		if((it != end) && (*it).isOnChannel(channel))
		{
			if(delta > 0)
			{
				S32 bytes_in_segment = (*it).size() - (start - (*it).data());
				S32 local_delta = llmin(delta, bytes_in_segment);
				rv += local_delta;
				delta -= local_delta;
				++it;
			}
			else
			{
				S32 bytes_in_segment = start - (*it).data();
				S32 local_delta = llmin(llabs(delta), bytes_in_segment);
				rv -= local_delta;
				delta += local_delta;
			}
		}
	}
	else if(delta < 0)
	{
		// start is NULL, and delta indicates seeking backwards -
		// return NULL.
		return NULL;
	}
	else
	{
		// start is NULL and delta > 0
		it = mSegments.begin();
	}
	if(delta > 0)
	{
		// At this point, we have an iterator into the segments, and
		// are seeking forward until delta is zero or we run out
		while(delta && (it != end))
		{
			if(!((*it).isOnChannel(channel)))
			{
				++it;
				continue;
			}
			if(delta <= (*it).size())
			{
				// it's in this segment
				rv = (*it).data() + delta;
			}
			delta -= (*it).size();
			++it;
		}
		if(delta && (it == end))
		{
			// Whoops - sought past end.
			rv = NULL;
		}
	}
	else //if(delta < 0)
	{
		// We are at the beginning of a segment, and need to search
		// backwards.
		segment_list_t::const_reverse_iterator rit(it);
		segment_list_t::const_reverse_iterator rend = mSegments.rend();
		while(delta && (rit != rend))
		{
			if(!((*rit).isOnChannel(channel)))
			{
				++rit;
				continue;
			}
			if(llabs(delta) <= (*rit).size())
			{
				// it's in this segment.
				rv = (*rit).data() + (*rit).size() + delta;
				delta = 0;
			}
			else
			{
				delta += (*rit).size();
			}
			++rit;
		}
		if(delta && (rit == rend))
		{
			// sought past the beginning.
			rv = NULL;
		}
	}
	return rv;
}