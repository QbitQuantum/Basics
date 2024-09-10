	void FileSharingWidget::stopDownloading()
	{
		assert(isState(State::PlainFile_Downloading) ||
			   isState(State::ImageFile_Downloading));

		if (isState(State::PlainFile_Downloading))
		{
			setState(State::PlainFile_MetainfoLoaded);
			connectFileDownloadSignals(false);
		}

        if (isState(State::ImageFile_Downloading))
        {
            setState(State::ImageFile_MetainfoLoaded);
            connectImageDownloadedSignal(false);
        }

		Ui::GetDispatcher()->abortSharedFileDownloading(
			ContactUin_,
			FsInfo_->GetUri(),
			getCurrentProcessId()
		);

		resetCurrentProcessId();

		BytesTransferred_ = 0;
        Ui::GetDispatcher()->post_stats_to_core(core::stats::stats_event_names::filesharing_download_cancel);
	}