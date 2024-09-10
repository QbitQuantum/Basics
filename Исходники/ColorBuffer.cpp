void ColorBuffer::GenerateMipMaps(CommandContext& BaseContext)
{
	if (m_NumMipMaps == 0)
		return;

	ComputeContext& Context = BaseContext.GetComputeContext();

	Context.SetRootSignature(Graphics::g_GenerateMipsRS);

	Context.TransitionResource(*this, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
	Context.SetDynamicDescriptor(1, 0, m_SRVHandle);

	for (uint32_t TopMip = 0; TopMip < m_NumMipMaps; )
	{
		uint32_t SrcWidth = m_Width >> TopMip;
		uint32_t SrcHeight = m_Height >> TopMip;
		uint32_t DstWidth = SrcWidth >> 1;
		uint32_t DstHeight = SrcHeight >> 1;

		// Determine if the first downsample is more than 2:1.  This happens whenever
		// the source width or height is odd.
		uint32_t NonPowerOfTwo = (SrcWidth & 1) | (SrcHeight & 1) << 1;
		if (m_Format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
			Context.SetPipelineState(Graphics::g_GenerateMipsGammaPSO[NonPowerOfTwo]);
		else
			Context.SetPipelineState(Graphics::g_GenerateMipsLinearPSO[NonPowerOfTwo]);

		// We can downsample up to four times, but if the ratio between levels is not
		// exactly 2:1, we have to shift our blend weights, which gets complicated or
		// expensive.  Maybe we can update the code later to compute sample weights for
		// each successive downsample.  We use _BitScanForward to count number of zeros
		// in the low bits.  Zeros indicate we can divide by two without truncating.
		uint32_t AdditionalMips;
		_BitScanForward((unsigned long*)&AdditionalMips, DstWidth | DstHeight);
		uint32_t NumMips = 1 + (AdditionalMips > 3 ? 3 : AdditionalMips);
		if (TopMip + NumMips > m_NumMipMaps)
			NumMips = m_NumMipMaps - TopMip;

		// These are clamped to 1 after computing additional mips because clamped
		// dimensions should not limit us from downsampling multiple times.  (E.g.
		// 16x1 -> 8x1 -> 4x1 -> 2x1 -> 1x1.)
		if (DstWidth == 0)
			DstWidth = 1;
		if (DstHeight == 0)
			DstHeight = 1;

		Context.SetConstants(0, TopMip, NumMips, 1.0f / DstWidth, 1.0f / DstHeight);
		Context.SetDynamicDescriptors(2, 0, NumMips, m_UAVHandle + TopMip + 1);
		Context.Dispatch2D(DstWidth, DstHeight);

		Context.InsertUAVBarrier(*this);

		TopMip += NumMips;
	}

	Context.TransitionResource(*this, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
}