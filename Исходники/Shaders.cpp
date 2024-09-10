CVector3 cRenderWorker::NormalMapShader(const sShaderInputData &input)
{
	cObjectData objectData = data->objectData[input.objectId];
	CVector3 texX, texY;
	double texturePixelSize = 1.0;
	CVector2<double> texPoint =
		TextureMapping(input.point, input.normal, objectData, input.material, &texX, &texY)
		+ CVector2<double>(0.5, 0.5);

	// mipmapping - calculation of texture pixel size
	double delta = CalcDelta(input.point);
	double deltaTexX =
		((TextureMapping(input.point + texX * delta, input.normal, objectData, input.material)
			 + CVector2<double>(0.5, 0.5))
			- texPoint)
			.Length();
	double deltaTexY =
		((TextureMapping(input.point + texY * delta, input.normal, objectData, input.material)
			 + CVector2<double>(0.5, 0.5))
			- texPoint)
			.Length();
	deltaTexX = deltaTexX / fabs(input.viewVector.Dot(input.normal));
	deltaTexY = deltaTexY / fabs(input.viewVector.Dot(input.normal));
	texturePixelSize = 1.0 / max(deltaTexX, deltaTexY);

	CVector3 n = input.normal;
	// tangent vectors:
	CVector3 t = n.Cross(texX);
	t.Normalize();
	CVector3 b = n.Cross(texY);
	b.Normalize();
	CMatrix33 tbn(b, t, n);

	CVector3 tex;

	if (input.material->normalMapTextureFromBumpmap)
	{
		tex = input.material->normalMapTexture.NormalMapFromBumpMap(
			texPoint, input.material->normalMapTextureHeight, texturePixelSize);
	}
	else
	{
		tex = input.material->normalMapTexture.NormalMap(
			texPoint, input.material->normalMapTextureHeight, texturePixelSize);
	}

	CVector3 result = tbn * tex;
	result.Normalize();
	return result;
}