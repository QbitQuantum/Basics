static HANDLE
gst_ks_video_device_create_pin (GstKsVideoDevice * self,
    KsVideoMediaType * media_type, gulong * num_outstanding)
{
  GstKsVideoDevicePrivate *priv = GST_KS_VIDEO_DEVICE_GET_PRIVATE (self);

  HANDLE pin_handle = INVALID_HANDLE_VALUE;
  KSPIN_CONNECT *pin_conn = NULL;
  DWORD ret;

  GUID *propsets = NULL;
  gulong propsets_len;
  gboolean supports_mem_transport = FALSE;

  KSALLOCATOR_FRAMING *framing = NULL;
  gulong framing_size = sizeof (KSALLOCATOR_FRAMING);
  KSALLOCATOR_FRAMING_EX *framing_ex = NULL;
  gulong alignment;

  DWORD mem_transport;

  /*
   * Instantiate the pin.
   */
  pin_conn = ks_video_create_pin_conn_from_media_type (media_type);

  GST_DEBUG ("calling KsCreatePin with pin_id = %d", media_type->pin_id);

  ret = KsCreatePin (priv->filter_handle, pin_conn, GENERIC_READ, &pin_handle);
  if (ret != ERROR_SUCCESS)
    goto error_create_pin;

  GST_DEBUG ("KsCreatePin succeeded, pin %p created", pin_handle);

  g_free (pin_conn);
  pin_conn = NULL;

  /*
   * Query the pin for supported property sets.
   */
  if (ks_object_get_supported_property_sets (pin_handle, &propsets,
          &propsets_len)) {
    guint i;

    gst_ks_video_device_dump_supported_property_sets (self, "pin", propsets,
        propsets_len);

    for (i = 0; i < propsets_len; i++) {
      if (IsEqualGUID (&propsets[i], &KSPROPSETID_MemoryTransport))
        supports_mem_transport = TRUE;
    }

    g_free (propsets);
  } else {
    GST_DEBUG ("failed to query pin for supported property sets");
  }

  /*
   * Figure out how many simultanous requests it prefers.
   *
   * This is really important as it depends on the driver and the device.
   * Doing too few will result in poor capture performance, whilst doing too
   * many will make some drivers crash really horribly and leave you with a
   * BSOD. I've experienced the latter with older Logitech drivers.
   */
  *num_outstanding = 0;
  alignment = 0;

  if (ks_object_get_property (pin_handle, KSPROPSETID_Connection,
          KSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX, &framing_ex, NULL)) {
    if (framing_ex->CountItems >= 1) {
      *num_outstanding = framing_ex->FramingItem[0].Frames;
      alignment = framing_ex->FramingItem[0].FileAlignment;
    } else {
      GST_DEBUG ("ignoring empty ALLOCATORFRAMING_EX");
    }
  } else {
    GST_DEBUG ("query for ALLOCATORFRAMING_EX failed, trying "
        "ALLOCATORFRAMING");

    if (ks_object_get_property (pin_handle, KSPROPSETID_Connection,
            KSPROPERTY_CONNECTION_ALLOCATORFRAMING, &framing, &framing_size)) {
      *num_outstanding = framing->Frames;
      alignment = framing->FileAlignment;
    } else {
      GST_DEBUG ("query for ALLOCATORFRAMING failed");
    }
  }

  GST_DEBUG ("num_outstanding: %d alignment: 0x%08x", *num_outstanding,
      alignment);

  if (*num_outstanding == 0 || *num_outstanding > MAX_OUTSTANDING_FRAMES) {
    GST_DEBUG ("setting number of allowable outstanding frames to 1");
    *num_outstanding = 1;
  }

  g_free (framing);
  g_free (framing_ex);

  /*
   * TODO: We also need to respect alignment, but for now we just align
   *       on FILE_512_BYTE_ALIGNMENT.
   */

  /* Set the memory transport to use. */
  if (supports_mem_transport) {
    mem_transport = 0;          /* REVISIT: use the constant here */
    if (!ks_object_set_property (pin_handle, KSPROPSETID_MemoryTransport,
            KSPROPERTY_MEMORY_TRANSPORT, &mem_transport,
            sizeof (mem_transport))) {
      GST_DEBUG ("failed to set memory transport, sticking with the default");
    }
  }

  /*
   * Override the clock if we have one and the pin doesn't have any either.
   */
  if (priv->clock != NULL) {
    HANDLE *cur_clock_handle = NULL;
    gulong cur_clock_handle_size = sizeof (HANDLE);

    if (ks_object_get_property (pin_handle, KSPROPSETID_Stream,
            KSPROPERTY_STREAM_MASTERCLOCK, (gpointer *) & cur_clock_handle,
            &cur_clock_handle_size)) {
      GST_DEBUG ("current master clock handle: 0x%08x", *cur_clock_handle);
      CloseHandle (*cur_clock_handle);
      g_free (cur_clock_handle);
    } else {
      HANDLE new_clock_handle = gst_ks_clock_get_handle (priv->clock);

      if (ks_object_set_property (pin_handle, KSPROPSETID_Stream,
              KSPROPERTY_STREAM_MASTERCLOCK, &new_clock_handle,
              sizeof (new_clock_handle))) {
        gst_ks_clock_prepare (priv->clock);
      } else {
        GST_WARNING ("failed to set pin's master clock");
      }
    }
  }

  return pin_handle;

  /* ERRORS */
error_create_pin:
  {
    gchar *str;

    gst_ks_video_device_parse_win32_error ("KsCreatePin", ret, NULL, &str);
    GST_ERROR ("%s", str);
    g_free (str);

    goto beach;
  }
beach:
  {
    g_free (framing);
    if (ks_is_valid_handle (pin_handle))
      CloseHandle (pin_handle);
    g_free (pin_conn);

    return INVALID_HANDLE_VALUE;
  }
}