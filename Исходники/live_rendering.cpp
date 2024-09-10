int ImagineRender::applyPendingDataUpdates()
{
	m_logger.debug("applyPendingDataUpdates() called");
	
	m_liveRenderState.lock();
	
	// stop tracing as early as possible, so the render threads can shut down
	m_pRaytracer->terminate();
	
	std::vector<KatanaUpdateItem>::const_iterator itUpdate = m_liveRenderState.updatesBegin();
	for (; itUpdate != m_liveRenderState.updatesEnd(); ++itUpdate)
	{
		const KatanaUpdateItem& update = *itUpdate;

		if (update.type == KatanaUpdateItem::eTypeCamera)
		{
			// get hold of camera
			Camera* pCamera = m_pScene->getRenderCamera();

			if (update.haveXForm)
			{
				pCamera->transform().setCachedMatrix(update.xform.data(), true);
			}
			
			m_logger.debug("Updating Camera matrix");
			
			if (!update.extra.isEmpty())
			{
				pCamera->setFOV(update.extra.getFloat("fov", 70.0f));
				pCamera->setNearClippingPlane(update.extra.getFloat("nearClip", 0.1f));
			}
		}
		else if (update.type == KatanaUpdateItem::eTypeObjectMaterial && update.pMaterial)
		{
			Object* pLocationObject = m_pScene->getObjectByName(update.location);
			
			if (!pLocationObject)
			{
				m_logger.error("Can't find object: %s in scene in order to update its material.", update.location.c_str());
				continue;
			}
			
			update.pMaterial->preRenderMaterial();
			pLocationObject->setMaterial(update.pMaterial);
		}
		else if (update.type == KatanaUpdateItem::eTypeObject)
		{
			Object* pLocationObject = m_pScene->getObjectByName(update.location);
			
			if (!pLocationObject)
			{
				m_logger.error("Can't find object: %s in scene in order to update its properties.", update.location.c_str());
				continue;
			}
			
			m_logger.debug("Updating properties of object: %s", update.location.c_str());
			
			if (pLocationObject->getRenderVisibilityFlags() == 0)
			{
				// we can cheat here, and assume that if we've made it invisible before, we need to add it again.
				// This isn't really correct, as we can't tell the difference between deleted and hidden, but...
				pLocationObject->setRenderVisibilityFlags(RENDER_VISIBILITY_FLAGS_ALL);
			}
			else
			{
				if (update.extra.getBool("deleted", false))
				{
					// hacky and wrong, but...
					pLocationObject->setRenderVisibilityFlags(0);
				}
			}			
			
			if (update.haveXForm)
			{
				pLocationObject->transform().setCachedMatrix(update.xform.data(), true);
			}
		}
		else if (update.type == KatanaUpdateItem::eTypeLight)
		{
			Light* pLocationLight = m_pScene->getLightByName(update.location);
			
			if (!pLocationLight)
			{
				m_logger.error("Can't find light: %s in scene in order to update its parameters.", update.location.c_str());
				continue;
			}
			
			m_logger.debug("Updating properties of light: %s", update.location.c_str());
			
			if (update.haveXForm)
			{
				pLocationLight->transform().setCachedMatrix(update.xform.data(), true);
			}
			
			pLocationLight->setMuted(update.extra.getBool("muted", false));
			
			pLocationLight->setIntensity(update.extra.getFloat("intensity", 1.0f));
			pLocationLight->setExposure(update.extra.getFloat("exposure", 1.0f));
		}
	}

	m_liveRenderState.unlock();

	m_liveRenderState.flushUpdates();

	restartLiveRender();

	return 0;
}