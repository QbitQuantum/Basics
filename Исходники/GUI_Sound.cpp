void GuiSound::Rewind()
{
	SoundDecoder * decoder = SoundHandler::Instance()->Decoder(voice);
	if(!decoder)
		return;

	decoder->Rewind();
}