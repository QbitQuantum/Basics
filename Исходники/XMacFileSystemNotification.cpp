VError XMacFileSystemNotification::StartWatchingForChanges( const VFolder &inFolder, VFileSystemNotifier::EventKind inKindFilter, VFileSystemNotifier::IEventHandler *inHandler, sLONG inLatency )
{
	// We need to get the folder's path into an array for us to pass along to the OS call.
	VString posixPathString;
	inFolder.GetPath( posixPathString, FPS_POSIX);

	VStringConvertBuffer buffer( posixPathString, VTC_UTF_8);
	std::string posixPath( buffer.GetCPointer());

	CFStringRef pathRef = posixPathString.MAC_RetainCFStringCopy();
	CFArrayRef pathArray = CFArrayCreate( NULL, (const void **)&pathRef, 1, NULL );
	
	FSEventStreamContext context = { 0 };
	
	// The latency the user passed us is expressed in milliseconds, but the OS call requires the latency to be
	// expressed in seconds.
	CFTimeInterval latency = (inLatency / 1000.0);
	
	// Now we can make our change data object
	XMacChangeData *data = new XMacChangeData( inFolder.GetPath(), posixPath, inKindFilter, VTask::GetCurrent(), inHandler, this);
	context.info = data;
	data->fStreamRef = FSEventStreamCreate( NULL, &FSEventCallback, &context, pathArray, kFSEventStreamEventIdSinceNow, latency, kFSEventStreamCreateFlagNone );
	if (data->fStreamRef == NULL)
	{
		CFRelease( pathArray );
		CFRelease( pathRef );
		ReleaseRefCountable( &data);
		return MAKE_NATIVE_VERROR( errno );
	}
	
	// We also need to take an initial snapshot of the directory for us to compare again
	CreateDirectorySnapshot( posixPath, data->fSnapshot, true );
	
	// Now we can add the data object we just made to our list
	fOwner->PushChangeData( data);

	// Next, we can schedule this to run on the main event loop
	FSEventStreamScheduleWithRunLoop( data->fStreamRef, CFRunLoopGetMain(), kCFRunLoopDefaultMode );

	CFRelease( pathArray );
	CFRelease( pathRef );

	// Now that we've scheduled the stream to run on a helper thread, all that is left is to
	// start executing the stream
	VError err;
	if (FSEventStreamStart( data->fStreamRef ))
	{
		err = VE_OK;
	}
	else
	{
		err = MAKE_NATIVE_VERROR( errno );
	}
	ReleaseRefCountable( &data);
	
	return err;
}