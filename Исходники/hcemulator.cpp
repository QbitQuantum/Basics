void CActiveWriter::RunL()
	{
	TPtr8 currentbuffer = (iWriteBuffers[0])->Des();

	iConsole.Printf(_L("Write of %d bytes (including header) returned result %d.\n"), currentbuffer.Length(), iStatus.Int());
	
	// the write has completed - clear up the buffer
	delete iWriteBuffers[0];
	iWriteBuffers.Remove(0);

	if (iWriteBuffers.Count())
		// more to send
		DoWrite();
	}