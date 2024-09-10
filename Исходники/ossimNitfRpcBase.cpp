ossimRefPtr<ossimProperty> ossimNitfRpcBase::getProperty(const ossimString& name)const
{
   ossimProperty* result = 0;
   if(name == ERR_BIAS_KW)
   {
      result = new ossimStringProperty(name, theErrorBias);
   }
   else if(name == ERR_RAND_KW)
   {
      result = new ossimStringProperty(name, theErrRand);
   }
   else if(name == LINE_OFF_KW)
   {
      result = new ossimStringProperty(name, theLineOffset);
   }
   else if(name == SAMP_OFF_KW)
   {
      result = new ossimStringProperty(name, theSampleOffset);
   }
   else if(name == LAT_OFF_KW)
   {
      result = new ossimStringProperty(name, theGeodeticLatOffset);
   }
   else if(name == LONG_OFF_KW)
   {
      result = new ossimStringProperty(name, theGeodeticLonOffset);
   }
   else if(name == HEIGHT_OFF_KW)
   {
      result = new ossimStringProperty(name, theGeodeticHeightOffset);
   }
   else if(name == LINE_SCALE_KW)
   {
      result = new ossimStringProperty(name, theLineScale);
   }
   else if(name == SAMP_SCALE_KW)
   {
      result = new ossimStringProperty(name,theSampleScale );
   }
   else if(name == LAT_SCALE_KW)
   {
      result = new ossimStringProperty(name, theGeodeticLatScale);
   }
   else if(name == LONG_SCALE_KW)
   {
      result = new ossimStringProperty(name, theGeodeticLonScale);
   }
   else if(name == HEIGHT_SCALE_KW)
   {
      result = new ossimStringProperty(name, theGeodeticHeightScale);
   }
   else if(name.contains(LINE_NUM_COEFF_KW))
   {
      ossim_uint32 idx = 0;

         idx = ossimString(name.begin()+LINE_NUM_COEFF_KW.length(),
                           name.end()).toUInt32();
      --idx;

      if(idx < theLineNumeratorCoefficient.size())
      {
         result = new ossimStringProperty(name, theLineNumeratorCoefficient[idx]);
      }
   }
   else if(name.contains(LINE_DEN_COEFF_KW))
   {
      ossim_uint32 idx = 0;

      idx = ossimString(name.begin()+LINE_DEN_COEFF_KW.length(),
                        name.end()).toUInt32();
      --idx;

      if(idx < theLineDenominatorCoefficient.size())
      {
         result = new ossimStringProperty(name, theLineDenominatorCoefficient[idx]);
      }
   }
   else if(name.contains(SAMP_NUM_COEFF_KW))
   {
      ossim_uint32 idx = 0;

      idx = ossimString(name.begin()+SAMP_NUM_COEFF_KW.length(),
                        name.end()).toUInt32(); 
      --idx;

      if(idx < theSampleNumeratorCoefficient.size())
      {
         result = new ossimStringProperty(name, theSampleNumeratorCoefficient[idx]);
      }
   }
   else if(name.contains(SAMP_DEN_COEFF_KW))
   {
      ossim_uint32 idx = 0;

      idx = ossimString(name.begin()+SAMP_DEN_COEFF_KW.length(),
                        name.end()).toUInt32();
      --idx;

      if(idx < theSampleDenominatorCoefficient.size())
      {
         result = new ossimStringProperty(name, theSampleDenominatorCoefficient[idx]);
      }
   }

   return result;
}