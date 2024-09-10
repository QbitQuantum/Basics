bool DocumentImporter::addExtraTags(const COLLADAFW::UniqueId &uid, ExtraTags *extra_tags)
{
	uid_tags_map[uid.toAscii()] = extra_tags;
	return true;
}