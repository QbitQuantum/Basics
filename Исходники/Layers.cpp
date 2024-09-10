gfxContext::GraphicsOperator
Layer::GetEffectiveMixBlendMode()
{
  if(mMixBlendMode != gfxContext::OPERATOR_OVER)
    return mMixBlendMode;
  for (ContainerLayer* c = GetParent(); c && !c->UseIntermediateSurface();
    c = c->GetParent()) {
    if(c->mMixBlendMode != gfxContext::OPERATOR_OVER)
      return c->mMixBlendMode;
  }

  return mMixBlendMode;
}