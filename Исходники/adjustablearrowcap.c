GpStatus
gdip_adjust_arrowcap_destroy (GpCustomLineCap *cap)
{
	if (!cap)
		return InvalidParameter;

	GdipFree (cap);
	return Ok;
}