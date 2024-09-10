void LightPathtracer::SetScreenSize(const gl::Texture2D& _newBackbuffer)
{
	_newBackbuffer.BindImage(0, gl::Texture::ImageAccess::READ_WRITE);

	m_lockTexture.reset(new gl::Texture2D(_newBackbuffer.GetWidth(), _newBackbuffer.GetHeight(), gl::TextureFormat::R32UI));
	m_lockTexture->ClearToZero(0);
	m_lockTexture->BindImage(1, gl::Texture::ImageAccess::READ_WRITE);

	// Rule: Every block (size = m_localSizeLightPathtracer) should work with the same initial light sample!
	int numPixels = _newBackbuffer.GetWidth() * _newBackbuffer.GetHeight();
	m_numRaysPerLightSample = std::max(m_localSizeLightPathtracer, (numPixels / m_rendererSystem.GetNumInitialLightSamples() / m_localSizeLightPathtracer) * m_localSizeLightPathtracer);
	//m_numRaysPerLightSample = 1<<16;

	if(m_lightpathtraceUBO)
	{
		gl::MappedUBOView mapView(m_lightpathtraceUBOInfo, m_lightpathtraceUBO->Map(gl::Buffer::MapType::WRITE, gl::Buffer::MapWriteFlag::NONE));
		mapView["NumRaysPerLightSample"].Set(static_cast<std::int32_t>(m_numRaysPerLightSample));
		m_lightpathtraceUBO->Unmap();
	}
}