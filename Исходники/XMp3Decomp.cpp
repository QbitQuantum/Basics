void XMp3Decomp::Setup(XSound* snd, XBOOL reset)
{
	if (snd->dataLen == 0)
		return;
	if (!isInitMad())
		initMad();

	src = (XU8 *) snd->samples;
    bufLength = 0;      // number of bytes last filled with
    bufIndex = 0;       // index into the out buffer
    srcIndex = 0;
    this->snd = snd;

    // skip past the mp3 compression delay
    Decompress(0, snd->delay);
}