  bool ScheduleDay_Impl::addValue(const openstudio::Time& untilTime, double value) {
    if (untilTime.totalMinutes() <= 0.5 || untilTime.totalDays() > 1.0) {
      return false;
    }

    int untilHours = untilTime.hours() + 24*untilTime.days();
    int untilMinutes = untilTime.minutes() + floor((untilTime.seconds()/60.0) + 0.5);

    if (untilMinutes >= 60){
      untilHours += 1;
      untilMinutes += -60;
    }

    // use set to determine whether to overwrite or insert, and where
    std::set<openstudio::Time> times;
    std::pair<std::set<openstudio::Time>::const_iterator,bool> insertResult;
    for (const openstudio::Time& time : this->times()) {
      insertResult = times.insert(time);
      OS_ASSERT(insertResult.second);
    }

    insertResult = times.insert(untilTime);
    unsigned index = std::distance<std::set<openstudio::Time>::const_iterator>(times.begin(),insertResult.first);
    OS_ASSERT(index <= numExtensibleGroups());
    bool result(true);
    if (insertResult.second) {
      // new time--insert an extensible group
      std::vector<std::string> groupValues;
      groupValues.push_back(boost::lexical_cast<std::string>(untilHours));
      groupValues.push_back(boost::lexical_cast<std::string>(untilMinutes));
      groupValues.push_back(toString(value));

      IdfExtensibleGroup group = insertExtensibleGroup(index, groupValues);
      OS_ASSERT(!group.empty());
    }
    else {
      // time already exists, overwrite value
      IdfExtensibleGroup group = getExtensibleGroup(index);
      result = group.setDouble(OS_Schedule_DayExtensibleFields::ValueUntilTime,value);
    }

    return result;
  }