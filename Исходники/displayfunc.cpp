void keyFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 'p': {
			session->SaveFilmImage();
			break;
		}
		case 27: { // Escape key
			delete session;

			SLG_LOG("Done.");
			exit(EXIT_SUCCESS);
			break;
		}
		case ' ': // Restart rendering
			session->Stop();
			session->Start();
			break;
		case 'a': {
			session->BeginEdit();
			session->renderConfig->scene->camera->TranslateLeft(MOVE_STEP);
			session->renderConfig->scene->camera->Update(
				session->film->GetWidth(), session->film->GetHeight());
			session->editActions.AddAction(CAMERA_EDIT);
			session->EndEdit();
			break;
		}
		case 'd': {
			session->BeginEdit();
			session->renderConfig->scene->camera->TranslateRight(MOVE_STEP);
			session->renderConfig->scene->camera->Update(
				session->film->GetWidth(), session->film->GetHeight());
			session->editActions.AddAction(CAMERA_EDIT);
			session->EndEdit();
			break;
		}
		case 'w': {
			session->BeginEdit();
			session->renderConfig->scene->camera->TranslateForward(MOVE_STEP);
			session->renderConfig->scene->camera->Update(
				session->film->GetWidth(), session->film->GetHeight());
			session->editActions.AddAction(CAMERA_EDIT);
			session->EndEdit();
			break;
		}
		case 's': {
			session->BeginEdit();
			session->renderConfig->scene->camera->TranslateBackward(MOVE_STEP);
			session->renderConfig->scene->camera->Update(
				session->film->GetWidth(), session->film->GetHeight());
			session->editActions.AddAction(CAMERA_EDIT);
			session->EndEdit();
			break;
		}
		case 'r':
			session->BeginEdit();
			session->renderConfig->scene->camera->Translate(Vector(0.f, 0.f, MOVE_STEP));
			session->renderConfig->scene->camera->Update(
				session->film->GetWidth(), session->film->GetHeight());
			session->editActions.AddAction(CAMERA_EDIT);
			session->EndEdit();
			break;
		case 'f':
			session->BeginEdit();
			session->renderConfig->scene->camera->Translate(Vector(0.f, 0.f, -MOVE_STEP));
			session->renderConfig->scene->camera->Update(
				session->film->GetWidth(), session->film->GetHeight());
			session->editActions.AddAction(CAMERA_EDIT);
			session->EndEdit();
			break;
		case 'h':
			OSDPrintHelp = (!OSDPrintHelp);
			break;
		case 'n': {
			const unsigned int screenRefreshInterval = session->renderConfig->GetScreenRefreshInterval();
			if (screenRefreshInterval > 1000)
				session->renderConfig->SetScreenRefreshInterval(max(1000u, screenRefreshInterval - 1000));
			else
				session->renderConfig->SetScreenRefreshInterval(max(50u, screenRefreshInterval - 50));
			break;
		}
		case 'm': {
			const unsigned int screenRefreshInterval = session->renderConfig->GetScreenRefreshInterval();
			if (screenRefreshInterval >= 1000)
				session->renderConfig->SetScreenRefreshInterval(screenRefreshInterval + 1000);
			else
				session->renderConfig->SetScreenRefreshInterval(screenRefreshInterval + 50);
			break;
		}
		case 't':
			// Toggle tonemap type
			if (session->film->GetToneMapParams()->GetType() == TONEMAP_LINEAR) {
				Reinhard02ToneMapParams params;
				session->film->SetToneMapParams(params);
			} else {
				LinearToneMapParams params;
				session->film->SetToneMapParams(params);
			}
			break;
		/*case '0':
			config->SetRenderingEngineType(PATHOCL);
			glutTimerFunc(config->GetScreenRefreshInterval(), timerFunc, 0);
			break;*/
		case 'o': {
#if defined(WIN32)
			std::wstring ws;
			ws.assign(SLG_LABEL.begin (), SLG_LABEL.end());
			HWND hWnd = FindWindowW(NULL, ws.c_str());
			if (GetWindowLongPtr(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
				SetWindowPos(hWnd, HWND_NOTOPMOST, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
			else
				SetWindowPos(hWnd, HWND_TOPMOST, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
#endif
			break;
		}

		default:
			break;
	}

	displayFunc();
}