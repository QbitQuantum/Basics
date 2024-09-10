void IDXGISwapChainNew::preUpdateBB(UINT *width, UINT *height)
{
  dbg("dxgi_sc: preUpdateBB");

  int rrx = config.main.renderResolution.x;
  int rry = config.main.renderResolution.y;

  if(*width == rrx && *height == rry) {
    dbg("dxgi_sc: Multihead swapchain mode detected");
    HEAD *h = config.getPrimaryHead();
    *width = h->screenMode.x;
    *height = h->screenMode.y;

    // Set mouse hook on application focus window
    ihGlobal.setHWND(win);
    SoftTHActive++;
    h->hwnd = win;

    // Create new backbuffer
    dbg("dxgi_sc: Creating new backbuffer");
    // TODO: format
    #if defined(SOFTTHMAIN) || defined(D3D11)
    if(dev11)
    {
      // Create the full backbuffer render texture
      dbg("dxgi_sc: Creating FULL backbuffer for D3D11 Device");
      //CD3D10_TEXTURE2D_DESC d(DXGI_FORMAT_R8G8B8A8_UNORM, rrx, rry, 1, 1, D3D10_BIND_RENDER_TARGET, D3D10_USAGE_DEFAULT, NULL);
      CD3D11_TEXTURE2D_DESC d(DXGI_FORMAT_R8G8B8A8_UNORM, rrx, rry, 1, 1, D3D11_BIND_RENDER_TARGET, D3D11_USAGE_DEFAULT, NULL);
      newbbDesc11 = d;
      if(dev11->CreateTexture2D(&newbbDesc11, NULL, &newbb11) != S_OK)
        dbg("dxgi_sc: CreateTexture2D failed :("), exit(0);

      // Initialize outputs
      numDevs = config.getNumAdditionalHeads();
      dbg("dxgi_sc: Initializing %d outputs", numDevs);
      int logoStopTime = GetTickCount() + 4000;

      bool fpuPreserve = true; // TODO: does this exist in d3d10?

      outDevs11 = new OUTDEVICE11[numDevs];
      stagingOuts11 = new STAGINGOUT11[numDevs];
      for(int i=0;i<numDevs;i++)
      {
        OUTDEVICE11 *o  = &outDevs11[i];
        STAGINGOUT11 *so = &stagingOuts11[i];
        so->headID = i+1;
        so->devID = h->devID;
        so->stagingSurf = NULL;

        // Create the output device
        HEAD *h = config.getHead(i);
        dbg("dxgi_sc: Initializing Head %d (DevID: %d)",i+1,h->devID);
        o->output = new outDirect3D11(h->devID, h->screenMode.x, h->screenMode.y, h->transportRes.x, h->transportRes.y, win);
        o->cfg = h;
        bool local = h->transportMethod==OUTMETHOD_LOCAL;
        if (!local) has_nonlocal = true;
        dbg("dxgi_sc: Head %d is %s", i+1, local?"local":"non-local");

        // Create a main staging buffer sized for this head if non-local
        if (!local) {
          dbg("dxgi_sc: Creating a main non-local staging buffer for Head %d (DevID %d)", i + 1, h->devID);
          CD3D11_TEXTURE2D_DESC dss(DXGI_FORMAT_R8G8B8A8_UNORM, h->transportRes.x, h->transportRes.y, 1, 1, 0, D3D11_USAGE_STAGING, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 1, 0, 0);
          /*DWORD32 *fillbuf = new DWORD32[h->transportRes.x*h->transportRes.y];
          for (int ii = 0; ii < h->transportRes.y; ii++)
            for (int jj = 0; jj < h->transportRes.x; jj++)
            {
              if ((ii&32)==(jj&32))
                fillbuf[ii*h->transportRes.x + jj] = (DWORD32) 0x0000ff00;
              else
                fillbuf[ii*h->transportRes.x + jj] = (DWORD32) 0xffffffff;
            }
          D3D11_SUBRESOURCE_DATA fillsr;
          ZeroMemory(&fillsr, sizeof(fillsr));
          fillsr.pSysMem = (void *)fillbuf;
          fillsr.SysMemPitch = h->transportRes.x * 4;
          fillsr.SysMemSlicePitch = h->transportRes.x * h->transportRes.y * 4;
          if (dev11->CreateTexture2D(&dss, &fillsr, &so->stagingSurf) != S_OK) {*/
          if (dev11->CreateTexture2D(&dss, NULL, &so->stagingSurf) != S_OK) {
            dbg("dxgi_sc: CreateTexture2D staged for Head %d (DevID %d) failed :(",i+1,h->devID), exit(0);
          }
        }

        // Create shared surfaces
        HANDLE sha = o->output->GetShareHandle();
        if(sha) {
          o->localSurf = NULL;

          { // Open surfA share handle
            ID3D11Resource *tr;
			      if (o->cfg->transportMethod == OUTMETHOD_LOCAL) {
              // Local output
			        if (dev11->OpenSharedResource(sha, __uuidof(ID3D11Resource), (void**)(&tr)) != S_OK)
				        dbg("dxgi_sc: Local OpenSharedResource A failed!"), exit(0);
			      }
			      else
			      {
              // Non-local output
				      if (o->output->dev->OpenSharedResource(sha, __uuidof(ID3D11Resource), (void**)(&tr)) != S_OK)
					      dbg("dxgi_sc: Non-local OpenSharedResource A failed!"), exit(0);
			      }
            if(tr->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&o->localSurf)) != S_OK)
              dbg("dxgi_sc: Shared surface QueryInterface failed!"), exit(0);
            tr->Release();
          }
          dbg("dxgi_sc: Opened share handles");
        } else
          dbg("dxgi_sc: ERROR: Head %d: No share handle!", i+1), exit(0);
      }

      // Create the full backbuffer staged texture if we have non-local head
      /*if (has_nonlocal) {
        CD3D11_TEXTURE2D_DESC ds(DXGI_FORMAT_R8G8B8A8_UNORM, rrx, rry, 1, 1, NULL, D3D11_USAGE_STAGING, D3D11_CPU_ACCESS_READ, 1, 0, D3D11_RESOURCE_MISC_SHARED);
        newbbDesc11staged = ds;
        if(dev11->CreateTexture2D(&newbbDesc11staged, NULL, &newbb11staged) != S_OK)
          dbg("dxgi_sc: CreateTexture2D staged failed :("), exit(0);
      }*/
    }
    #endif
    #ifdef SOFTTHMAIN
    else
    #endif
    #if defined(SOFTTHMAIN) || defined(D3D10_1)
    if(dev10_1)
    {
      dbg("dxgi_sc: Creating backbuffer for D3D10.1 Device");
      CD3D10_TEXTURE2D_DESC d(DXGI_FORMAT_R8G8B8A8_UNORM, rrx, rry, 1, 1, D3D10_BIND_RENDER_TARGET, D3D10_USAGE_DEFAULT, NULL);
      newbbDesc10 = d;
      if(dev10_1->CreateTexture2D(&newbbDesc10, NULL, &newbb10) != S_OK)
        dbg("dxgi_sc: CreateTexture2D failed :("), exit(0);

      // Initialize outputs
      numDevs = config.getNumAdditionalHeads();
      dbg("dxgi_sc: Initializing %d outputs", numDevs);
      int logoStopTime = GetTickCount() + 4000;

      bool fpuPreserve = true; // TODO: does this exist in d3d10?

      outDevs10 = new OUTDEVICE10[numDevs];
      for(int i=0;i<numDevs;i++)
      {
        OUTDEVICE10 *o = &outDevs10[i];

        // Create the output device
        HEAD *h = config.getHead(i);
        bool local = h->transportMethod==OUTMETHOD_LOCAL;
        dbg("dxgi_sc: Initializing head %d (DevID: %d, %s)...", i+1, h->devID, local?"local":"non-local");
        o->output = new outDirect3D10(h->devID, h->screenMode.x, h->screenMode.y, h->transportRes.x, h->transportRes.y, win);
        o->cfg = h;

        // Create shared surfaces
        HANDLE sha = o->output->GetShareHandle();
        if(sha) {
          o->localSurf = NULL;

          { // Open surfA share handle
            ID3D10Resource *tr;
            if(dev10_1->OpenSharedResource(sha, __uuidof(ID3D10Resource), (void**)(&tr)) != S_OK)
              dbg("dxgi_sc: OpenSharedResource A failed!"), exit(0);
            if(tr->QueryInterface(__uuidof(ID3D10Texture2D), (void**)(&o->localSurf)) != S_OK)
              dbg("dxgi_sc: Shared surface QueryInterface failed!"), exit(0);
            tr->Release();
          }
          dbg("dxgi_sc: Opened share handles");
        } else
          dbg("dxgi_sc: ERROR: Head %d: No share handle!", i+1), exit(0);
      }
    }
    #endif
    #ifdef SOFTTHMAIN
    else
    #endif
    #if defined(SOFTTHMAIN) || defined(D3D10)
    if(dev10)
    {
      dbg("dxgi_sc: Creating backbuffer for D3D10 Device");
      CD3D10_TEXTURE2D_DESC d(DXGI_FORMAT_R8G8B8A8_UNORM, rrx, rry, 1, 1, D3D10_BIND_RENDER_TARGET, D3D10_USAGE_DEFAULT, NULL);
      newbbDesc10 = d;
      if(dev10->CreateTexture2D(&newbbDesc10, NULL, &newbb10) != S_OK)
        dbg("dxgi_sc: CreateTexture2D failed :("), exit(0);

      // Initialize outputs
      numDevs = config.getNumAdditionalHeads();
      dbg("dxgi_sc: Initializing %d outputs", numDevs);
      int logoStopTime = GetTickCount() + 4000;

      bool fpuPreserve = true; // TODO: does this exist in d3d10?

      outDevs10 = new OUTDEVICE10[numDevs];
      for(int i=0;i<numDevs;i++)
      {
        OUTDEVICE10 *o = &outDevs10[i];

        // Create the output device
        HEAD *h = config.getHead(i);
        bool local = h->transportMethod==OUTMETHOD_LOCAL;
        dbg("dxgi_sc: Initializing head %d (DevID: %d, %s)...", i+1, h->devID, local?"local":"non-local");
        o->output = new outDirect3D10(h->devID, h->screenMode.x, h->screenMode.y, h->transportRes.x, h->transportRes.y, win);
        o->cfg = h;

        // Create shared surfaces
        HANDLE sha = o->output->GetShareHandle();
        if(sha) {
          o->localSurf = NULL;

          { // Open surfA share handle
            ID3D10Resource *tr;
            if(dev10->OpenSharedResource(sha, __uuidof(ID3D10Resource), (void**)(&tr)) != S_OK)
              dbg("dxgi_sc: OpenSharedResource A failed!"), exit(0);
            if(tr->QueryInterface(__uuidof(ID3D10Texture2D), (void**)(&o->localSurf)) != S_OK)
              dbg("dxgi_sc: Shared surface QueryInterface failed!"), exit(0);
            tr->Release();
          }
          dbg("dxgi_sc: Opened share handles");
        } else
          dbg("dxgi_sc: ERROR: Head %d: No share handle!", i+1), exit(0);
      }
    }
    #endif

  } else {
    dbg("dxgi_sc: Singlehead swapchain mode");
    SoftTHActive--;

    if(dev11)
    {
      if(newbb11)
        SAFE_RELEASE_LAST(newbb11);
      newbb11 = NULL;
    }
    else if(dev10 || dev10_1)
    {
      if(newbb10)
        SAFE_RELEASE_LAST(newbb10);
      newbb10 = NULL;
    }

  }
}