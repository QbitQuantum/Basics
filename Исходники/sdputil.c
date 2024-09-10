int sdputil_init(SDP_DESCR_T *pSdp,
                 uint8_t payloadType,
                 unsigned int clockRateHz,
                 XC_CODEC_TYPE_T codecType,
                 const char *pDstHost,
                 uint16_t dstPort,
                 uint16_t dstPortRtcp,
                 const SRTP_CTXT_T *pSrtp,
                 const DTLS_CFG_T *pDtlsCfg,
                 const STUN_REQUESTOR_CFG_T *pStunCfg,
                 const SDP_CODEC_PARAM_T *pCodecSpecific,
                 const FRAME_RATE_T *pFps,
                 const VID_ENCODER_FBREQUEST_T *pFbReq) {

  int rc = 0;
  char tmp[128];
  struct sockaddr_storage connectip;

  if(!pSdp || payloadType > 0x7f || !pDstHost) {
    return -1;
  }

  memset(&connectip, 0, sizeof(connectip));
  if(!net_isipv4(pDstHost) && !net_isipv6(pDstHost)) {
    //
    // INADDR_NONE
    //
    pDstHost = "0.0.0.0";
  }

  net_getaddress(pDstHost, &connectip);
  if(INET_ADDR_VALID(connectip) && INET_IS_MULTICAST(connectip)) {
    pSdp->c.ttl = 64;
  } else if(INET_ADDR_VALID(connectip) && INET_ADDR_LOCALHOST(connectip)) {
    pSdp->c.ttl = 0;
  } else {
    //connectip.s_addr = net_getlocalip();

    //
    // For remote unicast destinations, leave the remote ip into the 'c=' field
    // which may be contrary to RFC4566
    //
    //connectip.s_addr = INADDR_ANY;

    pSdp->c.ttl = 0;
  }

  pSdp->c.ip_family = connectip.ss_family;
  strncpy(pSdp->c.iphost, INET_NTOP(connectip, tmp, sizeof(tmp)), sizeof(pSdp->c.iphost));

  //
  // Only write the RTCP port attribute in the SDP if using a non-default port
  //
  if(dstPortRtcp == RTCP_PORT_FROM_RTP(dstPort)) {
    dstPortRtcp = 0;   
  } 

  if(pFps && pFps->clockHz > 0 && pFps->frameDeltaHz > 0) {
    memcpy(&pSdp->vid.fps, pFps, sizeof(pSdp->vid.fps));
  }
  switch(codecType) {

    case XC_CODEC_TYPE_H264:
    case XC_CODEC_TYPE_MPEG4V:
    case XC_CODEC_TYPE_H263:
    case XC_CODEC_TYPE_H263_PLUS:
    case XC_CODEC_TYPE_VP8:
      pSdp->vid.common.available = 1;
      pSdp->vid.common.codecType = codecType;
      pSdp->vid.common.payloadType = payloadType;
      pSdp->vid.common.port = dstPort;
      pSdp->vid.common.portRtcp = dstPortRtcp;
      pSdp->vid.common.clockHz = clockRateHz;
      pSdp->vid.common.transType = SDP_TRANS_TYPE_RTP_UDP;

      if(pDtlsCfg) {
        if(pDtlsCfg->dtls_srtp) {
          pSdp->vid.common.transType = SDP_TRANS_TYPE_SRTP_DTLS_UDP;
        } else {
          pSdp->vid.common.transType = SDP_TRANS_TYPE_DTLS_UDP;
        }
        memcpy(&pSdp->vid.common.fingerprint, &pDtlsCfg->fingerprint, sizeof(pSdp->vid.common.fingerprint));
      }
      if(pSrtp) {
        pSdp->vid.common.transType =  SDP_TRANS_TYPE_SRTP_SDES_UDP;
        if((rc = sdputil_initsrtp(&pSdp->vid.common.srtp, pSrtp)) < 0) {
          return rc;
        }
      }
      if(pStunCfg && pStunCfg->bindingRequest) {
        if(pStunCfg->reqUsername) {
          strncpy(pSdp->vid.common.ice.ufrag, pStunCfg->reqUsername, STUN_STRING_MAX - 1);
        }
        if(pStunCfg->reqPass) {
          strncpy(pSdp->vid.common.ice.pwd, pStunCfg->reqPass, STUN_STRING_MAX - 1);
        }
      }
      
      if(codecType == XC_CODEC_TYPE_H264) {
        strncpy(pSdp->vid.common.encodingName, SDP_RTPMAP_ENCODINGNAME_H264,
          sizeof(pSdp->vid.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_MPEG4V) {
        strncpy(pSdp->vid.common.encodingName, SDP_RTPMAP_ENCODINGNAME_MPEG4V,
          sizeof(pSdp->vid.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_H263) {
        strncpy(pSdp->vid.common.encodingName, SDP_RTPMAP_ENCODINGNAME_H263,
          sizeof(pSdp->vid.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_H263_PLUS) {
        strncpy(pSdp->vid.common.encodingName, SDP_RTPMAP_ENCODINGNAME_H263_PLUS,
          sizeof(pSdp->vid.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_VP8) {
        strncpy(pSdp->vid.common.encodingName, SDP_RTPMAP_ENCODINGNAME_VP8,
          sizeof(pSdp->vid.common.encodingName));
      }

      break;
    case XC_CODEC_TYPE_AAC:
    case XC_CODEC_TYPE_AMRNB:
    case XC_CODEC_TYPE_SILK:
    case XC_CODEC_TYPE_OPUS:
    case XC_CODEC_TYPE_G711_MULAW:
    case XC_CODEC_TYPE_G711_ALAW:
      pSdp->aud.common.available = 1;
      pSdp->aud.common.codecType = codecType;
      pSdp->aud.common.payloadType = payloadType;
      pSdp->aud.common.port = dstPort;
      pSdp->aud.common.portRtcp = dstPortRtcp;
      pSdp->aud.common.clockHz = clockRateHz;
      pSdp->aud.common.transType = SDP_TRANS_TYPE_RTP_UDP;

      if(pDtlsCfg) {
        if(pDtlsCfg->dtls_srtp) {
          pSdp->aud.common.transType = SDP_TRANS_TYPE_SRTP_DTLS_UDP;
        } else {
          pSdp->aud.common.transType = SDP_TRANS_TYPE_DTLS_UDP;
        }
        memcpy(&pSdp->aud.common.fingerprint, &pDtlsCfg->fingerprint, sizeof(pSdp->aud.common.fingerprint));
      }
      if(pSrtp) {
        pSdp->aud.common.transType =  SDP_TRANS_TYPE_SRTP_SDES_UDP;
        if((rc = sdputil_initsrtp(&pSdp->aud.common.srtp, pSrtp)) < 0) {
          return rc;
        }
      }

      if(pStunCfg && pStunCfg->bindingRequest) { 
        if(pStunCfg->reqUsername) {
          strncpy(pSdp->aud.common.ice.ufrag, pStunCfg->reqUsername, STUN_STRING_MAX - 1);
        }
        if(pStunCfg->reqPass) {
          strncpy(pSdp->aud.common.ice.pwd, pStunCfg->reqPass, STUN_STRING_MAX - 1);
        }
      }

      if(codecType == XC_CODEC_TYPE_AAC) {
        strncpy(pSdp->aud.common.encodingName, SDP_RTPMAP_ENCODINGNAME_AAC,
          sizeof(pSdp->aud.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_AMRNB) {
        strncpy(pSdp->aud.common.encodingName, SDP_RTPMAP_ENCODINGNAME_AMR,
          sizeof(pSdp->aud.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_SILK) {
        strncpy(pSdp->aud.common.encodingName, SDP_RTPMAP_ENCODINGNAME_SILK,
          sizeof(pSdp->aud.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_OPUS) {
        strncpy(pSdp->aud.common.encodingName, SDP_RTPMAP_ENCODINGNAME_OPUS,
          sizeof(pSdp->aud.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_G711_MULAW) {
        strncpy(pSdp->aud.common.encodingName, SDP_RTPMAP_ENCODINGNAME_PCMU,
          sizeof(pSdp->aud.common.encodingName));
      } else if(codecType == XC_CODEC_TYPE_G711_ALAW) {
        strncpy(pSdp->aud.common.encodingName, SDP_RTPMAP_ENCODINGNAME_PCMA,
          sizeof(pSdp->aud.common.encodingName));
      }

      break;
    case MEDIA_FILE_TYPE_MP2TS:
      pSdp->vid.common.available = 1;
      pSdp->vid.common.codecType = MEDIA_FILE_TYPE_MP2TS;
      pSdp->vid.common.payloadType = payloadType;
      pSdp->vid.common.port = dstPort;
      pSdp->vid.common.portRtcp = dstPortRtcp;
      pSdp->vid.common.clockHz = 90000;

      if(pSrtp) {
        pSdp->vid.common.transType =  SDP_TRANS_TYPE_SRTP_SDES_UDP;
        if((rc = sdputil_initsrtp(&pSdp->vid.common.srtp, pSrtp)) < 0) {
          return rc;
        }
      }

      strncpy(pSdp->vid.common.encodingName, SDP_RTPMAP_ENCODINGNAME_MP2TS,
          sizeof(pSdp->vid.common.encodingName));
      break;
    default:
      return -1;
  }
 
  //
  // Advertise any a=rtcp-fb:  SDP flags
  //
  if(pSdp->vid.common.available) {
   if(pFbReq && (pFbReq->firCfg.fir_send_from_decoder || pFbReq->firCfg.fir_send_from_local ||
                 pFbReq->firCfg.fir_send_from_remote || pFbReq->firCfg.fir_send_from_capture)) {
      pSdp->vid.common.rtcpfb.fmtidmin1 = pSdp->vid.common.payloadType + 1;
      pSdp->vid.common.rtcpfb.flags |= SDP_RTCPFB_TYPE_CCM | SDP_RTCPFB_TYPE_CCM_FIR;
    }
   if(pFbReq && pFbReq->nackRtpRetransmit) {
    pSdp->vid.common.rtcpfb.flags |= SDP_RTCPFB_TYPE_NACK | SDP_RTCPFB_TYPE_NACK_GENERIC;
   }
    //pSdp->vid.common.rtcpfb.flags |= SDP_RTCPFB_TYPE_TRRINT;
    //pSdp->vid.common.rtcpfb.trrIntervalMs |= 30;
  }

  //
  // Codec specific default settings
  //
  switch(codecType) {

    case XC_CODEC_TYPE_H264:

      if(pCodecSpecific && (pCodecSpecific->flags & SDP_CODEC_PARAM_FLAGS_PKTZMODE)) {

        switch(pCodecSpecific->u.pktzMode) {
          case PKTZ_H264_MODE_0:
            pSdp->vid.u.h264.packetization_mode = 0;
            break;
          case PKTZ_H264_MODE_2:
            LOG(X_WARNING("H.264 NAL Packetization mode 2 not supported.  Using mode 1")); 
          case PKTZ_H264_MODE_1:
          case PKTZ_H264_MODE_NOTSET:
          default:
            pSdp->vid.u.h264.packetization_mode = 1;
            break;
       }

     }

     break;

    case XC_CODEC_TYPE_MPEG4V:

      pSdp->vid.u.mpg4v.profile_level_id = 1;
      break;

    case XC_CODEC_TYPE_VP8:
      break;

    case XC_CODEC_TYPE_AAC:
      strncpy(pSdp->aud.u.aac.mode, "AAC-hbr", sizeof(pSdp->aud.u.aac.mode));
      pSdp->aud.u.aac.sizelength = 13;
      pSdp->aud.u.aac.indexlength = 3;
      pSdp->aud.u.aac.indexdeltalength = 3;
      break;

    case XC_CODEC_TYPE_AMRNB:

      pSdp->aud.channels = 1;
      pSdp->aud.u.amr.octet_align = 1;

      break;

    case XC_CODEC_TYPE_SILK:

      if(pCodecSpecific && (pCodecSpecific->flags & SDP_CODEC_PARAM_FLAGS_CHANNELS)) {
        pSdp->aud.channels = pCodecSpecific->u.channels;
      } else {
        pSdp->aud.channels = 1;
      }

      //pSdp->aud.u.silk.dummy = 0;

      break;

    case XC_CODEC_TYPE_OPUS:

      if(pCodecSpecific && (pCodecSpecific->flags & SDP_CODEC_PARAM_FLAGS_CHANNELS)) {
        pSdp->aud.channels = pCodecSpecific->u.channels;;
      } else {
        pSdp->aud.channels = 1;
      }

      break;

    case XC_CODEC_TYPE_G711_MULAW:
    case XC_CODEC_TYPE_G711_ALAW:

      pSdp->aud.channels = 1;
      break;

    default:
      break;
  }

  return rc;
}