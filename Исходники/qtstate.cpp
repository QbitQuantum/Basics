// ---------------------------------------------------------------------
string qtstate(string p)
{
  QStringList s=s2q(p).split(" ",QString::SkipEmptyParts);
  QString c;
  string r;

  if (s.size()==0) return "";
  bool all="all"==s.at(0);

  c="debugpos";
  if (all || s.contains(c))
    r+=qpair(c,p2q(config.DebugPosX));
  c="profont";
  if (all || s.contains(c))
    r+=qpair(c,fontspec(app->font()));
  c="project";
  if (all || s.contains(c))
    r+=qpair(c,recent.ProjectOpen ? project.Path : "");
  c="version";
  if (all || s.contains(c))
    r+=qpair(c,getversion());
  return r;
}