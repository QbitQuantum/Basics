void ETHScriptWrapper::SetSpriteRect(const str_type::string& name, const unsigned int frame)
{
	SpritePtr pSprite = LoadAndGetSprite(name);
	if (pSprite)
	{
		pSprite->SetRect(frame);
	}
}