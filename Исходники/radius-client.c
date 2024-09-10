/*
 *	Compare two RADIUS_PACKET data structures, based on a number
 *	of criteria.
 */
static int send_one_packet(radclient_t *radclient)
{
    int i;

    assert(radclient->done == 0);

    /*
     *	Remember when we have to wake up, to re-send the
     *	request, of we didn't receive a response.
     */
    if ((sleep_time == -1) ||
            (sleep_time > (int) timeout))
    {
        sleep_time = (int) timeout;
    }

    /*
     *	Haven't sent the packet yet.  Initialize it.
     */
    if (radclient->request->id == -1)
    {
        int found = 0;

        assert(radclient->reply == NULL);

        /*
         *	Find a free packet Id
         */
        for (i = 0; i < 256; i++)
        {
            if (radius_id[(last_used_id + i) & 0xff] == 0)
            {
                last_used_id = (last_used_id + i) & 0xff;
                radius_id[last_used_id] = 1;
                radclient->request->id = last_used_id++;
                found = 1;
                break;
            }
        }

        /*
         *	Didn't find a free packet ID, we're not done,
         *	we don't sleep, and we stop trying to process
         *	this packet.
         */
        if (!found)
        {
            done = 0;
            sleep_time = 0;
            return 0;
        }

        assert(radclient->request->id != -1);
        assert(radclient->request->data == NULL);

        librad_md5_calc(radclient->request->vector, radclient->request->vector,
                        sizeof(radclient->request->vector));

        /*
         *	Update the password, so it can be encrypted with the
         *	new authentication vector.
         */
        if (radclient->password[0] != '\0')
        {
            VALUE_PAIR *vp;

            if ((vp = pairfind(radclient->request->vps, PW_PASSWORD)) != NULL)
            {
                strNcpy((char *)vp->strvalue, radclient->password, sizeof(vp->strvalue));
                vp->length = strlen(vp->strvalue);

            }
            else if ((vp = pairfind(radclient->request->vps, PW_CHAP_PASSWORD)) != NULL)
            {
                strNcpy((char *)vp->strvalue, radclient->password, sizeof(vp->strvalue));
                vp->length = strlen(vp->strvalue);

                rad_chap_encode(radclient->request, (char *) vp->strvalue, radclient->request->id, vp);
                vp->length = 17;
            }
        }

        radclient->timestamp = time(NULL);
        radclient->tries = 1;
        radclient->resend++;

        /*
         *	Duplicate found.  Serious error!
         */
    }
    else  		/* radclient->request->id >= 0 */
    {
        time_t now = time(NULL);

        /*
         *	FIXME: Accounting packets are never retried!
         *	The Acct-Delay-Time attribute is updated to
         *	reflect the delay, and the packet is re-sent
         *	from scratch!
         */

        /*
         *	Not time for a retry, do so.
         */
        if ((now - radclient->timestamp) < timeout)
        {
            /*
             *	When we walk over the tree sending
             *	packets, we update the minimum time
             *	required to sleep.
             */
            if ((sleep_time == -1) ||
                    (sleep_time > (now - radclient->timestamp)))
            {
                sleep_time = now - radclient->timestamp;
            }
            return 0;
        }

        /*
         *	We're not trying later, maybe the packet is done.
         */
        if (radclient->tries == retries)
        {
            assert(radclient->request->id >= 0);

            /*
             *	Delete the request from the tree of
             *	outstanding requests.
             */

            fprintf(stderr, "radclient: no response from server for ID %d\n", radclient->request->id);
            /*
             *	Normally we mark it "done" when we've received
             *	the response, but this is a special case.
             */
            if (radclient->resend == resend_count)
            {
                radclient->done = 1;
            }
            totallost++;
            return -1;
        }

        /*
         *	We are trying later.
         */
        radclient->timestamp = now;
        radclient->tries++;
    }


    /*
     *	Send the packet.
     */
    if (rad_send(radclient->request, NULL, secret) < 0)
    {
        fprintf(stderr, "radclient: Failed to send packet for ID %d: %s\n",
                radclient->request->id, librad_errstr);
    }

    return 0;
}