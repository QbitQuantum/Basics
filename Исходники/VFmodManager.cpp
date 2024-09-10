// -------------------------------------------------------------------------- //
// Misc                                           
// -------------------------------------------------------------------------- //
void VFmodManager::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{
  if (pData->m_pSender==&Vision::Callbacks.OnEngineInit)
  {
    InitFmodSystem();
    return;
  }

  if(pData->m_pSender == &Vision::Callbacks.OnEngineDeInit)
  {
    // release all resources before the engine deinitializes
    m_soundInstances.Clear(); 
    m_events.Clear();
    m_collisionMeshes.Clear();
    m_reverbs.Clear();

    m_bAnyStopped = false;

    DeInitFmodSystem();
    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnUpdateSceneFinished)
  {
    RunTick(Vision::GetTimer()->GetTimeDifference());
#ifdef _DEBUG_OUTPUT
    SoundInstances().DebugOutput();
    Events().DebugOutput();
#endif
    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnWorldInit)
  {
    if (!IsInitialized())
      return;

    VASSERT(m_pSystem!=NULL);

    // notify the sound engine about the world extents   
    float fRadius = 32000.0f;
    hkvAlignedBBox bbox;
    Vision::GetSceneManager()->GetSceneExtents(bbox);
    if (bbox.isValid())
      fRadius = bbox.getBoundingSphere().m_fRadius; 
    FMOD_ERRORCHECK(m_pSystem->setGeometrySettings(fRadius));

    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnWorldDeInit)
  {
    // stop all instances and dispose them if possible (i.e VFMOD_FLAG_NODISPOSE flag not set)
    SoundInstances().StopAll(true); 
    Events().StopAll(true);

    // remove all collision meshes
    CollisionMeshes().Clear(); 

    // remove all reverbs
    Reverbs().Clear();

    m_bAnyStopped = false;
  
    return;
  }

  if (pData->m_pSender==&IVScriptManager::OnScriptProxyCreation)
  {
    VScriptCreateStackProxyObject * pScriptData = (VScriptCreateStackProxyObject *)pData;

    //process data only as far as not handled until now
    if (!pScriptData->m_bProcessed)
    {
      int iRetParams = 0;
      if (pScriptData->m_pInstance->IsOfType(V_RUNTIME_CLASS(VFmodSoundObject)))
        iRetParams = LUA_CallStaticFunction(pScriptData->m_pLuaState,"FireLight","VFmodSoundObject","Cast","O>O",pScriptData->m_pInstance);
      else if (pScriptData->m_pInstance->IsOfType(V_RUNTIME_CLASS(VFmodEvent)))
        iRetParams = LUA_CallStaticFunction(pScriptData->m_pLuaState,"FireLight","VFmodEvent","Cast","O>O",pScriptData->m_pInstance);

      if (iRetParams>0)
      {
        if(lua_isnil(pScriptData->m_pLuaState, -1))   
          lua_pop(pScriptData->m_pLuaState, iRetParams);
        else                                         
          pScriptData->m_bProcessed = true;
      }
    }
    return;
  }

  if(pData->m_pSender==&IVScriptManager::OnRegisterScriptFunctions)
  {
    IVScriptManager* pSM = Vision::GetScriptManager();
    if (pSM)
    {
      lua_State* pLuaState = ((VScriptResourceManager*)pSM)->GetMasterState();
      if(pLuaState)
      {
        lua_getglobal(pLuaState, "Fmod");
        int iType = lua_type(pLuaState, -1);
        lua_pop(pLuaState, 1);

        if(iType!=LUA_TUSERDATA)
        {
          luaopen_FireLight(pLuaState);
          int iRetParams = LUA_CallStaticFunction(pLuaState,"FireLight","VFmodManager","Cast","v>v", &VFmodManager::GlobalManager());
          if (iRetParams==1)
          {
            if(lua_isnil(pLuaState, -1))
            {
              lua_pop(pLuaState, iRetParams);
            }
            else
            {
              lua_setglobal(pLuaState, "Fmod");
              return;
            }
          }
        }
        else
        {
          return; //already loaded
        }
      }
      
      Vision::Error.Warning("Unable to create Lua Fmod Module, lua_State is NULL or cast failed!");
    }
    return;
  }

#if defined(_VISION_MOBILE)
  // Pause Sound when in background
  if (pData->m_pSender == &Vision::Callbacks.OnLeaveForeground)
  {
    if (IsInitialized())
    {
      // From the FMOD Ex documentation:
      // "Channels will not have their per channel pause state overwritten, 
      // so that when a channelgroup is unpaused, the paused state of the channels will 
      // correct as they were set on a per channel basis."
      m_pMasterGroup->getPaused(&m_bMasterGroupPausedInForeground);
      m_pMusicGroup->getPaused(&m_bMusicGroupPausedInForeground);

      m_pMasterGroup->setPaused(true);
      m_pMusicGroup->setPaused(true);

      // Get master event category and pause it as well
      FMOD::EventCategory *pEventCategory = NULL;   
      FMOD_ERRORCHECK(m_pEventSystem->getCategoryByIndex(-1, &pEventCategory));

      pEventCategory->getPaused(&m_bMasterEventCategoryPausedInForeground);
      pEventCategory->setPaused(true);
    }

    return;
  }

  if (pData->m_pSender == &Vision::Callbacks.OnEnterForeground)
  {
    if (IsInitialized())
    {
      m_pMasterGroup->setPaused(m_bMasterGroupPausedInForeground);
      m_pMusicGroup->setPaused(m_bMusicGroupPausedInForeground);

      FMOD::EventCategory *pEventCategory = NULL;   
      FMOD_ERRORCHECK(m_pEventSystem->getCategoryByIndex(-1, &pEventCategory));

      pEventCategory->setPaused(m_bMasterEventCategoryPausedInForeground);
    }

    return;
  }
#endif
}