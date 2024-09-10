 virtual void
 applyDefaultsToRequest(ControlParameters& parameters) const
 {
   if (!parameters.hasFaceId()) {
     parameters.setFaceId(0);
   }
   if (!parameters.hasOrigin()) {
     parameters.setOrigin(ROUTE_ORIGIN_APP);
   }
   if (!parameters.hasCost()) {
     parameters.setCost(0);
   }
   if (!parameters.hasFlags()) {
     parameters.setFlags(ROUTE_FLAG_CHILD_INHERIT);
   }
   if (!parameters.hasExpirationPeriod()) {
     if (parameters.getFaceId() == 0) {
       parameters.setExpirationPeriod(time::milliseconds::max());
     }
     else {
       parameters.setExpirationPeriod(time::hours(1));
     }
   }
 }