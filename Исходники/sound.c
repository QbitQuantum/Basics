static int
do_play_sound (const char *psz_file, unsigned long ui_volume)
{
  int i_result = 0;
  MCIERROR mci_error = 0;
  char sz_cmd_buf_a[520];
  char sz_ret_buf_a[520];
  MMRESULT mm_result = MMSYSERR_NOERROR;
  unsigned long ui_volume_org = 0;
  BOOL b_reset_volume = FALSE;
  char warn_text[560];

  /* Since UNICOWS.DLL includes only a stub for mciSendStringW, we
     need to encode the file in the ANSI codepage on Windows 9X even
     if w32_unicode_filenames is non-zero.  */
  if (w32_major_version <= 4 || !w32_unicode_filenames)
    {
      char fname_a[MAX_PATH], shortname[MAX_PATH], *fname_to_use;

      filename_to_ansi (psz_file, fname_a);
      fname_to_use = fname_a;
      /* If the file name is not encodable in ANSI, try its short 8+3
	 alias.  This will only work if w32_unicode_filenames is
	 non-zero.  */
      if (_mbspbrk ((const unsigned char *)fname_a,
		    (const unsigned char *)"?"))
	{
	  if (w32_get_short_filename (psz_file, shortname, MAX_PATH))
	    fname_to_use = shortname;
	  else
	    mci_error = MCIERR_FILE_NOT_FOUND;
	}

      if (!mci_error)
	{
	  memset (sz_cmd_buf_a, 0, sizeof (sz_cmd_buf_a));
	  memset (sz_ret_buf_a, 0, sizeof (sz_ret_buf_a));
	  sprintf (sz_cmd_buf_a,
		   "open \"%s\" alias GNUEmacs_PlaySound_Device wait",
		   fname_to_use);
	  mci_error = mciSendStringA (sz_cmd_buf_a,
				      sz_ret_buf_a, sizeof (sz_ret_buf_a), NULL);
	}
    }
  else
    {
      wchar_t sz_cmd_buf_w[520];
      wchar_t sz_ret_buf_w[520];
      wchar_t fname_w[MAX_PATH];

      filename_to_utf16 (psz_file, fname_w);
      memset (sz_cmd_buf_w, 0, sizeof (sz_cmd_buf_w));
      memset (sz_ret_buf_w, 0, sizeof (sz_ret_buf_w));
      /* _swprintf is not available on Windows 9X, so we construct the
	 UTF-16 command string by hand.  */
      wcscpy (sz_cmd_buf_w, L"open \"");
      wcscat (sz_cmd_buf_w, fname_w);
      wcscat (sz_cmd_buf_w, L"\" alias GNUEmacs_PlaySound_Device wait");
      mci_error = mciSendStringW (sz_cmd_buf_w,
				  sz_ret_buf_w, ARRAYELTS (sz_ret_buf_w) , NULL);
    }
  if (mci_error != 0)
    {
      strcpy (warn_text,
	      "mciSendString: 'open' command failed to open sound file ");
      strcat (warn_text, psz_file);
      SOUND_WARNING (mciGetErrorString, mci_error, warn_text);
      i_result = (int) mci_error;
      return i_result;
    }
  if ((ui_volume > 0) && (ui_volume != UINT_MAX))
    {
      mm_result = waveOutGetVolume ((HWAVEOUT) WAVE_MAPPER, &ui_volume_org);
      if (mm_result == MMSYSERR_NOERROR)
        {
          b_reset_volume = TRUE;
          mm_result = waveOutSetVolume ((HWAVEOUT) WAVE_MAPPER, ui_volume);
          if (mm_result != MMSYSERR_NOERROR)
            {
	      SOUND_WARNING (waveOutGetErrorText, mm_result,
			     "waveOutSetVolume: failed to set the volume level"
			     " of the WAVE_MAPPER device.\n"
			     "As a result, the user selected volume level will"
			     " not be used.");
            }
        }
      else
        {
          SOUND_WARNING (waveOutGetErrorText, mm_result,
			 "waveOutGetVolume: failed to obtain the original"
                         " volume level of the WAVE_MAPPER device.\n"
                         "As a result, the user selected volume level will"
                         " not be used.");
        }
    }
  memset (sz_cmd_buf_a, 0, sizeof (sz_cmd_buf_a));
  memset (sz_ret_buf_a, 0, sizeof (sz_ret_buf_a));
  strcpy (sz_cmd_buf_a, "play GNUEmacs_PlaySound_Device wait");
  mci_error = mciSendStringA (sz_cmd_buf_a, sz_ret_buf_a, sizeof (sz_ret_buf_a),
			      NULL);
  if (mci_error != 0)
    {
      strcpy (warn_text,
	      "mciSendString: 'play' command failed to play sound file ");
      strcat (warn_text, psz_file);
      SOUND_WARNING (mciGetErrorString, mci_error, warn_text);
      i_result = (int) mci_error;
    }
  memset (sz_cmd_buf_a, 0, sizeof (sz_cmd_buf_a));
  memset (sz_ret_buf_a, 0, sizeof (sz_ret_buf_a));
  strcpy (sz_cmd_buf_a, "close GNUEmacs_PlaySound_Device wait");
  mci_error = mciSendStringA (sz_cmd_buf_a, sz_ret_buf_a, sizeof (sz_ret_buf_a),
			      NULL);
  if (b_reset_volume == TRUE)
    {
      mm_result = waveOutSetVolume ((HWAVEOUT) WAVE_MAPPER, ui_volume_org);
      if (mm_result != MMSYSERR_NOERROR)
        {
          SOUND_WARNING (waveOutGetErrorText, mm_result,
			 "waveOutSetVolume: failed to reset the original"
                         " volume level of the WAVE_MAPPER device.");
        }
    }
  return i_result;
}