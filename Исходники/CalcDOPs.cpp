AlmOrbit ConvertEEtoAO(EngEphemeris& ee)
{
   AlmOrbit ao(
      ee.getPRNID()   , ee.getEcc()   , ee.getI0()-0.3*PI, ee.getOmegaDot()      ,
      ee.getAhalf()   , ee.getOmega0(), ee.getW()        , ee.getM0()            ,
      ee.getAf0()     , ee.getAf1()   , long(ee.getToe()), long(ee.getHOWTime(1)),
      ee.getFullWeek(), ee.getHealth()
      );

   return ao;
}