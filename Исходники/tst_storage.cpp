void tst_storage::tst_alldayUtc()
{
  // test event saved with UTC time
  auto event = KCalCore::Event::Ptr(new KCalCore::Event);
  QDate startDate(2013, 12, 1);
  event->setDtStart(KDateTime(startDate, QTime(), KDateTime::UTC));
  event->setAllDay(true);
  event->setSummary("test event utc");

  QCOMPARE(event->allDay(), true);

  m_calendar->addEvent(event, NotebookId);
  m_storage->save();
  QString uid = event->uid();
  reloadDb();

  auto fetchedEvent = m_calendar->event(uid);
  QVERIFY(fetchedEvent.data());
  QVERIFY(fetchedEvent->dtStart().isUtc());

  KDateTime localStart = fetchedEvent->dtStart().toLocalZone();
  QVERIFY(localStart.time() == QTime(2, 0));

  KDateTime localEnd = fetchedEvent->dtEnd().toLocalZone();
  QVERIFY(localEnd.time() == QTime(2, 0));

  QCOMPARE(localEnd.date(), localStart.date().addDays(1));
}