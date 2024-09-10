int PressSensor::readEvents(sensors_event_t* data, int count)
{
	int i;
    if (count < 1)
        return -EINVAL;

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
        return n;

    int numEventReceived = 0;
    input_event const* event;

    while (count && mInputReader.readEvent(&event)) {
        int type = event->type;
        if ((type == EV_ABS) || (type == EV_REL) || (type == EV_KEY)) {
            processEvent(event->code, event->value);
            mInputReader.next();
        } else if (type == EV_SYN) {
            int64_t time = timevalToNano(event->time);
			for(i = 0 ; i< sensors && mPendingMask && count ;i++){
			  	 	if(mPendingMask & (1 << i)){
						mPendingMask &= ~(1 << i);
						mPendingEvent[i].timestamp = time;
						if (mEnabled[i]) {
							*data++ = mPendingEvent[i];
							count--;
							numEventReceived++;
						}
			  	 	}
	       }
		   if (!mPendingMask) {
		       mInputReader.next();
		   }
        } else {
            mInputReader.next();
        }
    }

    return numEventReceived;
}