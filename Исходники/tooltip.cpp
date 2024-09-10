void TooltipManager::addTooltip(Definition *d)
{
  static bool sourceTooltips = Config_getBool(SOURCE_TOOLTIPS);
  if (!sourceTooltips) return;
  QCString id = d->getOutputFileBase();
  int i=id.findRev('/');
  if (i!=-1)
  {
    id = id.right(id.length()-i-1); // strip path (for CREATE_SUBDIRS=YES)
  }
  id+=escapeId(Doxygen::htmlFileExtension);
  QCString anc = d->anchor();
  if (!anc.isEmpty())
  {
    id+="_"+anc;
  }
  if (p->tooltipInfo.find(id)==0)
  {
    p->tooltipInfo.insert(id,d);
  }
}