static gfx::Matrix4x4
GetTransformToAncestorsParentLayer(Layer* aStart, Layer* aAncestor)
{
  gfx::Matrix4x4 transform;
  Layer* ancestorParent = aAncestor->GetParent();
  for (Layer* iter = aStart; iter != ancestorParent; iter = iter->GetParent()) {
    transform = transform * iter->GetTransform();
    // If the layer has a non-transient async transform then we need to apply it here
    // because it will get applied by the APZ in the compositor as well
    const FrameMetrics& metrics = iter->GetFrameMetrics();
    transform = transform * gfx::Matrix4x4().Scale(metrics.mResolution.scale, metrics.mResolution.scale, 1.f);
  }
  return transform;
}