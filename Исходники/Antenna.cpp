//------------------------------------------------------------------------------
// onRfEmissionEventAntenna() -- process events for RF Emission not sent by us.
//
// 1) Build a list of emission packets from the queue and compute the
//    Line-Of-Sight (LOS) vectors back to the transmitter.
//
// 2) Transform LOS vectors to antenna coordinates
//
// 3) Compute antenna gains in the direction of the transmitter
//
// 4) Compute Antenna Effective Gains
//
// 5) Compute Antenna Effective Area and Polarization Gains
//
// 6) Compute total receiving antenaa gain and send the emission to our sensor
//------------------------------------------------------------------------------
bool Antenna::onRfEmissionEvent(Emission* const em)
{
   // Is this emission from a player of interest?
   if (fromPlayerOfInterest(em)) {

      Player* ownship = getOwnship();
      RfSystem* sys1 = getSystem();
      if (ownship != 0 && sys1 != 0) {
         sys1->ref();

         // Line-Of-Sight (LOS) vectors back to the transmitter.
         osg::Vec3d xlos = em->getTgtLosVec();
         osg::Vec4d los0( xlos.x(), xlos.y(), xlos.z(), 0.0);

         // 2) Transform local NED LOS vectors to antenna coordinates
         osg::Matrixd mm = getRotMat();
         mm *= ownship->getRotMat();
         osg::Vec4d losA = mm * los0;

         // ---
         // Compute antenna gains in the direction of the transmitter
         // ---
         double rGainDb = 0.0f;
         if (gainPattern != 0) {

            Basic::Func1* gainFunc1 = dynamic_cast<Basic::Func1*>(gainPattern);
            Basic::Func2* gainFunc2 = dynamic_cast<Basic::Func2*>(gainPattern);
            if (gainFunc2 != 0) {
               // ---
               // 3-a) Antenna pattern: 2D table (az & el off antenna boresight)
               // ---

               // Get component arrays and ground range squared
               double xa =  losA.x();
               double ya =  losA.y();
               double za = -losA.z();
               double ra2 = xa*xa + ya*ya;

               // Compute range along antenna x-y plane
               double ra = sqrt(ra2);

               // Compute azimuth off boresight
               double aazr = atan2(ya,xa);

               // Compute elevation off boresight
               double aelr = atan2(za,ra);

               // Lookup gain in 2D table and convert from dB
               if (gainPatternDeg)
                  rGainDb = gainFunc2->f( aazr * Basic::Angle::R2DCC, aelr * Basic::Angle::R2DCC );
               else
                  rGainDb = gainFunc2->f( aazr, aelr );

            }

            else if (gainFunc1 != 0) {
               // ---
                  // 3-b) Antenna Pattern: 1D table (off antenna boresight only
                  // ---

                  // Compute angle off antenna boresight
                  double aar = acos(losA.x());

                  // Lookup gain in 1D table and convert from dB
                  if (gainPatternDeg)
                     rGainDb = gainFunc1->f( aar * Basic::Angle::R2DCC );
                  else
                     rGainDb = gainFunc1->f(aar);

            }
         }

         // Compute off-boresight gain
         double rGain = pow(10.0,rGainDb/10.0);

         // Compute Antenna Effective Gain
         double aeGain = rGain * getGain();
         double lambda = em->getWavelength();
         double aea = getEffectiveArea(aeGain, lambda);

         double pGain = getPolarizationGain(em->getPolarization());
         double raGain = aea * pGain;

         sys1->rfReceivedEmission(em, this, LCreal(raGain));

         sys1->unref();
      }

   }

   return BaseClass::onRfEmissionEvent(em);
}