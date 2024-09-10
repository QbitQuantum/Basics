bool OpenGLSdlGraphicsManager::notifyEvent(const Common::Event &event) {
	switch (event.type) {
	case Common::EVENT_KEYUP:
		return isHotkey(event);

	case Common::EVENT_KEYDOWN:
		if (event.kbd.hasFlags(Common::KBD_ALT)) {
			if (   event.kbd.keycode == Common::KEYCODE_RETURN
			    || event.kbd.keycode == (Common::KeyCode)SDLK_KP_ENTER) {
				// Alt-Return and Alt-Enter toggle full screen mode
				beginGFXTransaction();
					setFeatureState(OSystem::kFeatureFullscreenMode, !getFeatureState(OSystem::kFeatureFullscreenMode));
				endGFXTransaction();

#ifdef USE_OSD
				if (getFeatureState(OSystem::kFeatureFullscreenMode)) {
					displayMessageOnOSD("Fullscreen mode");
				} else {
					displayMessageOnOSD("Windowed mode");
				}
#endif
				return true;
			}

			if (event.kbd.keycode == Common::KEYCODE_s) {
				// Alt-s creates a screenshot
				Common::String filename;

				for (int n = 0;; n++) {
					SDL_RWops *file;

					filename = Common::String::format("scummvm%05d.bmp", n);
					file = SDL_RWFromFile(filename.c_str(), "r");
					if (!file)
						break;
					SDL_RWclose(file);
				}

				saveScreenshot(filename.c_str());
				debug("Saved screenshot '%s'", filename.c_str());

				return true;
			}
		} else if (event.kbd.hasFlags(Common::KBD_CTRL | Common::KBD_ALT)) {
			if (   event.kbd.keycode == Common::KEYCODE_PLUS || event.kbd.keycode == Common::KEYCODE_MINUS
			    || event.kbd.keycode == Common::KEYCODE_KP_PLUS || event.kbd.keycode == Common::KEYCODE_KP_MINUS) {
				// Ctrl+Alt+Plus/Minus Increase/decrease the size
				const int direction = (event.kbd.keycode == Common::KEYCODE_PLUS || event.kbd.keycode == Common::KEYCODE_KP_PLUS) ? +1 : -1;

				if (getFeatureState(OSystem::kFeatureFullscreenMode)) {
					// In case we are in fullscreen we will choose the previous
					// or next mode.

					// In case no modes are available we do nothing.
					if (_fullscreenVideoModes.empty()) {
						return true;
					}

					// Look for the current mode.
					VideoModeArray::const_iterator i = Common::find(_fullscreenVideoModes.begin(),
					                                                _fullscreenVideoModes.end(),
					                                                VideoMode(_desiredFullscreenWidth, _desiredFullscreenHeight));
					if (i == _fullscreenVideoModes.end()) {
						return true;
					}

					// Cycle through the modes in the specified direction.
					if (direction > 0) {
						++i;
						if (i == _fullscreenVideoModes.end()) {
							i = _fullscreenVideoModes.begin();
						}
					} else {
						if (i == _fullscreenVideoModes.begin()) {
							i = _fullscreenVideoModes.end();
						}
						--i;
					}

					_desiredFullscreenWidth  = i->width;
					_desiredFullscreenHeight = i->height;

					// Try to setup the mode.
					if (!setupMode(_lastRequestedWidth, _lastRequestedHeight)) {
						warning("OpenGLSdlGraphicsManager::notifyEvent: Fullscreen resize failed ('%s')", SDL_GetError());
						g_system->quit();
					}
				} else {
					// Calculate the next scaling setting. We approximate the
					// current scale setting in case the user resized the
					// window. Then we apply the direction change.
					_graphicsScale = MAX<int>(_hwScreen->w / _lastRequestedWidth, _hwScreen->h / _lastRequestedHeight);
					_graphicsScale = MAX<int>(_graphicsScale + direction, 1);

					// Since we overwrite a user resize here we reset its
					// flag here. This makes enabling AR smoother because it
					// will change the window size like in surface SDL.
					_gotResize = false;

					// Try to setup the mode.
					if (!setupMode(_lastRequestedWidth * _graphicsScale, _lastRequestedHeight * _graphicsScale)) {
						warning("OpenGLSdlGraphicsManager::notifyEvent: Window resize failed ('%s')", SDL_GetError());
						g_system->quit();
					}
				}

#ifdef USE_OSD
				const Common::String osdMsg = Common::String::format("Resolution: %dx%d", _hwScreen->w, _hwScreen->h);
				displayMessageOnOSD(osdMsg.c_str());
#endif

				return true;
			} else if (event.kbd.keycode == Common::KEYCODE_a) {
				// In case the user changed the window size manually we will
				// not change the window size again here.
				_ignoreLoadVideoMode = _gotResize;

				// Ctrl+Alt+a toggles the aspect ratio correction state.
				beginGFXTransaction();
					setFeatureState(OSystem::kFeatureAspectRatioCorrection, !getFeatureState(OSystem::kFeatureAspectRatioCorrection));
				endGFXTransaction();

				// Make sure we do not ignore the next resize. This
				// effectively checks whether loadVideoMode has been called.
				assert(!_ignoreLoadVideoMode);

#ifdef USE_OSD
				Common::String osdMsg = "Aspect ratio correction: ";
				osdMsg += getFeatureState(OSystem::kFeatureAspectRatioCorrection) ? "enabled" : "disabled";
				displayMessageOnOSD(osdMsg.c_str());
#endif

				return true;
			} else if (event.kbd.keycode == Common::KEYCODE_f) {
				// Ctrl+Alt+f toggles the graphics modes.

				// We are crazy we will allow the OpenGL base class to
				// introduce new graphics modes like shaders for special
				// filtering. If some other OpenGL subclass needs this,
				// we can think of refactoring this.
				int mode = getGraphicsMode();
				const OSystem::GraphicsMode *supportedModes = getSupportedGraphicsModes();
				const OSystem::GraphicsMode *modeDesc = nullptr;

				// Search the current mode.
				for (; supportedModes->name; ++supportedModes) {
					if (supportedModes->id == mode) {
						modeDesc = supportedModes;
						break;
					}
				}
				assert(modeDesc);

				// Try to use the next mode in the list.
				++modeDesc;
				if (!modeDesc->name) {
					modeDesc = getSupportedGraphicsModes();
				}

				// Never ever try to resize the window when we simply want to
				// switch the graphics mode. This assures that the window size
				// does not change.
				_ignoreLoadVideoMode = true;

				beginGFXTransaction();
					setGraphicsMode(modeDesc->id);
				endGFXTransaction();

				// Make sure we do not ignore the next resize. This
				// effectively checks whether loadVideoMode has been called.
				assert(!_ignoreLoadVideoMode);

#ifdef USE_OSD
				const Common::String osdMsg = Common::String::format("Graphics mode: %s", _(modeDesc->description));
				displayMessageOnOSD(osdMsg.c_str());
#endif

				return true;
			}
		}
		// Fall through

	default:
		return false;
	}
}