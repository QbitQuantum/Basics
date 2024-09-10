//*****************************************************************************
//  METHOD: ossimDblGrid::load()
//  
//  Loads the grid from the stream in compact ASCII format (not necessarily
//  human readable).
//  
//*****************************************************************************
bool ossimDblGrid::load(istream& is)
{
   static const char MODULE[] = "ossimDblGrid::load()";
   if (traceExec())  ossimNotify(ossimNotifyLevel_DEBUG) << MODULE << " entering...\n";

   char strbuf[128];

   //***
   // Read magic number tag to insure it is an ossimDblGrid record:
   //***
   is >> strbuf;
   if (std::strncmp(strbuf, MAGIC_NUMBER.c_str(), MAGIC_NUMBER.length()))
   {
      ossimNotify(ossimNotifyLevel_FATAL) << MODULE << "Error reading OSSIM_DBL_GRID magic number from stream. "
         << "Aborting...\n";
      return false;
   }
   is.getline(strbuf, 128, '\n');
   theSize           = ossimDpt(0,0);
   theOrigin         = ossimDpt(0,0);
   theSpacing        = ossimDpt(0,0);
   theMinValue       = OSSIM_DEFAULT_MAX_PIX_DOUBLE;
   theMaxValue       =  OSSIM_DEFAULT_MIN_PIX_DOUBLE;
  // theNullValue      = theNullValue;
   theMeanIsComputed = false;


   //***
   // Read the grid size, origin, and spacing:
   //***
   ossimIpt size;
   ossimDpt origin, spacing;
   double null_value;
   is >> size.x 
      >> size.y 
      >> origin.u 
      >> origin.v 
      >> spacing.u
      >> spacing.v
      >> null_value;

   initialize(size, origin, spacing, null_value);

   //***
   // Loop to read grid points:
   //***
   int max_index = theSize.x*theSize.y;
   for (int i=0; i<max_index; i++)
   {
      is >> theGridData[i];
   }

   if (traceExec())  ossimNotify(ossimNotifyLevel_DEBUG) << MODULE << " returning...\n";

   return true;
}