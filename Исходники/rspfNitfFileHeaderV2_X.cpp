rspfRefPtr<rspfProperty> rspfNitfFileHeaderV2_X::getProperty(const rspfString& name)const
{
   rspfRefPtr<rspfProperty> property = 0;
   
   if(name == FHDR_KW)
   {
      property = new rspfStringProperty(name, rspfString(theFileTypeVersion));
   }
   else if(name == VERSION_KW)
   {
      property = new rspfStringProperty(name, rspfString(getVersion()));
   }
   else if(name == FILE_TYPE_KW)
   {
      property = new rspfStringProperty(name, "NITF");
   }
   else if(name == CLEVEL_KW)
   {
      rspfNumericProperty* numericProperty =
         new rspfNumericProperty(name,
                                  getComplexityLevel(),
                                  1,
                                  99);
      numericProperty->setNumericType(rspfNumericProperty::rspfNumericPropertyType_INT);
      property = numericProperty;
      
   }
   else if(name == STYPE_KW)
   {
      property = new rspfStringProperty(name, getSystemType().trim());
   }
   else if(name == OSTAID_KW)
   {
      property = new rspfStringProperty(name, getOriginatingStationId().trim());
   }
   else if(name == FDT_KW)
   {
      property = new rspfStringProperty(name, getDate());
   }
   else if(name == FTITLE_KW)
   {
      property = new rspfStringProperty(name, getTitle().trim());
   }
   else if(name == FSCLAS_KW)
   {
      rspfStringProperty* stringProperty =
         new rspfStringProperty(name,
                                 getSecurityClassification().trim(),
                                 false);
      
      stringProperty->addConstraint("");
      stringProperty->addConstraint("T");
      stringProperty->addConstraint("S");
      stringProperty->addConstraint("C");
      stringProperty->addConstraint("R");
      stringProperty->addConstraint("U");
      
      property = stringProperty;
   }
   else if(name == FSCODE_KW)
   {
      property = new rspfStringProperty(name,
                                         getCodeWords().trim());
   }
   else if(name == FSCTLH_KW)
   {
      property = new rspfStringProperty(name,
                                         getControlAndHandling().trim());
   }
   else if(name == FSREL_KW)
   {
      property = new rspfStringProperty(name,
                                         getReleasingInstructions().trim());
   }
   else if(name == FSCAUT_KW)
   {
      property = new rspfStringProperty(name,
                                         getClassificationAuthority().trim());
   }
   else if(name == FSCTLN_KW)
   {
      property = new rspfStringProperty(name,
                                         getSecurityControlNumber().trim());
      
   }
   else if(name == FSCOP_KW)
   {
      property = new rspfStringProperty(name,
                                         getCopyNumber().trim());
   }
   else if(name == FSCPYS_KW)
   {
      property = new rspfStringProperty(name,
                                         getNumberOfCopies().trim());
   }
   else if(name == ENCRYP_KW)
   {
      property = new rspfStringProperty(name,
                                         getEncryption().trim(),
                                         false);
   }
   else
   {
      property = rspfNitfFileHeader::getProperty(name).get();
   }
   
   return property;
}