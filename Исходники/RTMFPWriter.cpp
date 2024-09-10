void RTMFPWriter::flush(BinaryWriter& writer,UInt64 stage,UInt8 flags,bool header,const UInt8* data,UInt16 size) {
	if(_stageAck==0 && header)
		flags |= MESSAGE_HEADER;
	if(size==0)
		flags |= MESSAGE_ABANDONMENT;
	if(state()==CLOSED && _messages.size()==1) // On LAST message
		flags |= MESSAGE_END;

	// TRACE("RTMFPWriter ",id," stage ",stage);

	writer.write8(flags);

	if(header) {
		writer.write7BitLongValue(id);
		writer.write7BitLongValue(stage);
		writer.write7BitLongValue(stage-_stageAck);

		// signature
		if(_stageAck==0) {
			writer.writeString8(signature);
			// No write this in the case where it's a new flow!
			if(flowId>0) {
				writer.write8(1+Util::Get7BitValueSize(flowId)); // following size
				writer.write8(0x0a); // Unknown!
				writer.write7BitLongValue(flowId);
			}
			writer.write8(0); // marker of end for this part
		}

	}

	if (size > 0)
		writer.writeRaw(data, size);
}