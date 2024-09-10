 /**
  * Compare the MacCready setting with the specified value.
  *
  * @return true if the current setting is the same, false if the
  * value is different or if there is no value
  */
 bool CompareMacCready(fixed value) const {
   return mac_cready_available && fabs(mac_cready - value) <= fixed(0.05);
 }