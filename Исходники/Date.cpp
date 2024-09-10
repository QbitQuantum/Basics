 // this needs to be publicly available, for data paraser
 double GetTimezoneOffset(double t)
 {
     return (t - LocalTime(t)) / kMsecPerMinute;
 }