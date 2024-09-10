bool UFOFaceTokenImporter::importTextureName (FaceShader& faceShader, Tokeniser& tokeniser)
{
	const std::string texture = tokeniser.getToken();
	if (texture.empty()) {
		Tokeniser_unexpectedError(tokeniser, texture, "#texture-name");
		return false;
	}
	if (texture == "NULL" || texture.empty()) {
		faceShader.setShader("");
	} else {
		faceShader.setShader(GlobalTexturePrefix_get() + texture);
	}
	return true;
}