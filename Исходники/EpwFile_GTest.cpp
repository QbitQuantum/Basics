TEST(Filetypes, EpwFile_Data)
{
  try{
    path p = resourcesPath() / toPath("runmanager/USA_CO_Golden-NREL.724666_TMY3.epw");
    EpwFile epwFile(p);
    EXPECT_EQ(p, epwFile.path());
    EXPECT_EQ("F188656D", epwFile.checksum());
    EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
    EXPECT_EQ("CO", epwFile.stateProvinceRegion());
    EXPECT_EQ("USA", epwFile.country());
    EXPECT_EQ("TMY3", epwFile.dataSource());
    EXPECT_EQ("724666", epwFile.wmoNumber());
    EXPECT_EQ(39.74, epwFile.latitude());
    EXPECT_EQ(-105.18, epwFile.longitude());
    EXPECT_EQ(-7, epwFile.timeZone());
    EXPECT_EQ(1829, epwFile.elevation());
    EXPECT_EQ(Time(0,1,0,0), epwFile.timeStep());
    EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
    EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
    EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
    // Up to here, everything should be the same as the first test. Now ask for the data
    std::vector<EpwDataPoint> data = epwFile.data();
    EXPECT_EQ(8760,data.size());
    // The last data point should be on 12/31/1996, with a dry bulb temp of 4C and presure 81100
    EXPECT_EQ(4.0,data[8759].dryBulbTemperature().get());
    EXPECT_EQ(81100,data[8759].atmosphericStationPressure().get());
    // Try out the alternate access functions, dew point temperature should be -1C
    EXPECT_EQ(-1.0,data[8759].fieldByName("Dew Point Temperature").get());
    EXPECT_EQ(-1.0,data[8759].field(EpwDataField("Dew Point Temperature")).get());
    // The last data point should not have a liquid precipitation depth
    EXPECT_FALSE(data[8759].fieldByName("Liquid Precipitation Depth"));
    // Get a time series
    boost::optional<openstudio::TimeSeries> series = epwFile.getTimeSeries("Wind Speed");
    ASSERT_TRUE(series);
    ASSERT_EQ(8760,series->values().size());
    DateTimeVector seriesTimes = series->dateTimes();
    ASSERT_EQ(8760,seriesTimes.size());
    // Check the times in the data and the time series
    DateTime current(Date(1,1,1999),Time(0,1)); // Use 1999 to avoid leap years
    Time delta(0,1);
    for(unsigned i=0;i<8760;i++) {
      // This is a lot more complicated that it probably should be to avoid the year being a problem
      DateTime datatime = data[i].dateTime();
      EXPECT_EQ(datatime.date().monthOfYear(), current.date().monthOfYear());
      EXPECT_EQ(datatime.date().dayOfMonth(), current.date().dayOfMonth());
      EXPECT_EQ(datatime.time().hours(), current.time().hours());
      EXPECT_EQ(datatime.time().minutes(), current.time().minutes());
      DateTime seriestime = seriesTimes[i];
      EXPECT_EQ(seriestime.date().monthOfYear(), current.date().monthOfYear());
      EXPECT_EQ(seriestime.date().dayOfMonth(), current.date().dayOfMonth());
      EXPECT_EQ(seriestime.time().hours(), current.time().hours());
      EXPECT_EQ(seriestime.time().minutes(), current.time().minutes());
      current += delta;
    }
    // We should redo the original tests because we have reparsed the entire file
    EXPECT_EQ(p, epwFile.path());
    EXPECT_EQ("F188656D", epwFile.checksum());
    EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
    EXPECT_EQ("CO", epwFile.stateProvinceRegion());
    EXPECT_EQ("USA", epwFile.country());
    EXPECT_EQ("TMY3", epwFile.dataSource());
    EXPECT_EQ("724666", epwFile.wmoNumber());
    EXPECT_EQ(39.74, epwFile.latitude());
    EXPECT_EQ(-105.18, epwFile.longitude());
    EXPECT_EQ(-7, epwFile.timeZone());
    EXPECT_EQ(1829, epwFile.elevation());
    EXPECT_EQ(Time(0,1,0,0), epwFile.timeStep());
    EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
    EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
    EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  }catch(...){
    ASSERT_TRUE(false);
  }
}