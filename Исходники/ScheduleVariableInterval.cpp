  bool ScheduleVariableInterval_Impl::setTimeSeries(const openstudio::TimeSeries& timeSeries)
  {

    clearExtensibleGroups(false);

    DateTime firstReportDateTime = timeSeries.firstReportDateTime();
    Date startDate = firstReportDateTime.date();

    // set the start date
    this->setStartMonth(startDate.monthOfYear().value(), false);
    this->setStartDay(startDate.dayOfMonth(), false);

    // set the out of range value
    double outOfRangeValue = timeSeries.outOfRangeValue();
    this->setOutOfRangeValue(outOfRangeValue);

    // set the values
    std::vector<long> secondsFromFirstReport = timeSeries.secondsFromFirstReport();
    openstudio::Vector values = timeSeries.values();
    for (unsigned i = 0; i < values.size(); ++i){
      DateTime dateTime = firstReportDateTime + Time(0,0,0,secondsFromFirstReport[i]);
      Date date = dateTime.date();
      Time time = dateTime.time();

      std::vector<std::string> temp;
      temp.push_back(boost::lexical_cast<std::string>(date.monthOfYear().value()));
      temp.push_back(boost::lexical_cast<std::string>(date.dayOfMonth()));
      temp.push_back(boost::lexical_cast<std::string>(time.hours()));
      temp.push_back(boost::lexical_cast<std::string>(time.minutes()));
      temp.push_back(toString(values[i]));

      ModelExtensibleGroup group = pushExtensibleGroup(temp, false).cast<ModelExtensibleGroup>();
      OS_ASSERT(!group.empty());
    }
    
    this->emitChangeSignals();

    return true;
  }