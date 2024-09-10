   // -------------------------------------------------------------
   /// 4. forward filter(finalTime,filterDT).
   /// This is main routine; it runs the filter forward to finalTime, using timesteps
   /// filterDT (NB the defineMeasurements() routine controls actual timesteps).
   /// This calls defineTimestep() to get propagation matricies at each timestep.
   /// It calls defineMeasurements() to get time of the next data, data, mcov, and
   /// partials at each timestep. Timing is controlled by defineMeasurements().
   /// It calls defineAddsDrops 3 times, before MU, between MU and TU, and after TU.
   virtual void ForwardFilter(const double finalT, const double filterDT)
      throw(gpstk::Exception)
   {
      int iret;
      try {
         // forward filter: loop over time
         while(time <= finalT) {

            // ------------------------------------------------------------
            // MOD 1: add new state and drop states from the last iteration
            // Calls defineAddsDrops(1,time,addsSRI,dropsNL,(any drops here?))
            iret = KalmanAddsDrops(1,time);

            if(iret) {
               stage = AD1;
               Invert(std::string("Invert after add/drop states"));
               if(doOutput) output(NTU);
            }

            // ------------------------------------------------------------
            // MU: returns 0: Process         : ok, process normally
            //             1: ProcessThenQuit : quit after this data,
            //             2: SkipThisEpoch   : don't process this data, but proceed
            //             3: SkipThenQuit    : skip this data, and then quit
            //             4: QuitImmediately : stop now
            // This defines nexttime as the next available data epoch.
            double nexttime = time;
            KalmanReturn ret = KalmanMeasurementUpdate(nexttime);
            if(ret == QuitImmediately)
               break;
            // else Skip
            // else SkipThenQuit
            else if(ret == Process || ret == ProcessThenQuit) {
               stage = MU;

               if(doInversions) {
                  Invert(std::string("Invert after MU"));
                  if(doOutput) output(NMU);
               }
            }

            // ------------------------------------------------------------
            // MOD 2: add new state and drop states from the last iteration
            // Calls defineAddsDrops(2,time,addsSRI,dropsNL,(any drops here?))
            iret = KalmanAddsDrops(2,time);

            if(iret) {
               stage = AD2;
               Invert(std::string("Invert after add/drop states"));
               if(doOutput) output(NTU);
            }

            // compute next timestep
            double deltaT = nexttime - time;
            if(deltaT > 1.5*filterDT) deltaT=filterDT;

            // ------------------------------------------------------------
            // TU. this will update time by deltaT
            KalmanTimeUpdate(time,deltaT);
            stage = TU;

            if(doInversions) {
               Invert(std::string("Invert after TU"));
               if(doOutput) output(NTU);
            }

            // ------------------------------------------------------------
            // MOD 3: add new state and drop states from the last iteration
            // Calls defineAddsDrops(3,time,addsSRI,dropsNL,(any drops here?))
            iret = KalmanAddsDrops(3,time);

            if(iret) {
               stage = AD3;
               Invert(std::string("Invert after add/drop states"));
               if(doOutput) output(NTU);
            }

            if(ret == ProcessThenQuit || ret == SkipThenQuit) break;

         }  // end loop over forward filter
      }
      catch(gpstk::Exception& e) {
         e.addText("ForwardFilter");
         GPSTK_RETHROW(e);
      }
   }