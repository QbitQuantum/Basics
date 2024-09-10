int AvFormatDecoderDVD::ReadPacket(AVFormatContext *ctx, AVPacket* pkt)
{
    int result = 0;

    if (m_framesReq > 0)
    {
        m_framesReq--;

        if (m_lastVideoPkt)
        {
            av_copy_packet(pkt, m_lastVideoPkt);

            if (m_lastVideoPkt->pts != AV_NOPTS_VALUE)
                m_lastVideoPkt->pts += pkt->duration;

            if (m_lastVideoPkt->dts != AV_NOPTS_VALUE)
                m_lastVideoPkt->dts += pkt->duration;
        }
        else
        {
            LOG(VB_GENERAL, LOG_ERR, LOC + QString( "Need to generate frame @ %1 - %2 but no frame available!")
                .arg(pkt->pts)
                .arg(m_framesReq));
        }
    }
    else
    {
        bool gotPacket;

        do
        {
            gotPacket = true;

            result = av_read_frame(ctx, pkt);

            while (result == AVERROR_EOF && errno == EAGAIN)
            {
                if (ringBuffer->DVD()->IsReadingBlocked())
                {
                    if (ringBuffer->DVD()->GetLastEvent() == DVDNAV_HOP_CHANNEL)
                    {
                        // Non-seamless jump - clear all buffers
                        m_framesReq = 0;
                        ReleaseContext(m_curContext);

                        while (m_contextList.size() > 0)
                            m_contextList.takeFirst()->DecrRef();

                        Reset(true, false, false);
                        m_audio->Reset();
                        m_parent->DiscardVideoFrames(false);
                    }
                    ringBuffer->DVD()->UnblockReading();
                    result = av_read_frame(ctx, pkt);
                }
                else
                {
                    break;
                }
            }

            if (result >= 0)
            {
                pkt->dts = ringBuffer->DVD()->AdjustTimestamp(pkt->dts);
                pkt->pts = ringBuffer->DVD()->AdjustTimestamp(pkt->pts);

                if (m_returnContext)
                {
                    // We've jumped in a slideshow and have had to jump again
                    // to find the right video packet to show so only allow
                    // the packets through that let us find it.
                    gotPacket = false;

                    AVStream *curstream = ic->streams[pkt->stream_index];

                    if ((curstream->codec->codec_type == AVMEDIA_TYPE_VIDEO) ||
                        (curstream->codec->codec_id == AV_CODEC_ID_DVD_NAV))
                    {
                        // Allow video or NAV packets through
                        gotPacket = true;
                    }
                }
            }
        }while(!gotPacket);
    }

    return result;
}