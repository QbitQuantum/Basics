SoCamera *
QuarterWidgetP::searchForCamera(SoNode * root)
{
  SoSearchAction sa;
  sa.setInterest(SoSearchAction::FIRST);
  sa.setType(SoCamera::getClassTypeId());
  sa.apply(root);

  if (sa.getPath()) {
    SoNode * node = sa.getPath()->getTail();
    if (node && node->isOfType(SoCamera::getClassTypeId())) {
      return (SoCamera *) node;
    }
  }
  return NULL;
}