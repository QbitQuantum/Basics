void BasicShader::updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.texture != NULL)
		material.texture->bind();
	else
		WHITE.bind();

	setUniform("transform", projectedMatrix);
	setUniform("color", material.color);
}