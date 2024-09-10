//==============================================================================
Error BlurringRenderingPass::initBlurring(
	Renderer& r, U width, U height, U samples, F32 blurringDistance)
{
	Array<StringAuto, 2> pps = {{getAllocator(), getAllocator()}};

	pps[1].sprintf(
		"#define HPASS\n"
		"#define COL_RGB\n"
		"#define BLURRING_DIST float(%f)\n"
		"#define IMG_DIMENSION %u\n"
		"#define SAMPLES %u\n",
		blurringDistance, height, samples);

	pps[0].sprintf(
		"#define VPASS\n"
		"#define COL_RGB\n"
		"#define BLURRING_DIST float(%f)\n"
		"#define IMG_DIMENSION %u\n"
		"#define SAMPLES %u\n",
		blurringDistance, width, samples);

	for(U i = 0; i < 2; i++)
	{
		Direction& dir = m_dirs[i];

		r.createRenderTarget(width, height,
			PixelFormat(ComponentFormat::R8G8B8, TransformFormat::UNORM),
			1, SamplingFilter::LINEAR, 1, dir.m_rt);

		// Create FB
		FramebufferPtr::Initializer fbInit;
		fbInit.m_colorAttachmentsCount = 1;
		fbInit.m_colorAttachments[0].m_texture = dir.m_rt;
		fbInit.m_colorAttachments[0].m_loadOperation =
			AttachmentLoadOperation::DONT_CARE;
		dir.m_fb.create(&getGrManager(), fbInit);

		ANKI_CHECK(dir.m_frag.loadToCache(&getResourceManager(),
			"shaders/VariableSamplingBlurGeneric.frag.glsl",
			pps[i].toCString(), "r_"));

		ANKI_CHECK(r.createDrawQuadPipeline(
			dir.m_frag->getGrShader(), dir.m_ppline));
	}

	return ErrorCode::NONE;
}