// Set up OpenNI to obtain 8-bit mono images from the Kinect's RGB camera
int kinectInit(void)
{
  XnStatus nRetVal = XN_STATUS_OK;
  ScriptNode scriptNode;
  EnumerationErrors errors;

  printf("Reading config from: '%s'\n", SAMPLE_XML_PATH_LOCAL);
  nRetVal = context.InitFromXmlFile(SAMPLE_XML_PATH_LOCAL, scriptNode, &errors);

  nRetVal = context.FindExistingNode(XN_NODE_TYPE_IMAGE, g_image); 
  //g_image.SetPixelFormat(XN_PIXEL_FORMAT_GRAYSCALE_8_BIT); 
  g_image.SetPixelFormat(XN_PIXEL_FORMAT_RGB24); 
  g_image.GetMetaData(g_imageMD);

  nRetVal = context.FindExistingNode(XN_NODE_TYPE_DEPTH, depth);
  depth.GetMetaData(depthMD);

  //  nRetVal = depth.GetAlternativeViewPointCap().SetViewPoint(g_image);
  //nRetVal = depth.GetFrameSyncCap().FrameSyncWith(g_image);

 return nRetVal;
}