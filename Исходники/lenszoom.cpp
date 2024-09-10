cl_event render_bottom(int x, int y, int percentage, int deviceid)
{
	device_kernel_func_params[deviceid] = kernel_func_params;

	device_kernel_func_params[deviceid].zoom_center[0] = x * displayed_image_width / screen_width;
	device_kernel_func_params[deviceid].zoom_center[1] = y * displayed_image_height / screen_height;

	LZ_RECT src1, src2, dest;
	src1.x = 0; src1.y = 0; src1.w = screen_width; src1.h = screen_height;
	src2.x = x - zoomAreaRadius; src2.y = y + zoomAreaRadius - zoomAreaDiameter * percentage / 100;
	src2.w = zoomAreaDiameter; src2.h = zoomAreaDiameter * percentage / 100;
	intersectRect(dest, src1, src2);

	device_kernel_func_params[deviceid].lcoffset[0] = -zoomAreaRadius;
	device_kernel_func_params[deviceid].lcoffset[1] = zoomAreaRadius - zoomAreaDiameter * percentage / 100;

	if(src2.x < 0)
		device_kernel_func_params[deviceid].lcoffset[0] += src2.w - dest.w;
	if(src2.y < 0)
		device_kernel_func_params[deviceid].lcoffset[1] += src2.h - dest.h;

	work_dims[deviceid][0] = dest.w;
	work_dims[deviceid][1] = dest.h;

	void* memAreaPtr = &((unsigned short*)screen_pixels)[dest.y * screen_width + dest.x];
	unsigned int memAreaLen = dest.h * screen_width * bytes_per_pixel;
//	printf("Bottom mem area %8x - %8x\n", (unsigned int)memAreaPtr, (unsigned int)memAreaPtr + memAreaLen);

	cl_event event = 0;
	if (memAreaLen)
	{
		if(buffer[deviceid][1])
		{
			clReleaseMemObject(buffer[deviceid][1]);
			buffer[deviceid][1] = 0;
		}

		cl_int error = 0;
		buffer[deviceid][1] = clCreateBuffer(context[deviceid],
						CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
						memAreaLen,
						memAreaPtr,
						&error);
		if (buffer[deviceid][1] == (cl_mem)0)
		{
			printf("failed to create cl_mem buffer for the bottom rendering, error(%d)\n", error);
			return event;
		}


		error = clSetKernelArg( kernel[deviceid], 1, sizeof(cl_mem), &buffer[deviceid][1] );
		if (error != CL_SUCCESS)
		{
			printf("failed to create set kernel arg for the bottom rendering, error(%d)\n", error);
			return event;
		}


		error = clEnqueueNDRangeKernel(	queue[deviceid],
										kernel[deviceid],
										2,
										NULL,
										work_dims[deviceid],
										NULL,
										0,
										NULL,
										&event);
		if (error != CL_SUCCESS)
		{
			printf("failed to create enqueue kernel for the bottom rendering, error(%d)\n", error);
			return event;
		}
	}

	return event;
}