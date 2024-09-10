void SchedulesTabController::addRule(model::ScheduleRuleset & scheduleRuleset)
{
  model::ScheduleRule rule(scheduleRuleset);

  rule.daySchedule().addValue(Time(1,0),defaultStartingValue(rule.daySchedule()));
}