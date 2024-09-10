GS_PLAYER_INFO PlayCutscene(VideoPtr pVideo, const std::wstring& fileName,
							InputPtr pInput, const GS_KEY escapeKey)
{
	if (!pVideo)
	{
		ShowMessage(L"Invalid video handler - gs2d::PlayCutscene", GSMT_ERROR);
		return GSPI_FAILED;
	}

	GS_PLAYER_INFO info = GSPI_FINISHED;
	//pVideo->TurnLoopManagerOff();

	const bool rendering = pVideo->Rendering();
	if (rendering)
		pVideo->EndSpriteScene();

	PlayerPtr player = CreatePlayer(pVideo, fileName);
	if (!player)
	{
		ShowMessage(L"Failed while trying to load the video - gs2d::PlayCutscene", GSMT_ERROR);
		if (rendering)
			pVideo->BeginSpriteScene();
		return GSPI_FAILED;
	}

	pVideo->EnableMediaPlaying(true);
	player->SetFullscreen();
	player->Rewind();
	player->Play();

	while (!player->IsFinished())
	{
		player->UpdateVideo();
		const Video::APP_STATUS status = pVideo->HandleEvents();
		if (status == Video::APP_QUIT)
		{
			info = GSPI_CLOSE_WINDOW;
			break;
		}
		else
		{
			if (status == Video::APP_SKIP)
				continue;
		}

		if (pInput)
		{
			pInput->Update();
			if (pInput->GetKeyState(escapeKey) == GSKS_HIT)
			{
				info = GSPI_SKIPPED;
				break;
			}
		}
	}

	if (rendering)
		pVideo->BeginSpriteScene();

	pVideo->EnableMediaPlaying(false);
	return info;
}