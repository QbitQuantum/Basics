GF_EXPORT
const char *gf_esd_get_textual_description(GF_ESD *esd)
{
	if (!esd || !esd->decoderConfig) return "Bad parameter";

	switch (esd->decoderConfig->streamType) {
	case GF_STREAM_OD:
		return "MPEG-4 Object Descriptor";
	case GF_STREAM_OCR:
		return "MPEG-4 Object Clock Reference";
	case GF_STREAM_SCENE:
		switch (esd->decoderConfig->objectTypeIndication) {
		case 0x0:
		case 0x1:
		case 0x2:
		case 0x3:
		case 0xFF:
			return "MPEG-4 BIFS Scene Description";
		case GPAC_OTI_SCENE_BIFS_EXTENDED:
			return "MPEG-4 Extended BIFS Scene Description";
		case GPAC_OTI_SCENE_AFX:
			if (!esd->decoderConfig->decoderSpecificInfo || !esd->decoderConfig->decoderSpecificInfo->data)
				return "AFX Unknown";
			return gf_afx_get_type_description(esd->decoderConfig->decoderSpecificInfo->data[0]);
		case GPAC_OTI_SCENE_LASER:
		{
			GF_LASERConfig l_cfg;
			gf_odf_get_laser_config(esd->decoderConfig->decoderSpecificInfo, &l_cfg);
			if (! l_cfg.newSceneIndicator ) return "LASeR Scene Segment Description";
		}
		return "LASeR Scene Description";
		case GPAC_OTI_SCENE_SYNTHESIZED_TEXTURE:
			return "MPEG-4 Synthesized Texture";
		case GPAC_OTI_SCENE_SAF:
			return "MPEG-4 SAF";
		case GPAC_OTI_3GPP2_CMF:
			return "3GPP2 CMF";
		default:
			return "Unknown Scene Type";
		}
		break;
	case GF_STREAM_VISUAL:
		switch (esd->decoderConfig->objectTypeIndication) {
		case GPAC_OTI_VIDEO_MPEG2_SIMPLE:
			return "MPEG-2 Visual Simple Profile";
		case GPAC_OTI_VIDEO_MPEG2_MAIN:
			return "MPEG-2 Visual Main Profile";
		case GPAC_OTI_VIDEO_MPEG2_SNR:
			return "MPEG-2 Visual SNR Profile";
		case GPAC_OTI_VIDEO_MPEG2_SPATIAL:
			return "MPEG-2 Visual SNR Profile";
		case GPAC_OTI_VIDEO_MPEG2_HIGH:
			return "MPEG-2 Visual SNR Profile";
		case GPAC_OTI_VIDEO_MPEG2_422:
			return "MPEG-2 Visual SNR Profile";
		case GPAC_OTI_VIDEO_MPEG1:
			return "MPEG-1 Video";
		case GPAC_OTI_IMAGE_JPEG:
			return "JPEG Image";
		case GPAC_OTI_IMAGE_PNG:
			return "PNG Image";
		case GPAC_OTI_IMAGE_JPEG_2000:
			return "JPEG2000 Image";
		case GPAC_OTI_VIDEO_MPEG4_PART2:
			return "MPEG-4 Part 2 Video";
		case GPAC_OTI_VIDEO_AVC:
			return "MPEG-4 AVC|H264 Video";
		case GPAC_OTI_VIDEO_SVC:
			return "MPEG-4 SVC Video";
		case GPAC_OTI_VIDEO_AVC_PS:
			return "MPEG-4 AVC|H264 Parameter Set";
		case GPAC_OTI_VIDEO_HEVC:
			return "MPEG-H HEVC Video";
		case GPAC_OTI_VIDEO_SHVC:
			return "MPEG-H SHVC Video";
		case GPAC_OTI_MEDIA_FFMPEG:
			return "GPAC FFMPEG Private Video";
		case GPAC_OTI_VIDEO_SMPTE_VC1:
			return "SMPTE VC-1 Video";
		case GPAC_OTI_VIDEO_DIRAC:
			return "Dirac Video";
		default:
			return "Unknown Video type";
		}
		break;
	case GF_STREAM_AUDIO:
		switch (esd->decoderConfig->objectTypeIndication) {
		case GPAC_OTI_AUDIO_AAC_MPEG2_MP:
			return "MPEG-2 AAC Main Profile";
		case GPAC_OTI_AUDIO_AAC_MPEG2_LCP:
			return "MPEG-2 AAC Low Complexity Profile";
		case GPAC_OTI_AUDIO_AAC_MPEG2_SSRP:
			return "MPEG-2 AAC Scaleable Sampling Rate Profile";
		case GPAC_OTI_AUDIO_MPEG2_PART3:
			return "MPEG-2 Audio Part 3";
		case GPAC_OTI_AUDIO_MPEG1:
			return "MPEG-1 Audio";
		case GPAC_OTI_AUDIO_AAC_MPEG4:
		{
#ifdef GPAC_DISABLE_AV_PARSERS
			return "MPEG-4 AAC";
#else
			GF_M4ADecSpecInfo a_cfg;
			if (!esd->decoderConfig->decoderSpecificInfo) return "MPEG-4 AAC";
			gf_m4a_get_config(esd->decoderConfig->decoderSpecificInfo->data, esd->decoderConfig->decoderSpecificInfo->dataLength, &a_cfg);
			return gf_m4a_object_type_name(a_cfg.base_object_type);
#endif
		}
		break;
		case GPAC_OTI_MEDIA_FFMPEG:
			return "GPAC FFMPEG Private Audio";
		case GPAC_OTI_AUDIO_EVRC_VOICE:
			return "EVRC Voice";
		case GPAC_OTI_AUDIO_SMV_VOICE:
			return "SMV Voice";
		case GPAC_OTI_AUDIO_AC3:
			return "AC-3 audio";
		case GPAC_OTI_AUDIO_EAC3:
			return "Enhanced AC-3 Audio";
		case GPAC_OTI_AUDIO_DRA:
			return "DRA Audio";
		case GPAC_OTI_AUDIO_ITU_G719:
			return "ITU G719 Audio";
		case GPAC_OTI_AUDIO_DTS_CA:
			return "DTS Coherent Acoustics audio";
		case GPAC_OTI_AUDIO_DTS_HD_HR:
			return "DTS-HD High Resolution audio";
		case GPAC_OTI_AUDIO_DTS_HD_MASTER:
			return "DTS-HD Master audios";
		default:
			return "Unknown Audio Type";
		}
		break;
	case GF_STREAM_MPEG7:
		return "MPEG-7 Description";
	case GF_STREAM_IPMP:
		return "MPEG-4 IPMP";
	case GF_STREAM_OCI:
		return "MPEG-4 OCI";
	case GF_STREAM_MPEGJ:
		return "MPEG-4 MPEG-J";
	case GF_STREAM_INTERACT:
		return "MPEG-4 User Interaction";
	case GF_STREAM_IPMP_TOOL:
		return "MPEG-4 IPMP Tool";
	case GF_STREAM_FONT:
		return "MPEG-4 Font Data";
	case GF_STREAM_TEXT:
		return "MPEG-4 Streaming Text";
	case GF_STREAM_ND_SUBPIC:
		return "Nero Digital Subpicture";

	case GF_STREAM_PRIVATE_SCENE:
		switch (esd->decoderConfig->objectTypeIndication) {
		case GPAC_OTI_PRIVATE_SCENE_GENERIC:
		{
			char *ext = strchr(esd->decoderConfig->decoderSpecificInfo->data + 4, '.');
			if (!ext) return "GPAC Internal Scene Description";
			ext += 1;
			if (!strnicmp(ext, "bt", 2))
				return "BT Scene Description";
			if (!strnicmp(ext, "xmt", 2))
				return "XMT Scene Description";
			if (!strnicmp(ext, "wrl", 3))
				return "VRML Scene Description";
			if (!strnicmp(ext, "x3d", 3))
				return "W3D Scene Description";
			if (!strnicmp(ext, "x3dv", 4))
				return "X3D Scene Description";
			if (!strnicmp(ext, "swf", 3))
				return "Flash (SWF) Scene Description";
			if (!strnicmp(ext, "xsr", 3))
				return "LASeR-ML Scene Description";
			if (!strnicmp(ext, "wgt", 3))
				return "W3C Widget Package";
			if (!strnicmp(ext, "mgt", 3))
				return "MPEG-U Widget Package";
		}
		return "GPAC Internal Scene Description";
		case GPAC_OTI_PRIVATE_SCENE_SVG:
			return "SVG";
		case GPAC_OTI_PRIVATE_SCENE_LASER:
			return "LASeR (XML)";
		case GPAC_OTI_PRIVATE_SCENE_XBL:
			return "XBL";
		case GPAC_OTI_PRIVATE_SCENE_EPG:
			return "DVB Event Information";
		case GPAC_OTI_PRIVATE_SCENE_WGT:
			return "W3C/MPEG-U Widget";
		case GPAC_OTI_SCENE_SVG:
			return "SVG over RTP";
		case GPAC_OTI_SCENE_SVG_GZ:
			return "SVG+gz over RTP";
		case GPAC_OTI_SCENE_DIMS:
			return "3GPP DIMS";
		default:
			return "Unknown Scene Description";
		}
		break;
	case GF_STREAM_PRIVATE_MEDIA:
		return "Opaque Decoder";
	case GF_STREAM_4CC:
		return gf_4cc_to_str(esd->decoderConfig->objectTypeIndication);
	default:
		return "Unknown Media Type";
	}
}