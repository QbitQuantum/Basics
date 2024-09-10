void KVGeoNavigator::ExtractDetectorNameFromPath(KVString& detname)
{
   // We analyse the current path in order to construct the full (unique) name
   // of the detector, i.e. if the current path is
   //
   // /TOP_1/STRUCT_BLOCK_2/CHIO_WALL_1/DET_CHIO_2/WINDOW_1
   //
   // then the default name of the detector will be "BLOCK_2_CHIO_2"
   // (see below to override this)
   //
   // This method also fills the fCurrentStructures array with elements
   // deduced from the path, e.g. if the path is
   //
   // /TOP_1/STRUCT_BLOCK_2/STRUCT_QUARTET_1/DET_SI1-T1
   //
   // then by default
   //  fCurrentStructures[0] = KVGeoStrucElement(name = "BLOCK_2", type = "BLOCK", number = 2)
   //  fCurrentStructures[1] = KVGeoStrucElement(name = "QUARTET_1", type = "QUARTET", number = 1)
   //
   // and the default name of the detector will be "BLOCK_2_QUARTET_1_SI1-T1"
   //
   // STRUCTURE & DETECTOR NAME FORMATTING
   // ====================================
   //    -- STRUCTURES --
   // The default names for structures are taken from the node name by stripping off
   // the "STRUCT_" prefix. It is assumed that the remaining string is of the form
   //    "[structure type]_[structure number]"
   // (the structure number is always taken after the last occurence of '_' in the
   // node name). This is the name that will be used by default for the structure.
   // However, this format can be change by calling method
   //    SetStructureNameFormat("[structure type]", "[format]")
   // where format can contain any of the following tokens:
   //    $type$         - will be replaced by the structure type name
   //    $type%[fmt]$   - will be replaced by the structure type name using given format
   //    $number$       - will be replaced by the structure number
   //    $number%[fmt]$ - will be replaced by the structure number using given format
   //
   // Example: to change the name of the block in the previous example to "B-02",
   //   SetStructureNameFormat("BLOCK", "$type%.1s$-$number%02d$")
   //
   //    -- DETECTORS --
   // The default base names for detectors are taken from the node name by stripping off
   // the "DET_" prefix. In order to ensure that all detectors have unique names,
   // by default we prefix the names of the parent structures to the basename in
   // order to generate the full name of the detector:
   //    [struc1-name]_[struc2-name]_..._[detector-basename]
   // However, this format can be changed by calling method
   //    SetDetectorNameFormat("[format]")
   // where format can contain any of the following tokens:
   //    $det:name$             - will be replaced by the detector basename
   //    $struc:[type]:name$    - will be replaced by the name of the parent structure of given type
   //    $struc:[type]:type$    - will be replaced by the type of the parent structure of given type
   //    $struc:[type]:number$  - will be replaced by the number of the parent structure of given type
   // plus additional formatting information as for SetStructureNameFormat (see above).
   //
   // Example: to change the name of the "SI1-T1" detector in the previous example to
   //  "SI1-T1-Q1-B2":
   //   SetDetectorNameFormat("$det:name$-Q$struc:QUARTET:number$-B$struc:BLOCK:number$")
   // Or if you also change the format of the structure names:
   //   SetStructureNameFormat("BLOCK", "$type%.1s$$number$")
   //   SetStructureNameFormat("QUARTET", "$type%.1s$$number$")
   //   SetDetectorNameFormat("$det:name$-$struc:QUARTET:name$-$struc:BLOCK:name$")


   KVString path = GetCurrentPath();
   path.Begin("/");
   detname = "";
   fCurrentStructures.Clear("C");
   fCurStrucNumber = 0;
   while (!path.End()) {
      KVString elem = path.Next();
      if (elem.BeginsWith("STRUCT_")) {
         // structure element. strip off "STRUCT_" and extract type and number of structure.
         KVString struc_name(elem(7, elem.Length() - 7));
         KVGeoStrucElement* gel = (KVGeoStrucElement*)fCurrentStructures.ConstructedAt(fCurStrucNumber++);
         Ssiz_t last_ = struc_name.Last('_'); // find last '_' in structure name
         TString type = struc_name(0, last_);
         TString nums = struc_name(last_ + 1, struc_name.Length() - last_ - 1);
         Int_t number = nums.Atoi();
         KVString name;
         FormatStructureName(type, number, name);
         gel->SetNameTitle(name, type);
         gel->SetNumber(number);
      } else if (elem.BeginsWith("DET_")) {
         // detector name. strip off "DET_" and use rest as basename
         KVString basename(elem(4, elem.Length() - 4));
         FormatDetectorName(basename, detname);
      }
   }
}