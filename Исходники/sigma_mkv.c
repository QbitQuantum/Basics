static void kraise_splice (char *file1, char *file2, char *fileout) {

  kr_mkv_t *in[2];
  kr_mkv_t *out;
  int i;
  int bytes_read;
  uint32_t track;
  uint64_t timecode;
  uint8_t *buffer[2];
  uint32_t out_track;
  int keyframe;
  uint8_t flags;
  int packets;
  int have_buffer[2];
  int have_buffer_bytes[2];
  int inframes;

  have_buffer_bytes[0] = 0;
  have_buffer_bytes[1] = 0;
  have_buffer[1] = 0;
  inframes = 0;
  have_buffer[0] = 0;
  have_buffer[1] = 0;
  packets = 0;

  buffer[0] = malloc (10000000);
  buffer[1] = malloc (10000000);

  for (i = 0; i < 2; i++) {

    if (i == 0) {
      in[i] = kr_mkv_open_file (file1);
    } else {
      in[i] = kr_mkv_open_file (file2);
    }


    printf ("File %d: FPS %d/%d RES %dx%d\n",
            i,
            in[i]->tracks[VIDEO_TRACK].fps_numerator,
            in[i]->tracks[VIDEO_TRACK].fps_denominator,
            in[i]->tracks[VIDEO_TRACK].width,
            in[i]->tracks[VIDEO_TRACK].height);

    if (in[0] == NULL) {
      fprintf (stderr, "Could not open input file: %s\n", file1);
      exit (1);
    }
  }


  if ((in[0]->tracks[VIDEO_TRACK].width != in[0]->tracks[VIDEO_TRACK].width) ||
      (in[1]->tracks[VIDEO_TRACK].height != in[1]->tracks[VIDEO_TRACK].height)) {

    fprintf (stderr, "Resolutions are not equal\n");
    exit (1);
  }


  out = kr_mkv_create_file (fileout);

  if (out == NULL) {
    fprintf (stderr, "Could not open output file: %s\n", fileout);
    exit (1);
  }

  printf ("Created file: %s\n", fileout);

  out_track = kr_mkv_add_video_track (out, VP8,
                                     30,
                                     1,
                                     in[0]->tracks[VIDEO_TRACK].width,
                                     in[0]->tracks[VIDEO_TRACK].height);

  printf ("Added new track: %d\n", out_track);




  while ((bytes_read = kr_mkv_read_packet (in[0], &track, &timecode, &flags, buffer[0])) > 0) {

    have_buffer_bytes[0] = bytes_read;

    printf ("Read file %d packet %d track %d %d bytes\n",
            1, packets++, track, bytes_read);
    fflush (stdout);

    if (flags == 0x80) {
      keyframe = 1;
    } else {
      keyframe = 0;
    }

    if (keyframe == 1) {
      inframes = 0;
      while ((have_buffer[1] == 1) ||
             (((bytes_read = kr_mkv_read_packet (in[1], &track, &timecode, &flags, buffer[1])) > 0))) {

        if (have_buffer[1] == 1) {
          keyframe = 1;
          have_buffer[1] = 0;
        } else {
          printf ("Read file %d packet %d track %d %d bytes\n",
                  2, packets++, track, bytes_read);
          fflush (stdout);

          if (flags == 0x80) {
            keyframe = 1;
          } else {
            keyframe = 0;
          }

          have_buffer_bytes[1] = bytes_read;

          if ((keyframe == 1) && (inframes > 0)) {
            have_buffer[1] = 1;
            break;
          }
        }
        if (track == 1) {
          kr_mkv_add_video (out, out_track, buffer[1], have_buffer_bytes[1], keyframe);
        }
        inframes++;
      }
    }

    if (track == 1) {
      kr_mkv_add_video (out, out_track, buffer[0], have_buffer_bytes[0], keyframe);
    }
  }

  printf ("\nDone.\n");

  free (buffer[0]);
  free (buffer[1]);
  kr_mkv_destroy (&in[0]);
  kr_mkv_destroy (&in[1]);
  kr_mkv_destroy (&out);

}