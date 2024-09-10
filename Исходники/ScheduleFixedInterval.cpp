  bool ScheduleFixedInterval_Impl::setTimeSeries(const openstudio::TimeSeries& timeSeries)
  {
    // check the interval
    boost::optional<openstudio::Time> intervalTime = timeSeries.intervalLength();
    if (!intervalTime){
      return false;
    }

    // check the interval
    double intervalLength = intervalTime->totalMinutes();
    if (intervalLength - floor(intervalLength) > 0){
      return false;
    }

    // check the interval
    if (intervalTime->totalDays() > 1){
      return false;
    }

    // check that first report is whole number of intervals from start date
    DateTime firstReportDateTime = timeSeries.firstReportDateTime();
    Date startDate = firstReportDateTime.date();
    Time firstReportTime = firstReportDateTime.time();

    double numIntervalsToFirstReport = std::max(1.0, firstReportTime.totalMinutes() / intervalLength);
    if (numIntervalsToFirstReport - floor(numIntervalsToFirstReport) > 0){
      return false;
    }

    // at this point we are going to change the object
    clearExtensibleGroups(false);

    // set the interval
    this->setIntervalLength(intervalLength, false);

    // set the start date
    this->setStartMonth(startDate.monthOfYear().value(), false);
    this->setStartDay(startDate.dayOfMonth(), false);

    // set the out of range value
    double outOfRangeValue = timeSeries.outOfRangeValue();

    // add in numIntervalsToFirstReport-1 outOfRangeValues to pad the timeseries
    for (unsigned i = 0; i < numIntervalsToFirstReport - 1; ++i){
      std::vector<std::string> temp;
      temp.push_back(toString(outOfRangeValue));

      ModelExtensibleGroup group = pushExtensibleGroup(temp, false).cast<ModelExtensibleGroup>();
      OS_ASSERT(!group.empty());
    }

    // set the values
    openstudio::Vector values = timeSeries.values();
    for (unsigned i = 0; i < values.size(); ++i){
      std::vector<std::string> temp;
      temp.push_back(toString(values[i]));

      ModelExtensibleGroup group = pushExtensibleGroup(temp, false).cast<ModelExtensibleGroup>();
      OS_ASSERT(!group.empty());
    }

    this->emitChangeSignals();

    return true;
  }