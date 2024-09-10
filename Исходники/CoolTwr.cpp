void CoolingTower::EvalProducts(CNodeEvalIndex & NEI)
  {
  switch (SolveMethod())
    {
    case SM_Direct:
      {
      const int wi = H2OLiq();
      const int si = H2OVap();
      const int ioLiq = IOWithId_Self(ioid_Liq);
      const int ioVap = IOWithId_Self(ioid_Vap);
      const int ioLoss = IOWithId_Self(ioid_LiqLoss);
      const int ioDrift = IOWithId_Self(ioid_DriftLoss);
      
      SpConduit & Ql=*IOConduit(ioLiq);
      SpConduit & Qv=*IOConduit(ioVap);
      
      StkSpConduit QMix("Mix", chLINEID(), this);

      iCycles = Max(2L, iCycles);
      dLGRatio = Range(0.01, dLGRatio, 10.0);
      ClrCI(3);
      ClrCI(4);
      ClrCI(5);
      ClrCI(6);
      dDuty = 0.0;
      SigmaQInPMin(QMix(), som_ALL, Id_2_Mask(ioid_Feed));
      Ql.QCopy(QMix());
      Qv.QCopy(QMix());

      const double QmWaterLiqIn = QMix().VMass[wi];
      const double QmWaterVapIn = QMix().VMass[si];
      const double QmVapIn = QMix().QMass(som_Gas);
      dQmIn = QMix().QMass(som_ALL);
      const flag HasFlw = (dQmIn>UsableMass);
      dTempKFeed = QMix().Temp();
      const double TotHfAtFeedT_Before = QMix().totHf(som_ALL, dTempKFeed, QMix().Press());
      
      //RB.EvalProducts(QMix);
      //EHX.EvalProducts(QMix);

      //double POut = AtmosPress(); //force outlet to Atmos P
      double POut = Std_P; //force outlet to Std_P

      //double AvgCellAgeY=AvgCellAge/(365.25*24.0*60.0*60.0);   
      //double TimeSinceDescaleM=TimeSinceDescale/(365.25*24.0*60.0*60.0/12.0);   
      //double RqdLiqTemp = AirWetBulbT + Approach + AvgCellAgeY*1.1 + TimeSinceDescaleM/12.0*4.0;
      double RqdLiqTemp = dAirWetBulbT + dApproachT;
      double T1 = QMix().Temp();
      double T2 = RqdLiqTemp;
      dLossQm = 0.0;
      bool ValidData;
      switch (iMethod)
        {
        case CTM_Simple: ValidData = (RqdLiqTemp<T1); break;
        case CTM_Merkel: ValidData = (iMerkelCalcType==MCT_TOut ? (dAirWetBulbT<T1) : (RqdLiqTemp<T1)); break;
        }
      if (!HasFlw)
        ValidData = false;
      double RqdLiqTempUsed;
      if (ValidData)
        {
        m_VLE.SetHfInAtZero(QMix());
        if (iMethod==CTM_Simple)
          {
          //const double h1 = QMix().totHf();
          RqdLiqTempUsed = RqdLiqTemp;
          EvapFnd EF(QMix(), RqdLiqTempUsed, POut, m_VLE);//QMix().Press());
          EF.SetTarget(QMix().totHf());
          if (Valid(dEvapFrac))
            {
            EF.SetEstimate(dEvapFrac, 1.0);
            //dEvapFrac = dNAN;
            }
          flag Ok = false;
          dMaxEvapFrac = Range(0.01, dMaxEvapFrac, 1.0);
          int iRet=EF.Start(0.0, dMaxEvapFrac);
          if (iRet==RF_EstimateOK) //estimate is good, solve not required
            {
            Ok = true;
            }
          else
            {
            if (iRet==RF_BadEstimate)
              iRet = EF.Start(0.0, dMaxEvapFrac); // Restart
            if (iRet==RF_OK)
              if (EF.Solve_Brent()==RF_OK)
                Ok = true;
            }
          dEvapFrac = EF.Result(); //use result regardless
          if (!Ok)
            {
            SigmaQInPMin(QMix(), som_ALL, Id_2_Mask(ioid_Feed));
            m_VLE.SetSatPVapFrac(QMix(), dEvapFrac, 0);
            QMix().SetPress(POut);
            RqdLiqTempUsed = QMix().Temp();
            }
          //const double h2 = QMix().totHf();
          //dDuty = h1-h2; this gives 0 (as expected)
          //dDuty is zero because there is no heattransfer with the air
          }
        else
          {
          dAirCp = Max(0.000001, dAirCp);
          dAirWetBulbT = Range(MerkelTMn, dAirWetBulbT, MerkelTMx-10.0);
          if (T1<MerkelTMn || T1>MerkelTMx)
            {
            SetCI(6, true);
            T1 = Range(MerkelTMn, T1, MerkelTMx);
            }

          MerkelTempFnd Fnd(QMix(), *this, T1);
          if (iMerkelCalcType==MCT_KaVL)
            {
            if (T2<MerkelTMn || T2>MerkelTMx)
              {
              SetCI(5, true);
              T2 = Range(MerkelTMn, T2, MerkelTMx);
              RqdLiqTemp = T2;
              }
            dKaVL = Fnd.Function(T2);
            }
          else
            {
            Fnd.SetTarget(dKaVL);
            //Note that for high LG_Ratio (eg>1.0) then ApproachT is higher.

            double Mn = dAirWetBulbT+(T1-dAirWetBulbT)*0.005;
            const double Mx = dAirWetBulbT+(T1-dAirWetBulbT)*0.999;//T1-0.001;
            if (Valid(RqdLiqTemp) && RqdLiqTemp>Mn && RqdLiqTemp<Mx)
              {
              Fnd.SetEstimate(RqdLiqTemp, 1.0);
              //RqdLiqTemp = dNAN;
              }
            flag Ok = false;
            int iRet=Fnd.Start(Mn, Mx);
            if (iRet==RF_EstimateOK) //estimate is good, solve not required
              {
              Ok = true;
              }
            else
              {
              double KaVL_MnTest = Fnd.Function(Mn);
              if (KaVL_MnTest<0.0)
                {
                //Crude fix to find min temp that doesn't cause KaV/L to be negative...
                double fr = 0.01;
                while (KaVL_MnTest<0.0 && fr<0.9)
                  {
                  Mn = dAirWetBulbT+(T1-dAirWetBulbT)*fr;
                  KaVL_MnTest = Fnd.Function(Mn);
                  fr += 0.01;
                  }
                iRet = Fnd.Start(Mn, Mx); // Restart
                }
              if (iRet==RF_OK)
                if (Fnd.Solve_Brent()==RF_OK)
                  Ok = true;
              }
            RqdLiqTemp = Fnd.Result(); //use result regardless
            T2 = RqdLiqTemp;
            if (!Ok)
              {
              const double KaVL_Calc = Fnd.Function(T2);
              SetCI(3, fabs(KaVL_Calc-dKaVL)>1.0e-6);
              }
            dApproachT = RqdLiqTemp - dAirWetBulbT;
            }

          dEvapFactor = Min(dEvapFactor, 0.1); //prevent user from puting a silly large number for this
          dEvapLossQm = dQmIn * dEvapFactor * (C2F(T1)-C2F(T2));//Evaporation Loss: WLe =  Wc * EvapFactor * dT
          dEvapLossQm = Min(dEvapLossQm, QmWaterLiqIn); //limit the amount that can be evaporated


          RqdLiqTempUsed = RqdLiqTemp;

          dEvapFrac = Min(dMaxEvapFrac, (dEvapLossQm+QmWaterVapIn)/GTZ(QmWaterLiqIn+QmWaterVapIn));
          const double h1 = QMix().totHf();
          m_VLE.SetSatPVapFrac(QMix(), dEvapFrac, 0);
          QMix().SetPress(POut);
          QMix().SetTemp(RqdLiqTempUsed);
          const double h2 = QMix().totHf();
          dDuty = h1-h2;

          //dAirEnthOut = AirEnth(T2);
          dAirEnthOut = Fnd.h2 / 0.430210432; //convert from Btu/lb to kJ/kg
          dAirQmIn = dQmIn/dLGRatio;
          dAirTRise = dDuty/GTZ(dAirQmIn)/dAirCp;
          dAirTOut = dAirDryBulbT + dAirTRise;
          dAirMixQm = dAirQmIn + dEvapLossQm;
          const double EvapLossCp = Qv.msCp();
          dAirMixCp = dAirQmIn/GTZ(dAirMixQm)*dAirCp + dEvapLossQm/GTZ(dAirMixQm)*EvapLossCp;
          dAirMixT = dAirQmIn/GTZ(dAirMixQm)*dAirTOut + dEvapLossQm/GTZ(dAirMixQm)*T2;
          }

        double QmWaterVapOut = QMix().VMass[si];
        dQmWaterEvap = Max(0.0, QmWaterVapOut - QmWaterVapIn);
        if (iMethod==CTM_Simple)
          dEvapLossQm=dQmWaterEvap;
        switch (iLossMethod)
          {
          case WLM_None: 
            dDriftLossQm = 0.0;
            dBlowdownLossQm = 0.0;
            dLossQm = 0.0; 
            break;
          case WLM_Frac: 
            dRqdDriftLossFrac = Range(0.0, dRqdDriftLossFrac, 1.0);
            dRqdLossFrac = Range(0.0, dRqdLossFrac, 0.9);
            dLossQm = dQmIn * dRqdLossFrac;
            dDriftLossQm = dLossQm * dRqdDriftLossFrac;
            dBlowdownLossQm = dLossQm - dDriftLossQm;
            break;
          case WLM_Qm: 
            dRqdDriftLossFrac = Range(0.0, dRqdDriftLossFrac, 1.0);
            dLossQm = dRqdLossQm;
            dDriftLossQm = dLossQm * dRqdDriftLossFrac;
            dBlowdownLossQm = dLossQm - dDriftLossQm;
            break;
          case WLM_DriftBlowdown:
            dDriftLossQm = dQmIn * dDriftLossFrac;//Drift Loss: WLd = % of water flow
            dBlowdownLossQm = dEvapLossQm/(iCycles-1);//Blowdown Loss: WLb = WLe / (cycles - 1)
            dLossQm = dDriftLossQm+dBlowdownLossQm;
            break;
          }
        if (dLossQm>dQmIn-dEvapLossQm-QmVapIn)
          {
          SetCI(4, true);
          dLossQm = dQmIn-dEvapLossQm-QmVapIn;
          }
        m_VLE.AddHfOutAtZero(QMix());
        }
      else
        {
        RqdLiqTempUsed = T1;
        dEvapFrac = 0.0;
        dLossQm = 0.0;
        dDriftLossQm = 0.0;
        dBlowdownLossQm = 0.0;
        dEvapLossQm = 0.0;
        dQmWaterEvap = 0.0;
        //if (iMethod==CTM_Merkel)
          {
          dAirEnthOut = TotHfAtFeedT_Before / 0.430210432; //convert from Btu/lb to kJ/kg
          dAirQmIn = 0.0;
          dAirTRise = 0.0;
          dAirTOut = dTempKFeed;
          dAirMixQm = 0.0;
          dAirMixCp = 0.0;
          dAirMixT = dTempKFeed;
          }
        }

      //QMix.ChangeModel(&SMSteamClass);
      const double TotHfAtFeedT_After = QMix().totHf(som_ALL, dTempKFeed, QMix().Press());
      Qv.QSetF(QMix(), som_Gas, 1.0);
      Qv.SetPress(POut);
      Qv.SetTemp(RqdLiqTempUsed);

      const double Qsl = QMix().QMass(som_SL);
      if (ioLoss<0)
        {
        if (ioDrift<0)
          {
          Ql.QSetF(QMix(), som_SL, 1.0);
          Ql.SetPress(POut);
          Ql.SetTemp(RqdLiqTempUsed);
          }
        else
          {
          SpConduit & Qdrift=*IOConduit(ioDrift);
          const double f = dDriftLossQm/GTZ(Qsl);
          Ql.QSetF(QMix(), som_SL, 1.0-f);
          Ql.SetPress(POut);
          Ql.SetTemp(RqdLiqTempUsed);
          Qdrift.QCopy(QMix());
          Qdrift.QSetF(QMix(), som_SL, f);
          Qdrift.SetPress(POut);
          Qdrift.SetTemp(RqdLiqTempUsed);
          }
        }
      else
        {
        SpConduit & Qloss=*IOConduit(ioLoss);
        const double f = dLossQm/GTZ(Qsl);
        Ql.QSetF(QMix(), som_SL, 1.0-f);
        Ql.SetPress(POut);
        Ql.SetTemp(RqdLiqTempUsed);
        if (ioDrift<0)
          {
          Qloss.QCopy(QMix());
          Qloss.QSetF(QMix(), som_SL, f);
          Qloss.SetPress(POut);
          Qloss.SetTemp(RqdLiqTempUsed);
          }
        else
          {
          const double fd = dDriftLossQm/GTZ(Qsl);
          const double fl = f - fd;
          SpConduit & Qdrift=*IOConduit(ioDrift);
          Qdrift.QCopy(QMix());
          Qdrift.QSetF(QMix(), som_SL, fd);
          Qdrift.SetPress(POut);
          Qdrift.SetTemp(RqdLiqTempUsed);
          Qloss.QCopy(QMix());
          Qloss.QSetF(QMix(), som_SL, fl);
          Qloss.SetPress(POut);
          Qloss.SetTemp(RqdLiqTempUsed);
          }
        }

      //results...
      dTotalLossQm = dLossQm+dEvapLossQm;
      dHeatFlow = TotHfAtFeedT_After - TotHfAtFeedT_Before; //what exactly is this???
      dFinalP = Ql.Press();
      dFinalT = Ql.Temp();
      dTempDrop = T1 - dFinalT;
      SetCI(1, HasFlw && RqdLiqTemp>T1);
      SetCI(2, HasFlw && RqdLiqTempUsed>RqdLiqTemp);
      break;
      }
    default:
      MN_Surge::EvalProducts(NEI);
    }
  }