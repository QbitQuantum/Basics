static GstFlowReturn
gst_rg_limiter_transform_ip (GstBaseTransform * base, GstBuffer * buf)
{
  GstRgLimiter *filter = GST_RG_LIMITER (base);
  gfloat *input;
  guint count;
  guint i;

  if (!filter->enabled)
    return GST_FLOW_OK;

  if (GST_BUFFER_FLAG_IS_SET (buf, GST_BUFFER_FLAG_GAP))
    return GST_FLOW_OK;

  input = (gfloat *) GST_BUFFER_DATA (buf);
  count = GST_BUFFER_SIZE (buf) / sizeof (gfloat);

  for (i = count; i--;) {
    if (*input > THRES)
      *input = tanhf ((*input - THRES) / COMPL) * COMPL + THRES;
    else if (*input < -THRES)
      *input = tanhf ((*input + THRES) / COMPL) * COMPL - THRES;
    input++;
  }

  return GST_FLOW_OK;
}