ImageProvider::ImageProvider(Context* pContext) : AbstractImageStreamProvider(pContext)
{
	CALL_XN( pContext->FindExistingNode(XN_NODE_TYPE_IMAGE, m_imageGen) );

	ImageMetaData md;
	m_imageGen.GetMetaData(md);
	CHECK_ERROR(md.PixelFormat() == XN_PIXEL_FORMAT_RGB24, "This camera's data format is not supported.");
	CHECK_ERROR(md.XRes() == 640 && md.YRes() == 480, "This camera's resolution is not supported.");
}