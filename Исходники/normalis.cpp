// Normalize a blob using blob transformations. Less accurate, but
// more accurately copies the old way.
void DENORM::LocalNormBlob(TBLOB* blob) const {
  TBOX blob_box = blob->bounding_box();
  ICOORD translation(-IntCastRounded(x_origin_), -IntCastRounded(y_origin_));
  blob->Move(translation);
  if (y_scale_ != 1.0f)
    blob->Scale(y_scale_);
  if (rotation_ != NULL)
    blob->Rotate(*rotation_);
  translation.set_x(IntCastRounded(final_xshift_));
  translation.set_y(IntCastRounded(final_yshift_));
  blob->Move(translation);
}