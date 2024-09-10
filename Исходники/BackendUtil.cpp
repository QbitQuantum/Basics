bool DuettoNativeRewriterPass::runOnFunction(Function& F)
{
  DuettoUtils::rewriteNativeObjectsConstructors(*F.getParent(), F);
  return true;
}