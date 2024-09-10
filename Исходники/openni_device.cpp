openni_wrapper::OpenNIDevice::OpenNIDevice (xn::Context& context, const xn::NodeInfo& device_node, const xn::NodeInfo& image_node, const xn::NodeInfo& depth_node, const xn::NodeInfo& ir_node) 
  : context_ (context),
    device_node_info_ (device_node)
{
  // This magic value is taken from a calibration routine.
  rgb_focal_length_SXGA_  = 1050;

// workaround for MAC from Alex Ichim
#ifdef __APPLE__
  XnStatus rc;

  xn::EnumerationErrors errors;
  rc = context_.InitFromXmlFile ("/etc/openni/SamplesConfig.xml", &errors);
  if (rc == XN_STATUS_NO_NODE_PRESENT)
  {
    XnChar strError[1024];
    errors.ToString(strError, 1024);
    printf ("%s\n", strError);
  }
  else if (rc != XN_STATUS_OK)
  {
    printf ("Open failed: %s\n", xnGetStatusString(rc));
  }

  XnStatus status = context_.FindExistingNode(XN_NODE_TYPE_DEPTH, depth_generator_);
  if (status != XN_STATUS_OK)
    cerr << "node depth problems" << endl;
  status = context_.FindExistingNode(XN_NODE_TYPE_IMAGE, image_generator_);
  if (status != XN_STATUS_OK)
    cerr << "node image problems" << endl;
  status = context_.FindExistingNode(XN_NODE_TYPE_IR, ir_generator_);
    if (status != XN_STATUS_OK)
      cerr << "node ir problems" << endl;

#else

#if (XN_MINOR_VERSION >= 3)
// create the production nodes
  XnStatus status = context_.CreateProductionTree (const_cast<xn::NodeInfo&>(depth_node), depth_generator_);
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating depth generator failed. Reason: %s", xnGetStatusString (status));

  status = context_.CreateProductionTree (const_cast<xn::NodeInfo&>(image_node), image_generator_);
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating image generator failed. Reason: %s", xnGetStatusString (status));

  status = context_.CreateProductionTree (const_cast<xn::NodeInfo&>(ir_node), ir_generator_);
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating IR generator failed. Reason: %s", xnGetStatusString (status));
#else
  XnStatus status = context_.CreateProductionTree (const_cast<xn::NodeInfo&>(depth_node));
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating depth generator failed. Reason: %s", xnGetStatusString (status));

  status = context_.CreateProductionTree (const_cast<xn::NodeInfo&>(image_node));
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating image generator failed. Reason: %s", xnGetStatusString (status));

  status = context_.CreateProductionTree (const_cast<xn::NodeInfo&>(ir_node));
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating IR generator failed. Reason: %s", xnGetStatusString (status));

  // get production node instances
  status = depth_node.GetInstance (depth_generator_);
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating depth generator instance failed. Reason: %s", xnGetStatusString (status));

  status = image_node.GetInstance (image_generator_);
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating image generator instance failed. Reason: %s", xnGetStatusString (status));

  status = ir_node.GetInstance (ir_generator_);
  if (status != XN_STATUS_OK)
    THROW_OPENNI_EXCEPTION ("creating IR generator instance failed. Reason: %s", xnGetStatusString (status));
#endif // (XN_MINOR_VERSION >= 3)
  ir_generator_.RegisterToNewDataAvailable ((xn::StateChangedHandler)NewIRDataAvailable, this, ir_callback_handle_);
#endif // __APPLE__

  depth_generator_.RegisterToNewDataAvailable ((xn::StateChangedHandler)NewDepthDataAvailable, this, depth_callback_handle_);
  image_generator_.RegisterToNewDataAvailable ((xn::StateChangedHandler)NewImageDataAvailable, this, image_callback_handle_);

  Init ();
}