int main(int argc, char **argv)
{
  plan_tests(47);

  const TCHAR *path = _T("output/test/test.igc");
  File::Delete(path);

  static const GeoPoint home(Angle::Degrees(fixed(7.7061111111111114)),
                             Angle::Degrees(fixed(51.051944444444445)));
  static const GeoPoint tp(Angle::Degrees(fixed(10.726111111111111)),
                           Angle::Degrees(fixed(50.6322)));

  static NMEAInfo i;
  i.clock = fixed_one;
  i.time = fixed(1);
  i.time_available.Update(i.clock);
  i.date_time_utc.year = 2010;
  i.date_time_utc.month = 9;
  i.date_time_utc.day = 4;
  i.date_time_utc.hour = 11;
  i.date_time_utc.minute = 22;
  i.date_time_utc.second = 33;
  i.location = home;
  i.location_available.Update(i.clock);
  i.gps_altitude = fixed(487);
  i.gps_altitude_available.Update(i.clock);
  i.ProvideBaroAltitudeTrue(fixed(490));

  IGCWriter writer(path, i);

  writer.WriteHeader(i.date_time_utc, _T("Pilot Name"), _T("ASK-21"),
                     _T("D-1234"), _T("34"), "FOO", _T("bar"));
  writer.StartDeclaration(i.date_time_utc, 3);
  writer.AddDeclaration(home, _T("Bergneustadt"));
  writer.AddDeclaration(tp, _T("Suhl"));
  writer.AddDeclaration(home, _T("Bergneustadt"));
  writer.EndDeclaration();

  i.date_time_utc.second += 5;
  writer.LogPoint(i);
  i.date_time_utc.second += 5;
  writer.LogEvent(i, "my_event");
  i.date_time_utc.second += 5;
  writer.LoggerNote(_T("my_note"));

  i.date_time_utc.second += 5;
  i.location = GeoPoint(Angle::Degrees(fixed(-7.7061111111111114)),
                        Angle::Degrees(fixed(-51.051944444444445)));
  writer.LogPoint(i);

  writer.Finish(i);
  writer.Sign();

  CheckTextFile(path, expect);

  GRecord grecord;
  grecord.Initialize();
  grecord.SetFileName(path);
  ok1(grecord.VerifyGRecordInFile());

  return exit_status();
}