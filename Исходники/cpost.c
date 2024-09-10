/*------------------------------------------------------------------
 * add default key words to reserved hash
 *------------------------------------------------------------------*/
void InitializeReservedHash(
   Info *info,
   char *keyList
   )
   {
   int   i;
   char *part;

   /*---------------------------------------------------------------
    * create hash table
    *---------------------------------------------------------------*/
   info->reservedHash = HashCreate(sizeof(char *),
                                  30,
                                  (HashFunc *)IdentHash,
                                  (ListCompareFunc *)IdentCompare,
                                  cPostNoMem);

   if (!info->reservedHash)
      cPostError(1,"error creating reserved word hash table");

   for (i=0; i<sizeof(ReservedTokens)/sizeof(char *); i++)
      if (!HashAdd(info->reservedHash,&(ReservedTokens[i])))
         cPostError(1,"error adding reserved word '%s' to hash table",
                    ReservedTokens[i]);

   /*---------------------------------------------------------------
    * loop through the comma separated keys ...
    *---------------------------------------------------------------*/
   part = strtok(keyList,",");
   while (part)
      {
      /*------------------------------------------------------------
       * special c++ token
       *------------------------------------------------------------*/
      if (!Stricmp("c++",part))
         {
         for (i=0; i<sizeof(CppReservedTokens)/sizeof(char *); i++)
            if (!HashAdd(info->reservedHash,&(CppReservedTokens[i])))
               cPostError(1,"error adding reserved word '%s' to hash table",
                          CppReservedTokens[i]);

         }

      /*------------------------------------------------------------
       * use Java tokens
       *------------------------------------------------------------*/
      if (!Stricmp("java",part))
         {
         /*------------------------------------------------------------
          * remove default C tokens
          *------------------------------------------------------------*/
         for (i=0; i<sizeof(ReservedTokens)/sizeof(char *); i++)
            HashDelete(info->reservedHash,&(ReservedTokens[i]));

         /*------------------------------------------------------------
          * add Java tokens
          *------------------------------------------------------------*/
         for (i=0; i<sizeof(JavaReservedTokens)/sizeof(char *); i++)
            if (!HashAdd(info->reservedHash,&(JavaReservedTokens[i])))
               cPostError(1,"error adding reserved word '%s' to hash table",
                          JavaReservedTokens[i]);

         }

      /*------------------------------------------------------------
       * file name
       *------------------------------------------------------------*/
      else if (('@' == part[0]) && (1 != strlen(part)))
         {
         TokFileInfo  tfi;
         char        *key;

         part++;

         tfi = TokFileOpen(part);

         if (!tfi)
            cPostError(0,"error opening file '%s' for reading",part);

         else
            {
            while (NULL != (part = TokFileNext(tfi)))
               {
               key = malloc(1 + strlen(part));
               if (!key)
                  cPostError(1,"out of memory!!");

               strcpy(key,part);

               if (!HashAdd(info->reservedHash,&key))
                  cPostError(0,"error adding reserved word '%s' to hash table; word ignored",
                                key);
               }
            }
         }

      /*------------------------------------------------------------
       * plain old token
       *------------------------------------------------------------*/
      else if (!HashAdd(info->reservedHash,&part))
         {
         cPostError(0,"error adding reserved word '%s' to hash table; word ignored",part);
         }

      part = strtok(NULL,",");
      }
   }