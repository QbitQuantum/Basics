static GstEvent *
gst_rg_volume_tag_event (GstRgVolume * self, GstEvent * event)
{
  GstTagList *tag_list;
  gboolean has_track_gain, has_track_peak, has_album_gain, has_album_peak;
  gboolean has_ref_level;

  g_return_val_if_fail (event != NULL, NULL);
  g_return_val_if_fail (GST_EVENT_TYPE (event) == GST_EVENT_TAG, event);

  gst_event_parse_tag (event, &tag_list);

  if (gst_tag_list_is_empty (tag_list))
    return event;

  has_track_gain = gst_tag_list_get_double (tag_list, GST_TAG_TRACK_GAIN,
      &self->track_gain);
  has_track_peak = gst_tag_list_get_double (tag_list, GST_TAG_TRACK_PEAK,
      &self->track_peak);
  has_album_gain = gst_tag_list_get_double (tag_list, GST_TAG_ALBUM_GAIN,
      &self->album_gain);
  has_album_peak = gst_tag_list_get_double (tag_list, GST_TAG_ALBUM_PEAK,
      &self->album_peak);
  has_ref_level = gst_tag_list_get_double (tag_list, GST_TAG_REFERENCE_LEVEL,
      &self->reference_level);

  if (!has_track_gain && !has_track_peak && !has_album_gain && !has_album_peak)
    return event;

  if (has_ref_level && (has_track_gain || has_album_gain)
      && (ABS (self->reference_level - RG_REFERENCE_LEVEL) > 1.e-6)) {
    /* Log a message stating the amount of adjustment that is applied below. */
    GST_DEBUG_OBJECT (self,
        "compensating for reference level difference by %" GAIN_FORMAT,
        RG_REFERENCE_LEVEL - self->reference_level);
  }
  if (has_track_gain) {
    self->track_gain += RG_REFERENCE_LEVEL - self->reference_level;
  }
  if (has_album_gain) {
    self->album_gain += RG_REFERENCE_LEVEL - self->reference_level;
  }

  /* Ignore values that are obviously invalid. */
  if (G_UNLIKELY (has_track_gain && !VALID_GAIN (self->track_gain))) {
    GST_DEBUG_OBJECT (self,
        "ignoring bogus track gain value %" GAIN_FORMAT, self->track_gain);
    has_track_gain = FALSE;
  }
  if (G_UNLIKELY (has_track_peak && !VALID_PEAK (self->track_peak))) {
    GST_DEBUG_OBJECT (self,
        "ignoring bogus track peak value %" PEAK_FORMAT, self->track_peak);
    has_track_peak = FALSE;
  }
  if (G_UNLIKELY (has_album_gain && !VALID_GAIN (self->album_gain))) {
    GST_DEBUG_OBJECT (self,
        "ignoring bogus album gain value %" GAIN_FORMAT, self->album_gain);
    has_album_gain = FALSE;
  }
  if (G_UNLIKELY (has_album_peak && !VALID_PEAK (self->album_peak))) {
    GST_DEBUG_OBJECT (self,
        "ignoring bogus album peak value %" PEAK_FORMAT, self->album_peak);
    has_album_peak = FALSE;
  }

  /* Clamp peaks >1.0.  Float based decoders can produce spurious samples >1.0,
   * cutting these files back to 1.0 should not cause any audible distortion.
   * This is most often seen with Vorbis files. */
  if (has_track_peak && self->track_peak > 1.) {
    GST_DEBUG_OBJECT (self,
        "clamping track peak %" PEAK_FORMAT " to 1.0", self->track_peak);
    self->track_peak = 1.0;
  }
  if (has_album_peak && self->album_peak > 1.) {
    GST_DEBUG_OBJECT (self,
        "clamping album peak %" PEAK_FORMAT " to 1.0", self->album_peak);
    self->album_peak = 1.0;
  }

  self->has_track_gain |= has_track_gain;
  self->has_track_peak |= has_track_peak;
  self->has_album_gain |= has_album_gain;
  self->has_album_peak |= has_album_peak;

  event = (GstEvent *) gst_mini_object_make_writable (GST_MINI_OBJECT (event));
  gst_event_parse_tag (event, &tag_list);

  gst_tag_list_remove_tag (tag_list, GST_TAG_TRACK_GAIN);
  gst_tag_list_remove_tag (tag_list, GST_TAG_TRACK_PEAK);
  gst_tag_list_remove_tag (tag_list, GST_TAG_ALBUM_GAIN);
  gst_tag_list_remove_tag (tag_list, GST_TAG_ALBUM_PEAK);
  gst_tag_list_remove_tag (tag_list, GST_TAG_REFERENCE_LEVEL);

  gst_rg_volume_update_gain (self);

  if (gst_tag_list_is_empty (tag_list)) {
    gst_event_unref (event);
    event = NULL;
  }

  return event;
}