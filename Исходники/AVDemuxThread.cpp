void AVDemuxThread::run()
{
    m_buffering = false;
    end = false;
    if (audio_thread && !audio_thread->isRunning())
        audio_thread->start(QThread::HighPriority);
    if (video_thread && !video_thread->isRunning())
        video_thread->start();

    int stream = 0;
    Packet pkt;
    pause(false);
    qDebug("get av queue a/v thread = %p %p", audio_thread, video_thread);
    PacketBuffer *aqueue = audio_thread ? audio_thread->packetQueue() : 0;
    PacketBuffer *vqueue = video_thread ? video_thread->packetQueue() : 0;
    // aqueue as a primary buffer: music with/without cover
    AVThread* thread = !video_thread || (audio_thread && demuxer->hasAttacedPicture()) ? audio_thread : video_thread;
    m_buffer = thread->packetQueue();
    const qint64 buf2 = aqueue ? aqueue->bufferValue() : 1; // TODO: may be changed by user. Deal with audio track change
    if (aqueue) {
        aqueue->clear();
        aqueue->setBlocking(true);
    }
    if (vqueue) {
        vqueue->clear();
        vqueue->setBlocking(true);
    }
    connect(thread, SIGNAL(seekFinished(qint64)), this, SIGNAL(seekFinished(qint64)), Qt::DirectConnection);
    seek_tasks.clear();
    int was_end = 0;
    if (ademuxer) {
        ademuxer->seek(0LL);
    }
    qreal last_apts = 0;
    qreal last_vpts = 0;
    while (!end) {
        processNextSeekTask();
        //vthread maybe changed by AVPlayer.setPriority() from no dec case
        vqueue = video_thread ? video_thread->packetQueue() : 0;
        if (demuxer->atEnd()) {
            // if avthread may skip 1st eof packet because of a/v sync
            const int kMaxEof = 1;//if buffer packet, we can use qMax(aqueue->bufferValue(), vqueue->bufferValue()) and not call blockEmpty(false);
            if (aqueue && (!was_end || aqueue->isEmpty())) {
                if (was_end < kMaxEof)
                    aqueue->put(Packet::createEOF());
                const qreal dpts = last_vpts - last_apts;
                if (dpts > 0.1) {
                    Packet fake_apkt;
                    fake_apkt.duration = last_vpts - qMin(thread->clock()->videoTime(), thread->clock()->value()); // FIXME: when clock value < 0?
                    qDebug("audio is too short than video: %.3f, fake_apkt.duration: %.3f", dpts, fake_apkt.duration);
                    last_apts = last_vpts = 0; // if not reset to 0, for example real eof pts, then no fake apkt after seek because dpts < 0
                    aqueue->put(fake_apkt);
                }
                aqueue->blockEmpty(was_end >= kMaxEof); // do not block if buffer is not enough. block again on seek
            }
            if (vqueue && (!was_end || vqueue->isEmpty())) {
                if (was_end < kMaxEof)
                    vqueue->put(Packet::createEOF());
                vqueue->blockEmpty(was_end >= kMaxEof);
            }
            if (m_buffering) {
                m_buffering = false;
                Q_EMIT mediaStatusChanged(QtAV::BufferedMedia);
            }
            was_end = qMin(was_end + 1, kMaxEof);
            bool exit_thread = !user_paused;
            if (aqueue)
                exit_thread &= aqueue->isEmpty();
            if (vqueue)
                exit_thread &= vqueue->isEmpty();
            if (exit_thread) {
                if (!(mediaEndAction() & MediaEndAction_Pause))
                    break;
                pause(true);
                Q_EMIT requestClockPause(true);
                if (aqueue)
                    aqueue->blockEmpty(true);
                if (vqueue)
                    vqueue->blockEmpty(true);
            }
            // wait for a/v thread finished
            msleep(100);
            continue;
        }
        was_end = 0;
        if (tryPause()) {
            continue; //the queue is empty and will block
        }
        updateBufferState();
        if (!demuxer->readFrame()) {
            continue;
        }
        stream = demuxer->stream();
        pkt = demuxer->packet();
        Packet apkt;
        bool audio_has_pic = demuxer->hasAttacedPicture();
        int a_ext = 0;
        if (ademuxer) {
            QMutexLocker locker(&buffer_mutex);
            Q_UNUSED(locker);
            if (ademuxer) {
                a_ext = -1;
                audio_has_pic = ademuxer->hasAttacedPicture();
                // FIXME: buffer full but buffering!!!
                // avoid read external track everytime. aqueue may not block full
                // vqueue will not block if aqueue is not enough
                if (!aqueue->isFull() || aqueue->isBuffering()) {
                    if (ademuxer->readFrame()) {
                        if (ademuxer->stream() == ademuxer->audioStream()) {
                            a_ext = 1;
                            apkt = ademuxer->packet();
                        }
                    }
                    // no continue otherwise. ademuxer finished earlier than demuxer
                }
            }
        }
        //qDebug("vqueue: %d, aqueue: %d/isbuffering %d isfull: %d, buffer: %d/%d", vqueue->size(), aqueue->size(), aqueue->isBuffering(), aqueue->isFull(), aqueue->buffered(), aqueue->bufferValue());

        //QMutexLocker locker(&buffer_mutex); //TODO: seems we do not need to lock
        //Q_UNUSED(locker);
        /*1 is empty but another is enough, then do not block to
          ensure the empty one can put packets immediatly.
          But usually it will not happen, why?
        */
        /* demux thread will be blocked only when 1 queue is full and still put
         * if vqueue is full and aqueue becomes empty, then demux thread
         * will be blocked. so we should wake up another queue when empty(or threshold?).
         * TODO: the video stream and audio stream may be group by group. provide it
         * stream data: aaaaaaavvvvvvvaaaaaaaavvvvvvvvvaaaaaa, it happens
         * stream data: aavavvavvavavavavavavavavvvaavavavava, it's ok
         */
        //TODO: use cache queue, take from cache queue if not empty?
        const bool a_internal = stream == demuxer->audioStream();
        if (a_internal || a_ext > 0) {//apkt.isValid()) {
            if (a_internal && !a_ext) // internal is always read even if external audio used
                apkt = demuxer->packet();
            last_apts = apkt.pts;
            /* if vqueue if not blocked and full, and aqueue is empty, then put to
             * vqueue will block demuex thread
             */
            if (aqueue) {
                if (!audio_thread || !audio_thread->isRunning()) {
                    aqueue->clear();
                    continue;
                }
                // must ensure bufferValue set correctly before continue
                if (m_buffer != aqueue)
                    aqueue->setBufferValue(m_buffer->isBuffering() ? std::numeric_limits<qint64>::max() : buf2);
                // always block full if no vqueue because empty callback may set false
                // attached picture is cover for song, 1 frame
                aqueue->blockFull(!video_thread || !video_thread->isRunning() || !vqueue || audio_has_pic);
                // external audio: a_ext < 0, stream = audio_idx=>put invalid packet
                if (a_ext >= 0)
                    aqueue->put(apkt); //affect video_thread
            }
        }
        // always check video stream if use external audio
        if (stream == demuxer->videoStream()) {
            if (vqueue) {
                if (!video_thread || !video_thread->isRunning()) {
                    vqueue->clear();
                    continue;
                }
                vqueue->blockFull(!audio_thread || !audio_thread->isRunning() || !aqueue || aqueue->isEnough());
                vqueue->put(pkt); //affect audio_thread
                last_vpts = pkt.pts;
            }
        } else if (demuxer->subtitleStreams().contains(stream)) { //subtitle
            Q_EMIT internalSubtitlePacketRead(demuxer->subtitleStreams().indexOf(stream), pkt);
        } else {
            continue;
        }
    }
    m_buffering = false;
    m_buffer = 0;
    while (audio_thread && audio_thread->isRunning()) {
        qDebug("waiting audio thread.......");
        Packet quit_pkt(Packet::createEOF());
        quit_pkt.position = 0;
        aqueue->put(quit_pkt);
        aqueue->blockEmpty(false); //FIXME: why need this
        audio_thread->pause(false);
        audio_thread->wait(500);
    }
    while (video_thread && video_thread->isRunning()) {
        qDebug("waiting video thread.......");
        Packet quit_pkt(Packet::createEOF());
        quit_pkt.position = 0;
        vqueue->put(quit_pkt);
        vqueue->blockEmpty(false);
        video_thread->pause(false);
        video_thread->wait(500);
    }
    thread->disconnect(this, SIGNAL(seekFinished(qint64)));
    qDebug("Demux thread stops running....");
    Q_EMIT mediaStatusChanged(QtAV::EndOfMedia);
}