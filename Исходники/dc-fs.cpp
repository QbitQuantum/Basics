Common::SeekableReadStream *RoninCDFileNode::createReadStream() {
	return StdioStream::makeFromPath(getPath().c_str(), false);
}