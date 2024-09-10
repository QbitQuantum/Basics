void NetStream::execute()
{
	//checkPolicyFile only applies to per-pixel access, loading and playing is always allowed.
	//So there is no need to disallow playing if policy files disallow it.
	//We do need to check if per-pixel access is allowed.
	SecurityManager::EVALUATIONRESULT evaluationResult = sys->securityManager->evaluatePoliciesURL(url, true);
	if(evaluationResult == SecurityManager::NA_CROSSDOMAIN_POLICY)
		rawAccessAllowed = true;

	if(downloader->hasFailed())
	{
		this->incRef();
		sys->currentVm->addEvent(_MR(this),_MR(Class<Event>::getInstanceS("ioError")));
		sys->downloadManager->destroy(downloader);
		return;
	}

	//The downloader hasn't failed yet at this point

	istream s(downloader);
	s.exceptions ( istream::eofbit | istream::failbit | istream::badbit );

	ThreadProfile* profile=sys->allocateProfiler(RGB(0,0,200));
	profile->setTag("NetStream");
	bool waitForFlush=true;
	StreamDecoder* streamDecoder=NULL;
	//We need to catch possible EOF and other error condition in the non reliable stream
	try
	{
		Chronometer chronometer;
		streamDecoder=new FFMpegStreamDecoder(s);
		if(!streamDecoder->isValid())
			threadAbort();

		bool done=false;
		while(!done)
		{
			//Check if threadAbort has been called, if so, stop this loop
			if(closed)
				done = true;
			bool decodingSuccess=streamDecoder->decodeNextFrame();
			if(decodingSuccess==false)
				done = true;

			if(videoDecoder==NULL && streamDecoder->videoDecoder)
			{
				videoDecoder=streamDecoder->videoDecoder;
				this->incRef();
				getVm()->addEvent(_MR(this),
						_MR(Class<NetStatusEvent>::getInstanceS("status", "NetStream.Play.Start")));
				this->incRef();
				getVm()->addEvent(_MR(this),
						_MR(Class<NetStatusEvent>::getInstanceS("status", "NetStream.Buffer.Full")));
			}

			if(audioDecoder==NULL && streamDecoder->audioDecoder)
				audioDecoder=streamDecoder->audioDecoder;

			if(audioStream==NULL && audioDecoder && audioDecoder->isValid() && sys->audioManager->pluginLoaded())
				audioStream=sys->audioManager->createStreamPlugin(audioDecoder);

			if(audioStream && audioStream->paused() && !paused)
			{
				//The audio stream is paused but should not!
				//As we have new data fill the stream
				audioStream->fill();
			}

			if(!tickStarted && isReady())
			{
				multiname onMetaDataName;
				onMetaDataName.name_type=multiname::NAME_STRING;
				onMetaDataName.name_s="onMetaData";
				onMetaDataName.ns.push_back(nsNameAndKind("",NAMESPACE));
				ASObject* callback = client->getVariableByMultiname(onMetaDataName);
				if(callback && callback->getObjectType() == T_FUNCTION)
				{
					ASObject* callbackArgs[1];
					ASObject* metadata = Class<ASObject>::getInstanceS();
					double d;
					uint32_t i;
					if(streamDecoder->getMetadataDouble("width",d))
						metadata->setVariableByQName("width", "",abstract_d(d),DYNAMIC_TRAIT);
					else
						metadata->setVariableByQName("width", "", abstract_d(getVideoWidth()),DYNAMIC_TRAIT);
					if(streamDecoder->getMetadataDouble("height",d))
						metadata->setVariableByQName("height", "",abstract_d(d),DYNAMIC_TRAIT);
					else
						metadata->setVariableByQName("height", "", abstract_d(getVideoHeight()),DYNAMIC_TRAIT);
					if(streamDecoder->getMetadataDouble("framerate",d))
						metadata->setVariableByQName("framerate", "",abstract_d(d),DYNAMIC_TRAIT);
					if(streamDecoder->getMetadataDouble("duration",d))
						metadata->setVariableByQName("duration", "",abstract_d(d),DYNAMIC_TRAIT);
					if(streamDecoder->getMetadataInteger("canseekontime",i))
						metadata->setVariableByQName("canSeekToEnd", "",abstract_b(i == 1),DYNAMIC_TRAIT);
					if(streamDecoder->getMetadataDouble("audiodatarate",d))
						metadata->setVariableByQName("audiodatarate", "",abstract_d(d),DYNAMIC_TRAIT);
					if(streamDecoder->getMetadataDouble("videodatarate",d))
						metadata->setVariableByQName("videodatarate", "",abstract_d(d),DYNAMIC_TRAIT);

					//TODO: missing: audiocodecid (Number), cuePoints (Object[]),
					//videocodecid (Number), custommetadata's
					client->incRef();
					metadata->incRef();
					callbackArgs[0] = metadata;
					callback->incRef();
					_R<FunctionEvent> event(new FunctionEvent(_MR(static_cast<IFunction*>(callback)),
							_MR(client), callbackArgs, 1));
					getVm()->addEvent(NullRef,event);
				}

				tickStarted=true;
				if(frameRate==0)
				{
					assert(videoDecoder->frameRate);
					frameRate=videoDecoder->frameRate;
				}
				sys->addTick(1000/frameRate,this);
				//Also ask for a render rate equal to the video one (capped at 24)
				float localRenderRate=dmin(frameRate,24);
				sys->setRenderRate(localRenderRate);
			}
			profile->accountTime(chronometer.checkpoint());
			if(aborting)
				throw JobTerminationException();
		}

	}
	catch(LightsparkException& e)
	{
		LOG(LOG_ERROR, "Exception in NetStream " << e.cause);
		threadAbort();
		waitForFlush=false;
	}
	catch(JobTerminationException& e)
	{
		waitForFlush=false;
	}
	catch(exception& e)
	{
		LOG(LOG_ERROR, _("Exception in reading: ")<<e.what());
	}
	if(waitForFlush)
	{
		//Put the decoders in the flushing state and wait for the complete consumption of contents
		if(audioDecoder)
			audioDecoder->setFlushing();
		if(videoDecoder)
			videoDecoder->setFlushing();
		
		if(audioDecoder)
			audioDecoder->waitFlushed();
		if(videoDecoder)
			videoDecoder->waitFlushed();

		this->incRef();
		getVm()->addEvent(_MR(this), _MR(Class<NetStatusEvent>::getInstanceS("status", "NetStream.Play.Stop")));
		this->incRef();
		getVm()->addEvent(_MR(this), _MR(Class<NetStatusEvent>::getInstanceS("status", "NetStream.Buffer.Flush")));
	}
	//Before deleting stops ticking, removeJobs also spin waits for termination
	sys->removeJob(this);
	tickStarted=false;
	sem_wait(&mutex);
	//Change the state to invalid to avoid locking
	videoDecoder=NULL;
	audioDecoder=NULL;
	//Clean up everything for a possible re-run
	sys->downloadManager->destroy(downloader);
	//This transition is critical, so the mutex is needed
	downloader=NULL;
	if(audioStream)
		sys->audioManager->freeStreamPlugin(audioStream);
	audioStream=NULL;
	sem_post(&mutex);
	delete streamDecoder;
}