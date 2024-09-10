int SrsRtpConn::on_udp_packet(sockaddr_in* from, char* buf, int nb_buf)
{
    int ret = ERROR_SUCCESS;

    pprint->elapse();

    if (true) {
        SrsStream stream;

        if ((ret = stream.initialize(buf, nb_buf)) != ERROR_SUCCESS) {
            return ret;
        }
    
        SrsRtpPacket pkt;
        if ((ret = pkt.decode(&stream)) != ERROR_SUCCESS) {
            srs_error("rtsp: decode rtp packet failed. ret=%d", ret);
            return ret;
        }

        if (pkt.chunked) {
            if (!cache) {
                cache = new SrsRtpPacket();
            }
            cache->copy(&pkt);
            cache->payload->append(pkt.payload->bytes(), pkt.payload->length());
            if (!cache->completed && pprint->can_print()) {
                srs_trace("<- "SRS_CONSTS_LOG_STREAM_CASTER" rtsp: rtp chunked %dB, age=%d, vt=%d/%u, sts=%u/%#x/%#x, paylod=%dB", 
                    nb_buf, pprint->age(), cache->version, cache->payload_type, cache->sequence_number, cache->timestamp, cache->ssrc, 
                    cache->payload->length()
                );
                return ret;
            }
        } else {
            srs_freep(cache);
            cache = new SrsRtpPacket();
            cache->reap(&pkt);
        }
    }

    if (pprint->can_print()) {
        srs_trace("<- "SRS_CONSTS_LOG_STREAM_CASTER" rtsp: rtp #%d %dB, age=%d, vt=%d/%u, sts=%u/%u/%#x, paylod=%dB, chunked=%d", 
            stream_id, nb_buf, pprint->age(), cache->version, cache->payload_type, cache->sequence_number, cache->timestamp, cache->ssrc, 
            cache->payload->length(), cache->chunked
        );
    }

    // always free it.
    SrsAutoFree(SrsRtpPacket, cache);
    
    if ((ret = rtsp->on_rtp_packet(cache, stream_id)) != ERROR_SUCCESS) {
        srs_error("rtsp: process rtp packet failed. ret=%d", ret);
        return ret;
    }

    return ret;
}