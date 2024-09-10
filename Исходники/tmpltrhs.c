static struct templateSlot *ParseSlotLabel(
  void *theEnv,
  EXEC_STATUS,
  char *inputSource,
  struct token *tempToken,
  struct deftemplate *theDeftemplate,
  int *error,
  int endType)
  {
   struct templateSlot *slotPtr;
   short position;

   /*========================*/
   /* Initialize error flag. */
   /*========================*/

   *error = FALSE;

   /*============================================*/
   /* If token is a right parenthesis, then fact */
   /* template definition is complete.           */
   /*============================================*/

   GetToken(theEnv,execStatus,inputSource,tempToken);
   if (tempToken->type == endType)
     { return(NULL); }

   /*=======================================*/
   /* Put a space between the template name */
   /* and the first slot definition.        */
   /*=======================================*/

   PPBackup(theEnv,execStatus);
   SavePPBuffer(theEnv,execStatus," ");
   SavePPBuffer(theEnv,execStatus,tempToken->printForm);

   /*=======================================================*/
   /* Slot definition begins with opening left parenthesis. */
   /*=======================================================*/

   if (tempToken->type != LPAREN)
     {
      SyntaxErrorMessage(theEnv,execStatus,"deftemplate pattern");
      *error = TRUE;
      return(NULL);
     }

   /*=============================*/
   /* Slot name must be a symbol. */
   /*=============================*/

   GetToken(theEnv,execStatus,inputSource,tempToken);
   if (tempToken->type != SYMBOL)
     {
      SyntaxErrorMessage(theEnv,execStatus,"deftemplate pattern");
      *error = TRUE;
      return(NULL);
     }

   /*======================================================*/
   /* Check that the slot name is valid for this template. */
   /*======================================================*/

   if ((slotPtr = FindSlot(theDeftemplate,(SYMBOL_HN *) tempToken->value,&position)) == NULL)
     {
      InvalidDeftemplateSlotMessage(theEnv,execStatus,ValueToString(tempToken->value),
                                    ValueToString(theDeftemplate->header.name),TRUE);
      *error = TRUE;
      return(NULL);
     }

   /*====================================*/
   /* Return a pointer to the slot name. */
   /*====================================*/

   return(slotPtr);
  }