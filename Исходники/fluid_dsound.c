DWORD WINAPI fluid_dsound_audio_run(LPVOID lpParameter)
{
  fluid_dsound_audio_driver_t* dev = (fluid_dsound_audio_driver_t*) lpParameter;
  short *buf1, *buf2;
  DWORD bytes1, bytes2;
  DWORD cur_position, frames, play_position, write_position, bytes;
  HRESULT res;

  cur_position = 0;

  /* boost the priority of the audio thread */
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

  IDirectSoundBuffer_Play(dev->sec_buffer, 0, 0, DSBPLAY_LOOPING);

  while (dev->cont) {

    IDirectSoundBuffer_GetCurrentPosition(dev->sec_buffer, &play_position, &write_position);

    if (cur_position <= play_position) {
      bytes = play_position - cur_position;
    } else if ((play_position < cur_position) && (write_position <= cur_position)) {
      bytes = dev->queue_byte_size + play_position - cur_position;
    } else {
      bytes = 0;
    }

    if (bytes >= dev->buffer_byte_size) {

      /* Lock */
      res = IDirectSoundBuffer_Lock(dev->sec_buffer, cur_position, bytes, (void*) &buf1, &bytes1, (void*) &buf2, &bytes2, 0);

      if ((res != DS_OK) || (buf1 == NULL)) {
	FLUID_LOG(FLUID_PANIC, "Failed to lock the audio buffer. System lockup might follow. Exiting.");
	ExitProcess(0);
      }

      /* fill the first part of the buffer */
      if (bytes1 > 0) {
	frames = bytes1 / dev->frame_size;
	dev->write(dev->synth, frames, buf1, 0, 2, buf1, 1, 2);
	cur_position += frames * dev->frame_size;
      }

      /* fill the second part of the buffer */
      if ((buf2 != NULL) && (bytes2 > 0)) {
	frames = bytes2 / dev->frame_size;
	dev->write(dev->synth, frames, buf2, 0, 2, buf2, 1, 2);
	cur_position += frames * dev->frame_size;
      }

      /* Unlock */
      IDirectSoundBuffer_Unlock(dev->sec_buffer, buf1, bytes1, buf2, bytes2);

      if (cur_position >= dev->queue_byte_size) {
	cur_position -= dev->queue_byte_size;
      }

    } else {
      Sleep(1);
    }
  }

  ExitThread(0);
  return 0; /* never reached */
}