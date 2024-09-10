status_t
MovieEncoder::Encode(const media_format_family& family,
					const media_format& format,
					const media_codec_info& info,
					const color_space& space)
{
	SetMediaFormatFamily(family);
	SetMediaFormat(format);
	SetMediaCodecInfo(info);
	SetColorSpace(space);
	
	return Encode();
}