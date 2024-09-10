static void
gst_directsound_src_set_mute (GstDirectSoundSrc * dsoundsrc, gboolean mute)
{
  MMRESULT mmres;
  MIXERCONTROLDETAILS details;
  MIXERCONTROLDETAILS_BOOLEAN details_boolean;

  if (dsoundsrc->mixer == NULL || dsoundsrc->control_id_mute < 0) {
    GST_WARNING ("mixer not initialized");
    return;
  }

  details.cbStruct = sizeof (details);
  details.dwControlID = dsoundsrc->control_id_mute;
  details.cChannels = dsoundsrc->mixerline_cchannels;
  details.cMultipleItems = 0;

  details_boolean.fValue = mute;
  details.cbDetails = sizeof (MIXERCONTROLDETAILS_BOOLEAN);
  details.paDetails = &details_boolean;

  mmres = mixerSetControlDetails ((HMIXEROBJ) dsoundsrc->mixer,
      &details, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);

  if (mmres != MMSYSERR_NOERROR)
    GST_WARNING ("Failed to set mute");
  else
    dsoundsrc->mute = mute;
}