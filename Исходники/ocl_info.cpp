long getOpenCLRawProcessorID(int device, const char **cpuname)
{
  static cl_char device_name[256+130];
  strcpy((char*)device_name, "Unknown");

  if (cpuname)
    *cpuname = (const char*)device_name;

  ocl_context_t *cont = ocl_get_context(device);
  if (cont)
  {
    clGetDeviceInfo(cont->deviceID, CL_DEVICE_NAME, sizeof(device_name)-130, device_name, NULL);

    //retrieve card info, if available
    u32 off = strlen((const char*)device_name);
    device_name[off++]=' '; device_name[off++]='\0';
#ifdef CL_DEVICE_BOARD_NAME_AMD
    if (clGetDeviceInfo(cont->deviceID, CL_DEVICE_BOARD_NAME_AMD, sizeof(device_name)-off, &device_name[off], NULL) == CL_SUCCESS)
    {
      device_name[off-1]='(';
      u32 off2 = strlen((const char*)device_name);
      device_name[off2] = ')';
      device_name[off2+1] = '\0';
    }
#endif
// ??? Never used
/*
    cl_uint vendor_id=0;
    clGetDeviceInfo(cont->deviceID, CL_DEVICE_VENDOR_ID, sizeof(vendor_id), &vendor_id, NULL);

    cl_uint cunits=0;
    clGetDeviceInfo(cont->deviceID, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cunits), &cunits, NULL);
*/
    return GetDeviceID(/* vendor_id, device_name, cunits, */ cont);
  }

  return -1;
}