status_t
FilePlaylistItem::SetAttribute(const Attribute& attribute,
	const BString& string)
{
	switch (attribute) {
		case ATTR_STRING_NAME:
		{
			BEntry entry(&fRefs[0], false);
			return entry.Rename(string.String(), false);
		}
	
		case ATTR_STRING_KEYWORDS:
			return _SetAttribute("Meta:Keywords", B_STRING_TYPE,
				string.String(), string.Length());

		case ATTR_STRING_ARTIST:
			return _SetAttribute("Audio:Artist", B_STRING_TYPE,
				string.String(), string.Length());
		case ATTR_STRING_AUTHOR:
			return _SetAttribute("Media:Author", B_STRING_TYPE,
				string.String(), string.Length());
		case ATTR_STRING_ALBUM:
			return _SetAttribute("Audio:Album", B_STRING_TYPE,
				string.String(), string.Length());
		case ATTR_STRING_TITLE:
			return _SetAttribute("Media:Title", B_STRING_TYPE,
				string.String(), string.Length());
		case ATTR_STRING_AUDIO_BITRATE:
			return _SetAttribute("Audio:Bitrate", B_STRING_TYPE,
				string.String(), string.Length());
		case ATTR_STRING_VIDEO_BITRATE:
			return _SetAttribute("Video:Bitrate", B_STRING_TYPE,
				string.String(), string.Length());

		default:
			return B_NOT_SUPPORTED;
	}
}