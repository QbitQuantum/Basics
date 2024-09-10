Text
RadioTraffic::TranslateVox(const char* phrase)
{
	Text vox = "vox.";
	vox += phrase;
	vox.toLower();
	vox = Game::GetText(vox);

	if (vox.contains("vox."))  // failed to translate
	return Text(phrase);    // return the original text

	return vox;
}