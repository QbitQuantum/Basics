TimeDelta SampleModePrefUI::GetSampleInterval() const {
  int time_value = wcstol(sample_interval_edit_->GetText(), NULL, 10);
  TimeScale scale = static_cast<TimeScale>(sample_interval_combo_->GetCurSel());
  switch (scale) {
  case SECOND:
    return TimeDelta::FromSeconds(time_value);
  case MINUTE:
    return TimeDelta::FromMinutes(time_value);
  case HOUR:
    return TimeDelta::FromHours(time_value);
  case DAY:
    return TimeDelta::FromDays(time_value);
  }
  return TimeDelta::Max();
}