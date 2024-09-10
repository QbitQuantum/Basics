static GstFlowReturn
gst_dx9screencapsrc_create (GstPushSrc * push_src, GstBuffer ** buf)
{
  GstDX9ScreenCapSrc *src = GST_DX9SCREENCAPSRC (push_src);
  GstBuffer *new_buf;
  gint new_buf_size, i;
  gint width, height, stride;
  GstClock *clock;
  GstClockTime buf_time, buf_dur;
  D3DLOCKED_RECT locked_rect;
  LPBYTE p_dst, p_src;
  HRESULT hres;
  GstMapInfo map;
  guint64 frame_number;

  if (G_UNLIKELY (!src->d3d9_device)) {
    GST_ELEMENT_ERROR (src, CORE, NEGOTIATION, (NULL),
        ("format wasn't negotiated before create function"));
    return GST_FLOW_NOT_NEGOTIATED;
  }

  clock = gst_element_get_clock (GST_ELEMENT (src));
  if (clock != NULL) {
    GstClockTime time, base_time;

    /* Calculate sync time. */

    time = gst_clock_get_time (clock);
    base_time = gst_element_get_base_time (GST_ELEMENT (src));
    buf_time = time - base_time;

    if (src->rate_numerator) {
      frame_number = gst_util_uint64_scale (buf_time,
          src->rate_numerator, GST_SECOND * src->rate_denominator);
    } else {
      frame_number = -1;
    }
  } else {
    buf_time = GST_CLOCK_TIME_NONE;
    frame_number = -1;
  }

  if (frame_number != -1 && frame_number == src->frame_number) {
    GstClockID id;
    GstClockReturn ret;

    /* Need to wait for the next frame */
    frame_number += 1;

    /* Figure out what the next frame time is */
    buf_time = gst_util_uint64_scale (frame_number,
        src->rate_denominator * GST_SECOND, src->rate_numerator);

    id = gst_clock_new_single_shot_id (clock,
        buf_time + gst_element_get_base_time (GST_ELEMENT (src)));
    GST_OBJECT_LOCK (src);
    src->clock_id = id;
    GST_OBJECT_UNLOCK (src);

    GST_DEBUG_OBJECT (src, "Waiting for next frame time %" G_GUINT64_FORMAT,
        buf_time);
    ret = gst_clock_id_wait (id, NULL);
    GST_OBJECT_LOCK (src);

    gst_clock_id_unref (id);
    src->clock_id = NULL;
    if (ret == GST_CLOCK_UNSCHEDULED) {
      /* Got woken up by the unlock function */
      GST_OBJECT_UNLOCK (src);
      return GST_FLOW_FLUSHING;
    }
    GST_OBJECT_UNLOCK (src);

    /* Duration is a complete 1/fps frame duration */
    buf_dur =
        gst_util_uint64_scale_int (GST_SECOND, src->rate_denominator,
        src->rate_numerator);
  } else if (frame_number != -1) {
    GstClockTime next_buf_time;

    GST_DEBUG_OBJECT (src, "No need to wait for next frame time %"
        G_GUINT64_FORMAT " next frame = %" G_GINT64_FORMAT " prev = %"
        G_GINT64_FORMAT, buf_time, frame_number, src->frame_number);
    next_buf_time = gst_util_uint64_scale (frame_number + 1,
        src->rate_denominator * GST_SECOND, src->rate_numerator);
    /* Frame duration is from now until the next expected capture time */
    buf_dur = next_buf_time - buf_time;
  } else {
    buf_dur = GST_CLOCK_TIME_NONE;
  }
  src->frame_number = frame_number;

  height = (src->src_rect.bottom - src->src_rect.top);
  width = (src->src_rect.right - src->src_rect.left);
  new_buf_size = width * 4 * height;

  GST_LOG_OBJECT (src,
      "creating buffer of %d bytes with %dx%d image",
      new_buf_size, width, height);

  /* Do screen capture and put it into buffer...
   * Aquire front buffer, and lock it
   */
  hres =
      IDirect3DDevice9_GetFrontBufferData (src->d3d9_device, 0, src->surface);
  if (FAILED (hres)) {
    GST_DEBUG_OBJECT (src, "DirectX::GetBackBuffer failed.");
    return GST_FLOW_ERROR;
  }

  if (src->show_cursor) {
    CURSORINFO ci;

    ci.cbSize = sizeof (CURSORINFO);
    GetCursorInfo (&ci);
    if (ci.flags & CURSOR_SHOWING) {
      ICONINFO ii;
      HDC memDC;

      GetIconInfo (ci.hCursor, &ii);

      if (SUCCEEDED (IDirect3DSurface9_GetDC (src->surface, &memDC))) {
        HCURSOR cursor = CopyImage (ci.hCursor, IMAGE_CURSOR, 0, 0,
            LR_MONOCHROME | LR_DEFAULTSIZE);

        DrawIcon (memDC,
            ci.ptScreenPos.x - ii.xHotspot - src->monitor_info.rcMonitor.left,
            ci.ptScreenPos.y - ii.yHotspot - src->monitor_info.rcMonitor.top,
            cursor);

        DestroyCursor (cursor);
        IDirect3DSurface9_ReleaseDC (src->surface, memDC);
      }

      DeleteObject (ii.hbmColor);
      DeleteObject (ii.hbmMask);
    }
  }

  hres =
      IDirect3DSurface9_LockRect (src->surface, &locked_rect, &(src->src_rect),
      D3DLOCK_NO_DIRTY_UPDATE | D3DLOCK_NOSYSLOCK | D3DLOCK_READONLY);
  if (FAILED (hres)) {
    GST_DEBUG_OBJECT (src, "DirectX::LockRect failed.");
    return GST_FLOW_ERROR;
  }

  new_buf = gst_buffer_new_and_alloc (new_buf_size);
  gst_buffer_map (new_buf, &map, GST_MAP_WRITE);
  p_dst = (LPBYTE) map.data;
  p_src = (LPBYTE) locked_rect.pBits;
  stride = width * 4;
  for (i = 0; i < height; ++i) {
    memcpy (p_dst, p_src, stride);
    p_dst += stride;
    p_src += locked_rect.Pitch;
  }
  gst_buffer_unmap (new_buf, &map);

  /* Unlock copy of front buffer */
  IDirect3DSurface9_UnlockRect (src->surface);

  GST_BUFFER_TIMESTAMP (new_buf) = buf_time;
  GST_BUFFER_DURATION (new_buf) = buf_dur;

  if (clock != NULL)
    gst_object_unref (clock);

  *buf = new_buf;
  return GST_FLOW_OK;
}