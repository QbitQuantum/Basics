bool
play_pcm_file (playable_pcm_file_t *file)
{
  int                 status;
  snd_pcm_t          *handle;
  snd_pcm_format_t    format;
  snd_pcm_sframes_t   frames_wrote;
  uint8_t             playback_buf[BUFSIZ];
  int                 frames_count;
  size_t              read_bytes;


  format = determine_pcm_format (&(file->info));
  if (format == SND_PCM_FORMAT_UNKNOWN)
    {
      fprintf (stderr, "%s: Unable to determine the beep's PCM data format.\n",
               progname);

      return false;
    }

  if (fsetpos (file->stream, &(file->pcm_start_pos)) != 0)
    {
      fprintf (stderr, "%s: Failed to seek to the PCM data of `%s': %s.\n",
               progname, file->name, strerror (errno));

      return false;
    }

  status = snd_pcm_open (&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
  if (status < 0)
    {
      fprintf (stderr, "%s: Failed to open the playback device: %s\n",
               progname, snd_strerror (status));

      return false;
    }

  status = snd_pcm_set_params (handle, format, SND_PCM_ACCESS_RW_INTERLEAVED,
                               file->info.channels, file->info.sample_rate,
                               1,          /* soft_resample */
                               0);         /* latency (us).*/
  if (status < 0)
    {
      fprintf (stderr, "%s: Failed to configure the playback device: %s.\n",
               progname, snd_strerror (status));

      snd_pcm_close (handle);
      return false;
    }

  while (true)
    {
      read_bytes = fread (playback_buf, 1, BUFSIZ, file->stream);
      if (read_bytes == 0)
        {
          if (ferror (file->stream))
            {
              fprintf (stderr, "%s: An error occured while reading from `%s': %s.\n",
                       progname, file->name, strerror (errno));

              snd_pcm_close (handle);
              return false;
            }

          break;
        }
      frames_count = snd_pcm_bytes_to_frames (handle, read_bytes);
      frames_wrote = snd_pcm_writei (handle, playback_buf, frames_count);
      if (frames_wrote < 0)
        frames_wrote = snd_pcm_recover (handle, frames_wrote, 0);

      if (frames_wrote < 0)
        {
          fprintf (stderr, "%s: Writing to the playback device failed: %s.\n",
                   progname, snd_strerror (frames_wrote));

          snd_pcm_close (handle);
          return false;
        }

      if (frames_wrote > 0 && frames_wrote < frames_count)
        {
          fprintf (stderr, "%s: Warning: Wrote only %ld frames instead of the "
                   "expected %d to the playback device.\n",
                   progname, frames_wrote, frames_count);
        }
    }

  snd_pcm_drain (handle);
  snd_pcm_close (handle);

  return true;
}