void TraceTest::all_serialisation_single()
{
  Trace::TraceCallback callbackRcv;
  Trace::TraceCallback callbackSingle;
  callbackSingle["callbackSingle"]= QStringList("first line");
  QVERIFY("first line" == callbackSingle["callbackSingle"].first());
  QVERIFY(callbackSingle.contains("callbackSingle"));
  QCOMPARE(1,callbackSingle["callbackSingle"].count());

  Trace::TraceFilter filterRcv;
  Trace::TraceFilter filterSingle;
  filterSingle["test_single_filter"]=Trace::TraceID_Warn;
  QCOMPARE(Trace::TraceID_Warn, filterSingle["test_single_filter"]);

  Trace::TraceMessage messageRcv;
  Trace::TraceMessage messageSingle;
  messageSingle = QStringList() << "a single message";

  QByteArray bytearray;
  QDataStream ts( &bytearray,QIODevice::WriteOnly  );
  Trace::serialize(ts,filterSingle);
  Trace::serialize(ts,messageSingle);
  Trace::serialize(ts,callbackSingle);

  QDataStream ds( &bytearray, QIODevice::ReadOnly );
  Trace::deserialize(ds,filterRcv,messageRcv,callbackRcv);

  QVERIFY(callbackRcv.contains("callbackSingle"));
  QCOMPARE(1,callbackRcv["callbackSingle"].count());
  QVERIFY("first line" == callbackRcv["callbackSingle"].first());

  QVERIFY(filterRcv.contains("test_single_filter"));
  QCOMPARE(Trace::TraceID_Warn, filterRcv["test_single_filter"]);

  QCOMPARE(messageSingle.count(),messageRcv.count());
  QCOMPARE(qPrintable(messageSingle.first()),qPrintable(messageRcv.first()));

}