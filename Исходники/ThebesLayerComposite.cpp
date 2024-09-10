gfxSize
ThebesLayerComposite::GetEffectiveResolution()
{
  // Work out render resolution by multiplying the resolution of our ancestors.
  // Only container layers can have frame metrics, so we start off with a
  // resolution of 1, 1.
  // XXX For large layer trees, it would be faster to do this once from the
  //     root node upwards and store the value on each layer.
  gfxSize resolution(1, 1);
  for (ContainerLayer* parent = GetParent(); parent; parent = parent->GetParent()) {
    const FrameMetrics& metrics = parent->GetFrameMetrics();
    resolution.width *= metrics.mResolution.scale;
    resolution.height *= metrics.mResolution.scale;
  }

  return resolution;
}