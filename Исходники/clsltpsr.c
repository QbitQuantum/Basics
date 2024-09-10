/****************************************************************
  NAME         : ParseSimpleFacet
  DESCRIPTION  : Parses the following facets for a slot:
                   access, source, propagation, storage,
                   pattern-match, visibility and override-message
  INPUTS       : 1) The input logical name
                 2) The bitmap indicating which facets have
                    already been parsed
                 3) The name of the facet
                 4) The bit to test/set in arg #2 for this facet
                 5) The facet value string which indicates the
                    facet should be false
                 6) The facet value string which indicates the
                    facet should be true
                 7) An alternate value string for use when the
                    first two don't match (can be NULL)
                 7) An alternate value string for use when the
                    first three don't match (can be NULL)
                    (will be an SF_VARIABLE type)
                 9) A buffer to hold the facet value symbol
                    (can be NULL - only set if args #5 and #6
                     are both NULL)
  RETURNS      : -1 on errors
                  0 if first value string matched
                  1 if second value string matched
                  2 if alternate value string matched
                  3 if variable value string matched
                  4 if facet value buffer was set
  SIDE EFFECTS : Messages printed on errors
                 Bitmap marked indicating facet was parsed
                 Facet value symbol buffer set, if appropriate
  NOTES        : None
 *****************************************************************/
static int ParseSimpleFacet(
  Environment *theEnv,
  const char *readSource,
  SlotDescriptor *slot,
  char *specbits,
  const char *facetName,
  int testBit,
  const char *clearRelation,
  const char *setRelation,
  const char *alternateRelation,
  const char *varRelation,
  CLIPSLexeme **facetSymbolicValue)
  {
   int rtnCode;

   if (TestBitMap(specbits,testBit))
     {
      PrintErrorID(theEnv,"CLSLTPSR",2,false);
      WriteString(theEnv,STDERR,"The '");
      WriteString(theEnv,STDERR,facetName);
      WriteString(theEnv,STDERR,"' facet for slot '");
      WriteString(theEnv,STDERR,slot->slotName->name->contents);
      WriteString(theEnv,STDERR,"' is already specified.\n");
      return -1;
     }
   SetBitMap(specbits,testBit);
   SavePPBuffer(theEnv," ");
   GetToken(theEnv,readSource,&DefclassData(theEnv)->ObjectParseToken);

   /* ===============================
      Check for the variable relation
      =============================== */
   if (DefclassData(theEnv)->ObjectParseToken.tknType == SF_VARIABLE_TOKEN)
     {
      if ((varRelation == NULL) ? false :
          (strcmp(DefclassData(theEnv)->ObjectParseToken.lexemeValue->contents,varRelation) == 0))
        rtnCode = 3;
      else
        goto ParseSimpleFacetError;
     }
   else
     {
      if (DefclassData(theEnv)->ObjectParseToken.tknType != SYMBOL_TOKEN)
        goto ParseSimpleFacetError;

      /* ===================================================
         If the facet value buffer is non-NULL
         simply get the value and do not check any relations
         =================================================== */
      if (facetSymbolicValue == NULL)
        {
         if (strcmp(DefclassData(theEnv)->ObjectParseToken.lexemeValue->contents,clearRelation) == 0)
           rtnCode = 0;
         else if (strcmp(DefclassData(theEnv)->ObjectParseToken.lexemeValue->contents,setRelation) == 0)
           rtnCode = 1;
         else if ((alternateRelation == NULL) ? false :
                  (strcmp(DefclassData(theEnv)->ObjectParseToken.lexemeValue->contents,alternateRelation) == 0))
           rtnCode = 2;
         else
           goto ParseSimpleFacetError;
        }
      else
        {
         rtnCode = 4;
         *facetSymbolicValue = DefclassData(theEnv)->ObjectParseToken.lexemeValue;
        }
     }
   GetToken(theEnv,readSource,&DefclassData(theEnv)->ObjectParseToken);
   if (DefclassData(theEnv)->ObjectParseToken.tknType != RIGHT_PARENTHESIS_TOKEN)
     goto ParseSimpleFacetError;
   return(rtnCode);

ParseSimpleFacetError:
   SyntaxErrorMessage(theEnv,"slot facet");
   return(-1);
  }