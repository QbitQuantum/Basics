void VideoEffect::Render(RenderBuffer &buffer, const std::string& filename,
	double starttime, bool aspectratio, std::string durationTreatment)
{
	VideoRenderCache *cache = (VideoRenderCache*)buffer.infoCache[id];
	if (cache == nullptr) {
		cache = new VideoRenderCache();
		buffer.infoCache[id] = cache;
	}

	std::string &_filename = cache->_filename;
	int &_starttime = cache->_starttime;
	bool &_aspectratio = cache->_aspectratio;
	std::string &_durationTreatment = cache->_durationTreatment;
	int &_loops = cache->_loops;
    int &_frameMS = cache->_frameMS;
	VideoReader* &_videoreader = cache->_videoreader;

	if (_starttime != starttime)
	{
		_starttime = starttime;
	}
    
	// we always reopen video on first frame or if it is not open or if the filename has changed
	if (buffer.needToInit)
	{
        buffer.needToInit = false;
		_filename = filename;
		_aspectratio = aspectratio;
		_durationTreatment = durationTreatment;
		_loops = 0;
        _frameMS = buffer.frameTimeInMs;
		if (_videoreader != NULL)
		{
			delete _videoreader;
			_videoreader = NULL;
		}

        if (buffer.BufferHt == 1)
        {
            log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
            logger_base.warn("VideoEffect::Cannot render video onto a 1 pixel high model. Have you set it to single line?");
        }
        else if (wxFileExists(_filename))
		{
			// have to open the file
			_videoreader = new VideoReader(_filename, buffer.BufferWi, buffer.BufferHt, _aspectratio);

            if (_videoreader == NULL)
            {
                log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
                logger_base.warn("VideoEffect: Failed to load video file %s.", (const char *)_filename.c_str());
            }
            else
            {
                // extract the video length
                int videolen = _videoreader->GetLengthMS();

                VideoPanel *fp = (VideoPanel*)panel;
                if (fp != nullptr)
                {
                    fp->addVideoTime(filename, videolen);
                }

                if (_starttime != 0)
                {
                    _videoreader->Seek(_starttime * 1000);
                }

                if (_durationTreatment == "Slow/Accelerate")
                {
                    int effectFrames = buffer.curEffEndPer - buffer.curEffStartPer + 1;
                    int videoFrames = (videolen - _starttime) / buffer.frameTimeInMs;
                    float speedFactor = (float)videoFrames / (float)effectFrames;
                    _frameMS = (int)((float)buffer.frameTimeInMs * speedFactor);
                }
            }
		}
        else
        {
            log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
            logger_base.warn("VideoEffect: Video file %s not found.", (const char *)_filename.c_str());
        }
	}

	if (_videoreader != NULL)
	{
		// get the image for the current frame
		AVFrame* image = _videoreader->GetNextFrame(_starttime * 1000 + (buffer.curPeriod - buffer.curEffStartPer) * _frameMS - _loops * _videoreader->GetLengthMS());
		
		// if we have reached the end and we are to loop
		if (_videoreader->AtEnd() && _durationTreatment == "Loop")
		{
			_loops++;
			// jump back to start and try to read frame again
			_videoreader->Seek(0);
			image = _videoreader->GetNextFrame(_starttime * 1000 + (buffer.curPeriod - buffer.curEffStartPer) * _frameMS - _loops * _videoreader->GetLengthMS());
		}

		int startx = (buffer.BufferWi - _videoreader->GetWidth()) / 2;
		int starty = (buffer.BufferHt - _videoreader->GetHeight()) / 2;

		// check it looks valid
		if (image != NULL)
		{
			// draw the image
			xlColor c;
			for (int y = 0; y < _videoreader->GetHeight(); y++)
			{
				for (int x = 0; x < _videoreader->GetWidth(); x++)
				{
					try
					{
						c.Set(*(image->data[0] + (_videoreader->GetHeight() - 1 - y) * _videoreader->GetWidth() * 3 + x * 3),
							  *(image->data[0] + (_videoreader->GetHeight() - 1 - y) * _videoreader->GetWidth() * 3 + x * 3 + 1),
							  *(image->data[0] + (_videoreader->GetHeight() - 1 - y) * _videoreader->GetWidth() * 3 + x * 3 + 2), 255);
					}
					catch (...)
					{
						// this shouldnt happen so make it stand out
						c = xlRED;
					}
					buffer.SetPixel(x + startx, y+starty, c);
				}
			}
		}
		else
		{
			// display a blue background to show we have gone past end of video
			for (int y = 0; y < buffer.BufferHt; y++)
			{
				for (int x = 0; x < buffer.BufferWi; x++)
				{
					buffer.SetPixel(x, y, xlBLUE);
				}
			}
		}
	}
    else
    {
        // display a red background to show we have a problem
        for (int y = 0; y < buffer.BufferHt; y++)
        {
            for (int x = 0; x < buffer.BufferWi; x++)
            {
                buffer.SetPixel(x, y, xlRED);
            }
        }
    }
}