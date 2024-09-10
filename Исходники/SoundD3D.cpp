HRESULT
SoundD3D::Play()
{
	if (IsPlaying())  return S_OK;
	if (!buffer)      return E_FAIL;

	HRESULT hr = E_FAIL;

	if (IsDone())
	hr = Rewind();

	if (IsReady()) {
		if (moved)
		Localize();

		if (flags & LOOP || flags & STREAMED)
		hr = buffer->Play(0, 0, DSBPLAY_LOOPING);
		else
		hr = buffer->Play(0, 0, 0);

		if (SUCCEEDED(hr))
		status = PLAYING;
	}

	return hr;
}