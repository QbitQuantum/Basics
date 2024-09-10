/**
 * @brief TimeManipulator::toString
 * @param time
 * @return
 */
std::string TimeManipulator::str(const ros::Time& time)
{
  double tenths = time.toSec() - floor(time.toSec());
  long minutes_unix = MathManipulator::getUnsignedDivision((long) floor(time.toSec()), 60);
  int seconds = MathManipulator::getUnsignedRest((long) floor(time.toSec()), 60);
  long hours_unix = MathManipulator::getUnsignedDivision(minutes_unix, 60);
  int minutes = MathManipulator::getUnsignedRest(minutes_unix, 60);
  long days_unix = MathManipulator::getUnsignedDivision(hours_unix, 24);
  int hours = MathManipulator::getUnsignedRest(hours_unix, 24);
  long periods_of_400_years = MathManipulator::getUnsignedDivision(days_unix, 146097);
  int days_in_400_years_period = MathManipulator::getUnsignedRest(days_unix, 146097);
  if (days_in_400_years_period >= 32 * 1461 + 789)
  {
    days_in_400_years_period++;
  }
  if (days_in_400_years_period >= 57 * 1461 + 789)
  {
    days_in_400_years_period++;
  }
  if (days_in_400_years_period >= 82 * 1461 + 789)
  {
    days_in_400_years_period++;
  }
  int periods_of_4_years = days_in_400_years_period / 1461;
  int days_in_4_years_period = days_in_400_years_period % 1461;
  if (days_in_4_years_period >= 59)
  {
    days_in_4_years_period++;
  }
  if (days_in_4_years_period >= 425)
  {
    days_in_4_years_period++;
  }
  if (days_in_4_years_period >= 1157)
  {
    days_in_4_years_period++;
  }
  int year_in_4_years_period = days_in_4_years_period / 366;
  int year_days = days_in_4_years_period % 366;
  int year = year_in_4_years_period + periods_of_4_years * 4 + periods_of_400_years * 400 + 1970;
  int months_table[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int month_counter = 0;
  while(year_days > months_table[month_counter])
  {
    year_days -= months_table[month_counter++];
  }
  int month = month_counter + 1;
  int day = year_days + 1;
  std::stringstream ss;
  ss << (month < 10 ? "0" : "") << month << (day < 10 ? "/0" : "/") << day << (year < 10 ? "/0" : "/") << year;
  ss << (hours < 10 ? " 0" : " ") << hours << (minutes < 10 ? ":0" : ":") << minutes;
  if (seconds + tenths > 0)
  {
    ss << (seconds < 10 ? ":0" : ":") << seconds + tenths;
  }
  return ss.str();
}