static gboolean
gst_directsound_ring_buffer_pause (GstRingBuffer * buf)
{
  HRESULT hr = S_OK;
  GstDirectSoundRingBuffer * dsoundbuffer;

  dsoundbuffer = GST_DIRECTSOUND_RING_BUFFER (buf);

  GST_DEBUG ("Pausing RingBuffer");

  GST_DSOUND_LOCK (dsoundbuffer);

  if (dsoundbuffer->pDSB8) {
    hr = IDirectSoundBuffer8_Stop (dsoundbuffer->pDSB8);
  }

  if (G_LIKELY (!dsoundbuffer->suspended)) {
    if (G_UNLIKELY(SuspendThread (dsoundbuffer->hThread) == -1))
      GST_WARNING ("gst_directsound_ring_buffer_pause: SuspendThread failed.");
    else 
      dsoundbuffer->suspended = TRUE;
  }

  GST_DSOUND_UNLOCK (dsoundbuffer);

  /* in the unlikely event that a device was reconfigured, we can consider
   * ourselves stopped even though the stop call failed */
  if (G_UNLIKELY (FAILED(hr)) &&
      G_UNLIKELY(hr != DIRECTSOUND_ERROR_DEVICE_RECONFIGURED) &&
      G_UNLIKELY(hr != DIRECTSOUND_ERROR_DEVICE_NO_DRIVER)) {
    GST_WARNING ("gst_directsound_ring_buffer_pause: IDirectSoundBuffer8_Stop, hr = %X", (unsigned int) hr);
    return FALSE;
  }

  return TRUE;
}