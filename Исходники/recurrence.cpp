TimeList Recurrence::recurTimesOn( const QDate &date, const KDateTime::Spec &timeSpec ) const
{
// kDebug() << "recurTimesOn(" << date << ")";
  int i, end;
  TimeList times;

  // The whole day is excepted
  if ( d->mExDates.containsSorted( date ) ) {
    return times;
  }

  // EXRULE takes precedence over RDATE entries, so for all-day events,
  // a matching excule also excludes the whole day automatically
  if ( allDay() ) {
    for ( i = 0, end = d->mExRules.count();  i < end;  ++i ) {
      if ( d->mExRules[i]->recursOn( date, timeSpec ) ) {
        return times;
      }
    }
  }

  KDateTime dt = startDateTime().toTimeSpec( timeSpec );
  if ( dt.date() == date ) {
    times << dt.time();
  }

  bool foundDate = false;
  for ( i = 0, end = d->mRDateTimes.count();  i < end;  ++i ) {
    dt = d->mRDateTimes[i].toTimeSpec( timeSpec );
    if ( dt.date() == date ) {
      times << dt.time();
      foundDate = true;
    } else if ( foundDate ) {
      break; // <= Assume that the rdatetime list is sorted
    }
  }
  for ( i = 0, end = d->mRRules.count();  i < end;  ++i ) {
    times += d->mRRules[i]->recurTimesOn( date, timeSpec );
  }
  times.sortUnique();

  foundDate = false;
  TimeList extimes;
  for ( i = 0, end = d->mExDateTimes.count();  i < end;  ++i ) {
    dt = d->mExDateTimes[i].toTimeSpec( timeSpec );
    if ( dt.date() == date ) {
      extimes << dt.time();
      foundDate = true;
    } else if ( foundDate ) {
      break;
    }
  }
  if ( !allDay() ) {     // we have already checked all-day times above
    for ( i = 0, end = d->mExRules.count();  i < end;  ++i ) {
      extimes += d->mExRules[i]->recurTimesOn( date, timeSpec );
    }
  }
  extimes.sortUnique();

  int st = 0;
  for ( i = 0, end = extimes.count();  i < end;  ++i ) {
    int j = times.removeSorted( extimes[i], st );
    if ( j >= 0 ) {
      st = j;
    }
  }
  return times;
}