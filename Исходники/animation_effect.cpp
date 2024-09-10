bool AnimationEffect::process(uint32 deltaTimeInMillis) {
	ScriptManager *scriptManager = _engine->getScriptManager();
	RenderManager *renderManager = _engine->getRenderManager();
	RenderTable::RenderState renderState = renderManager->getRenderTable()->getRenderState();
	bool isPanorama = (renderState == RenderTable::PANORAMA);
	int16 velocity = _engine->getMouseVelocity() + _engine->getKeyboardVelocity();

	// Do not update animation nodes in panoramic mode while turning, if the user
	// has set this option
	if (scriptManager->getStateValue(StateKey_NoTurnAnim) == 1 && isPanorama && velocity)
		return false;

	PlayNodes::iterator it = _playList.begin();
	if (it != _playList.end()) {
		playnode *nod = &(*it);

		if (nod->_curFrame == -1) {
			// The node is just beginning playback
			nod->_curFrame = nod->start;

			_animation->start();
			_animation->seekToFrame(nod->start);
			_animation->setEndFrame(nod->stop);

			nod->_delay = deltaTimeInMillis; // Force the frame to draw
			if (nod->slot)
				scriptManager->setStateValue(nod->slot, 1);
		} else if (_animation->endOfVideo()) {
			// The node has reached the end; check if we need to loop
			nod->loop--;

			if (nod->loop == 0) {
				if (nod->slot >= 0)
					scriptManager->setStateValue(nod->slot, 2);
				if (nod->_scaled) {
					nod->_scaled->free();
					delete nod->_scaled;
				}
				_playList.erase(it);
				return _disposeAfterUse;
			}

			nod->_curFrame = nod->start;
			_animation->seekToFrame(nod->start);
		}

		// Check if we need to draw a frame
		bool needsUpdate = false;
		if (_frmDelayOverride == 0) {
			// If not overridden, use the VideoDecoder's check
			needsUpdate = _animation->needsUpdate();
		} else {
			// Otherwise, implement our own timing
			nod->_delay -= deltaTimeInMillis;

			if (nod->_delay <= 0) {
				nod->_delay += _frmDelayOverride;
				needsUpdate = true;
			}
		}

		if (needsUpdate) {
			const Graphics::Surface *frame = _animation->decodeNextFrame();

			if (frame) {
				uint32 dstw;
				uint32 dsth;
				if (isPanorama) {
					dstw = nod->pos.height();
					dsth = nod->pos.width();
				} else {
					dstw = nod->pos.width();
					dsth = nod->pos.height();
				}

				// We only scale down the animation to fit its frame, not up, otherwise we
				// end up with distorted animations - e.g. the armor visor in location cz1e
				// in Nemesis (one of the armors inside Irondune), or the planet in location
				// aa10 in Nemesis (Juperon, outside the asylum). We do allow scaling up only
				// when a simple 2x filter is requested (e.g. the alchemists and cup sequence
				// in Nemesis)
				if (frame->w > dstw || frame->h > dsth || (frame->w == dstw / 2 && frame->h == dsth / 2)) {
					if (nod->_scaled)
						if (nod->_scaled->w != dstw || nod->_scaled->h != dsth) {
							nod->_scaled->free();
							delete nod->_scaled;
							nod->_scaled = NULL;
						}

					if (!nod->_scaled) {
						nod->_scaled = new Graphics::Surface;
						nod->_scaled->create(dstw, dsth, frame->format);
					}

					renderManager->scaleBuffer(frame->getPixels(), nod->_scaled->getPixels(), frame->w, frame->h, frame->format.bytesPerPixel, dstw, dsth);
					frame = nod->_scaled;
				}

				if (isPanorama) {
					Graphics::Surface *transposed = RenderManager::tranposeSurface(frame);
					renderManager->blitSurfaceToBkg(*transposed, nod->pos.left, nod->pos.top, _mask);
					transposed->free();
					delete transposed;
				} else {
					renderManager->blitSurfaceToBkg(*frame, nod->pos.left, nod->pos.top, _mask);
				}
			}
		}
	}

	return false;
}