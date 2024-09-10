 bool RefrigerationDefrostCycleParameters_Impl::setDefrost8StartTime(const openstudio::Time& defrost8StartTime) {
   bool hours = setInt(OS_Refrigeration_DefrostCycleParametersFields::Defrost8HourStartTime, defrost8StartTime.hours());
   bool minutes = setInt(OS_Refrigeration_DefrostCycleParametersFields::Defrost8MinuteStartTime, defrost8StartTime.minutes());
   if ( !hours || !minutes ) {
     resetDefrost8StartTime();
   }
   return hours && minutes;
 }