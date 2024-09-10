void
ChartBase::
setGuide(InputTree* tree)
{
  if(!tree) return;
  int trm = Term::get(tree->term())->toInt();
  guide[tree->start()][tree->finish()].push_back(trm);
  InputTreesIter iti = tree->subTrees().begin();
  for( ; iti!= tree->subTrees().end() ; iti++)
    setGuide(*iti);
}