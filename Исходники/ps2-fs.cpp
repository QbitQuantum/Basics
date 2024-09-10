Common::WriteStream *Ps2FilesystemNode::createWriteStream() {
	return PS2FileStream::makeFromPath(getPath(), true);
}