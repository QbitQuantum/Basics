// Returns the gatetime difference to current local time. Positive if gate is in the future.
int GateTimeDiff(int gate) {
  int timenow, gatetime;
  timenow=LocalTime();
  gatetime=PGOpenTime + (gate * PGGateIntervalTime *60);
  return(gatetime-timenow);
}