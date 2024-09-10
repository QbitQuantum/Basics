void i_vx_add_device(vx_state *vx,DISPLAY_DEVICE dd)
{
	int res;

	strcpy(vx->monitor[vx->max_mon].DeviceName,dd.DeviceName);
	strcpy(vx->monitor[vx->max_mon].DeviceString,dd.DeviceString);
	vx->monitor[vx->max_mon].DeviceState = dd.StateFlags;

	//framebuffer / token / vxDevice / res / depth 갱신하기
	// Token
	vx->monitor[vx->max_mon].hDC = CreateDC(NULL,vx->monitor[vx->max_mon].DeviceName, NULL, NULL);
	res = ExtEscape(vx->monitor[vx->max_mon].hDC,ESC_GET_UNIQ,0,NULL,sizeof(vx->monitor[vx->max_mon].token),(PCHAR)&(vx->monitor[vx->max_mon].token));
	if(!res)
	{
		//만일 가상 장치가 아닌 경우 release 시킨다
		vx->monitor[vx->max_mon].is_vxDevice = FALSE;
		DeleteDC(vx->monitor[vx->max_mon].hDC);
	}
	else
	{
		//Framebuffer 및 해상도 정보를 갱신한다.
		vx->monitor[vx->max_mon].is_vxDevice = TRUE;
		
		res = ExtEscape(vx->monitor[vx->max_mon].hDC,ESC_GET_MAPPATH,0,NULL,sizeof(vx->monitor[vx->max_mon].wpath),(PCHAR)&(vx->monitor[vx->max_mon].wpath));
		if(!res)
		{
			//failed!
			return;
		}

		vx->monitor[vx->max_mon].DeviceVideoMemory = i_vx_GetSharedMemoryW(vx->monitor[vx->max_mon].wpath);
		vx->monitor[vx->max_mon].pos.x = *(((int*)vx->monitor[vx->max_mon].DeviceVideoMemory));
		vx->monitor[vx->max_mon].pos.y = *(((int*)vx->monitor[vx->max_mon].DeviceVideoMemory)+1);
		vx->monitor[vx->max_mon].depth = *(((int*)vx->monitor[vx->max_mon].DeviceVideoMemory)+2);
		vx->monitor[vx->max_mon].DeviceFramebuffer = (char*)(((int*)vx->monitor[vx->max_mon].DeviceVideoMemory)+3);
	}
	vx->max_mon++;
}