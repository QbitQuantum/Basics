void D3D9Capture(IDirect3DDevice9* device) {
	h3d::EventProcess();

	if (!has_textured && capture_run) {

		//fix for some [backbuffers aren't actually being properly used]
		//get size/format at actual current rt at time of present
		IDirect3DSurface9* back_buffer = NULL;
		if (SUCCEEDED(device->GetRenderTarget(0, &back_buffer))) {
			D3DSURFACE_DESC sd;
			ZeroMemory(&sd, sizeof(sd));

			if (SUCCEEDED(back_buffer->GetDesc(&sd))) {
				//todo something
			}

			back_buffer->Release();
		}


		if (gpu_support)
			CreateD3D9GPUCapture(device);
		else
			CreateCPUCapture(device);
	}

	//KeeapAliveProcess(Flush()) Crash In Xp(WMware Workstation)
	//I Think Cry
	if (capture_run) {
			LONGLONG capture_tp = h3d::GetOSMillSeconds(); 
			if (capture_tp - prev_point > KEEP_TIME_DURATION) {
					HANDLE keepAlive = OpenEventW(EVENT_ALL_ACCESS, FALSE, sKeepAlive.c_str()); 
					if (keepAlive)
						CloseHandle(keepAlive); 
					else {
							Flush();
							logstream << "Don't Exist Event[" << sKeepAlive << "] (OBS Process Unexpected Exit,Wait Next Begin Event)" << std::endl;
							capture_run = false; 
					}
						prev_point = capture_tp; 
			}
	}
	//todo some keep alive state check

	if (has_textured && capture_run) {
		if (gpu_support)
			D3D9CaptureGPU(device);
		else {
			//copy texture data only when GetRenderTargetData completes
			for (UINT i = 0; i != NUM_BACKBUFF; ++i) {
				if (issued_querys[i]) {
					if (d3d9_querys[i]->GetData(0, 0, 0) == S_OK) {
						issued_querys[i] = false;

						IDirect3DSurface9* texture = d3d9_textures[i];
						D3DLOCKED_RECT locked_rect;

						if (SUCCEEDED(texture->LockRect(&locked_rect, NULL, D3DLOCK_READONLY))) {
							copy_data = locked_rect.pBits;
							copy_index = i;
							locked_textures[i] = true;

							SetEvent(copy_event);
						}
					}
				}
			}

			//todo fps maintain
			DWORD next_capture = (curr_capture == NUM_BACKBUFF - 1) ? 0 : (curr_capture + 1);
			IDirect3DSurface9* src_texture = d3d9_copytextures[curr_capture];
			IDirect3DSurface9* back_buffer = NULL;

			if (SUCCEEDED(device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer))) {
				device->StretchRect(back_buffer, NULL, src_texture, NULL, D3DTEXF_NONE);
				back_buffer->Release();

				if (copy_wait < NUM_BACKBUFF - 1)
					++copy_wait;//直到填满三个
				else {
					IDirect3DSurface9* prev_texture = d3d9_copytextures[next_capture];
					IDirect3DSurface9* target_texture = d3d9_textures[next_capture];

					if (locked_textures[next_capture]) {
						EnterCriticalSection(&data_mutexs[next_capture]);

						target_texture->UnlockRect();
						locked_textures[next_capture] = false;

						LeaveCriticalSection(&data_mutexs[next_capture]);
					}

					if (FAILED(device->GetRenderTargetData(prev_texture, target_texture)))
						logstream << "Failed captureing frame via cpu" << std::endl;

					d3d9_querys[next_capture]->Issue(D3DISSUE_END);
					issued_querys[next_capture] = true;

					//logstream << "Successfully captureing frame via cpu" << std::endl;
				}
			}

			curr_capture = next_capture;
		}
	}
	else if (has_textured)
		Flush();
}