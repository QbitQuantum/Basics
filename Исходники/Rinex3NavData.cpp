   // Private helper routine for constructors from OrbitEph-based Ephemerides
   void Rinex3NavData::loadFrom(const OrbitEph *oeptr)
   {
      time = oeptr->ctToc;
      sat = RinexSatID(oeptr->satID);
      satSys = string(1,sat.systemChar());
      PRNID = sat.id;

      //Toc = static_cast<GPSWeekSecond>(oeptr->ctToe).getSOW();
      af0 = oeptr->af0;
      af1 = oeptr->af1;
      af2 = oeptr->af2;

      //Toe = static_cast<GPSWeekSecond(oeptr->ctToe).getSOW();
      M0 = oeptr->M0;
      dn = oeptr->dn;
      ecc = oeptr->ecc;
      Ahalf = SQRT(oeptr->A);
      OMEGA0 = oeptr->OMEGA0;
      i0 = oeptr->i0;
      w = oeptr->w;
      OMEGAdot = oeptr->OMEGAdot;
      idot = oeptr->idot;

      Cuc = oeptr->Cuc;
      Cus = oeptr->Cus;
      Crc = oeptr->Crc;
      Crs = oeptr->Crs;
      Cic = oeptr->Cic;
      Cis = oeptr->Cis;
   }