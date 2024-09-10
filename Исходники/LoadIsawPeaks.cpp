  std::string  LoadIsawPeaks::ApplyCalibInfo(std::ifstream & in, std::string startChar,Geometry::Instrument_const_sptr instr_old, Geometry::Instrument_const_sptr instr,
      double &T0)
  {
    ParameterMap_sptr parMap1= instr_old->getParameterMap();

    ParameterMap_sptr parMap= instr->getParameterMap();


    while( in.good() && (startChar.size() <1 || startChar !="7") )
       {
         readToEndOfLine( in, true);
         startChar = getWord(in, false);
       }
     if( !(in.good()))
     {
       //g_log.error()<<"Peaks file has no time shift and L0 info"<<std::endl;
       throw std::invalid_argument("Peaks file has no time shift and L0 info");
     }
     std::string L1s= getWord(in,false);
     std::string T0s =getWord(in, false);
     if( L1s.length() < 1 || T0s.length() < 1)
     {
       g_log.error()<<"Missing L1 or Time offset"<<std::endl;
       throw std::invalid_argument("Missing L1 or Time offset");
     }
     double L1;
     try
     {
       std::istringstream iss( L1s+" "+T0s, std::istringstream::in);
       iss>>L1;
       iss>>T0;
       V3D sampPos=instr->getSample()->getPos();
       SCDCalibratePanels::FixUpSourceParameterMap(instr, L1/100, sampPos,parMap1);

     }catch(...)
     {
       g_log.error()<<"Invalid L1 or Time offset"<<std::endl;
       throw std::invalid_argument("Invalid L1 or Time offset");

     }

     readToEndOfLine( in, true);
     startChar = getWord(in , false);
     while( in.good() && (startChar.size() <1 || startChar !="5") )
            {
              readToEndOfLine( in, true);
              startChar = getWord(in, false);
            }

    if( !(in.good()))
    {
      g_log.error()<<"Peaks file has no detector panel info"<<std::endl;
      throw std::invalid_argument("Peaks file has no detector panel info");
    }


    while( startChar =="5")
    {

      std::string line;
      for( int i=0; i<16;i++)
      {
        std::string s= getWord(in, false);
        if( s.size() < 1)
        {
          g_log.error()<<"Not enough info to describe panel "<<std::endl;
          throw std::length_error("Not enough info to describe panel ");
        }
       line +=" "+s;;
      }

      readToEndOfLine(in, true);
      startChar = getWord( in, false);// blank lines ?? and # lines ignore

      std::istringstream iss( line, std::istringstream::in);
      int  bankNum,nrows,ncols;
      double width,height,depth,detD,Centx,Centy,Centz,Basex,Basey,Basez,
             Upx,Upy,Upz;
      try
      {
         iss>>bankNum>>nrows>>ncols>>width>>height>>depth>>detD
            >>Centx>>Centy>>Centz>>Basex>>Basey>>Basez
            >>Upx>>Upy>>Upz;
      }catch(...)
      {

        g_log.error()<<"incorrect type of data for panel "<<std::endl;
        throw std::length_error("incorrect type of data for panel ");
      }

      std::string SbankNum = boost::lexical_cast<std::string>(bankNum);

      std::string bankName = "bank"+SbankNum;
      boost::shared_ptr<const Geometry::IComponent> bank =instr_old->getComponentByName( bankName );

      if( !bank)
      {
        g_log.error()<<"There is no bank "<< bankName<<" in the instrument"<<std::endl;
        throw std::length_error("There is no bank "+ bankName+" in the instrument");
      }

      V3D dPos= V3D(Centx,Centy,Centz)/100.0- bank->getPos();
      V3D Base(Basex,Basey,Basez), Up(Upx,Upy,Upz);
      V3D ToSamp =Base.cross_prod(Up);
      Base.normalize();
      Up.normalize();
      ToSamp.normalize();
      Quat thisRot(Base,Up,ToSamp);
      Quat bankRot(bank->getRotation());
      bankRot.inverse();
      Quat dRot = thisRot*bankRot;

      boost::shared_ptr< const Geometry::RectangularDetector>bankR= boost::dynamic_pointer_cast
                         <const Geometry::RectangularDetector>( bank);

      double DetWScale = 1, DetHtScale = 1;
      if( bank)
      {
        DetWScale = width/bankR->xsize()/100;
        DetHtScale = height/bankR->ysize()/100;

      }
      std::vector<std::string> bankNames;
      bankNames.push_back(bankName);

      SCDCalibratePanels::FixUpBankParameterMap(bankNames,instr, dPos,
          dRot,DetWScale,DetHtScale , parMap1, false);

    }
    return startChar;
  }