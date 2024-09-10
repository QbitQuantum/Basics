QVector<Fluo> FluoDBase::removeTooNears( QVector<Fluo> list, double dE )
// list はソート済みと仮定する
{
  double val0;
  int no0;

  for ( int i = 0; i < list.count(); i++ ) {
    val0 = list[i].val;
    no0 = list[i].aNumber;
    for ( int j = i+1; j < list.count() && (( list[j].val - val0 ) < dE ); j++ ) {
      if ( list[j].aNumber == no0 )
	list.remove( j );
    }
  }

  return list;
}