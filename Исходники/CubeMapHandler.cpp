void CubeMapHandler::CreateSpecularFacePart(
	unsigned int texType,
	unsigned int size,
	const float3& cdir,
	const float3& xdif,
	const float3& ydif,
	unsigned int y,
	unsigned char* buf)
{
	// TODO move to a shader
	for (int x = 0; x < size; ++x) {
		const float3 dir = (cdir + (xdif * (x + 0.5f)) / size + (ydif * (y + 0.5f)) / size).Normalize();
		const float dot  = std::max(0.0f, dir.dot(sky->GetLight()->GetLightDir()));
		const float spec = std::min(1.0f, pow(dot, mapInfo->light.specularExponent) + pow(dot, 3.0f) * 0.25f);

		buf[x * 4 + 0] = (mapInfo->light.unitSpecularColor.x * spec * 255);
		buf[x * 4 + 1] = (mapInfo->light.unitSpecularColor.y * spec * 255);
		buf[x * 4 + 2] = (mapInfo->light.unitSpecularColor.z * spec * 255);
		buf[x * 4 + 3] = 255;
	}
}