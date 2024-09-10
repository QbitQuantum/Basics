globle int CheckSyntax(
  void *theEnv,
  char *theString,
  DATA_OBJECT_PTR returnValue)
  {
   char *name;
   struct token theToken;
   struct expr *top;
   short rv;

   /*==============================*/
   /* Set the default return value */
   /* (TRUE for problems found).   */
   /*==============================*/

   SetpType(returnValue,SYMBOL);
   SetpValue(returnValue,EnvTrueSymbol(theEnv));

   /*===========================================*/
   /* Create a string source router so that the */
   /* string can be used as an input source.    */
   /*===========================================*/

   if (OpenStringSource(theEnv,"check-syntax",theString,0) == 0)
     { return(TRUE); }

   /*=================================*/
   /* Only expressions and constructs */
   /* can have their syntax checked.  */
   /*=================================*/

   GetToken(theEnv,"check-syntax",&theToken);

   if (theToken.type != LPAREN)
     {
      CloseStringSource(theEnv,"check-syntax");
      SetpValue(returnValue,EnvAddSymbol(theEnv,"MISSING-LEFT-PARENTHESIS"));
      return(TRUE);
     }

   /*========================================*/
   /* The next token should be the construct */
   /* type or function name.                 */
   /*========================================*/

   GetToken(theEnv,"check-syntax",&theToken);
   if (theToken.type != SYMBOL)
     {
      CloseStringSource(theEnv,"check-syntax");
      SetpValue(returnValue,EnvAddSymbol(theEnv,"EXPECTED-SYMBOL-AFTER-LEFT-PARENTHESIS"));
      return(TRUE);
     }

   name = ValueToString(theToken.value);

   /*==============================================*/
   /* Set up a router to capture the error output. */
   /*==============================================*/

   EnvAddRouter(theEnv,"error-capture",40,
              FindErrorCapture, PrintErrorCapture,
              NULL, NULL, NULL);

   /*================================*/
   /* Determine if it's a construct. */
   /*================================*/

   if (FindConstruct(theEnv,name))
     {
      ConstructData(theEnv)->CheckSyntaxMode = TRUE;
      rv = (short) ParseConstruct(theEnv,name,"check-syntax");
      GetToken(theEnv,"check-syntax",&theToken);
      ConstructData(theEnv)->CheckSyntaxMode = FALSE;

      if (rv)
        {
         EnvPrintRouter(theEnv,WERROR,"\nERROR:\n");
         PrintInChunks(theEnv,WERROR,GetPPBuffer(theEnv));
         EnvPrintRouter(theEnv,WERROR,"\n");
        }

      DestroyPPBuffer(theEnv);

      CloseStringSource(theEnv,"check-syntax");

      if ((rv != FALSE) || (ParseFunctionData(theEnv)->WarningString != NULL))
        {
         SetErrorCaptureValues(theEnv,returnValue);
         DeactivateErrorCapture(theEnv);
         return(TRUE);
        }

      if (theToken.type != STOP)
        {
         SetpValue(returnValue,EnvAddSymbol(theEnv,"EXTRANEOUS-INPUT-AFTER-LAST-PARENTHESIS"));
         DeactivateErrorCapture(theEnv);
         return(TRUE);
        }

      SetpType(returnValue,SYMBOL);
      SetpValue(returnValue,EnvFalseSymbol(theEnv));
      DeactivateErrorCapture(theEnv);
      return(FALSE);
     }

   /*=======================*/
   /* Parse the expression. */
   /*=======================*/

   top = Function2Parse(theEnv,"check-syntax",name);
   GetToken(theEnv,"check-syntax",&theToken);
   ClearParsedBindNames(theEnv);
   CloseStringSource(theEnv,"check-syntax");

   if (top == NULL)
     {
      SetErrorCaptureValues(theEnv,returnValue);
      DeactivateErrorCapture(theEnv);
      return(TRUE);
     }

   if (theToken.type != STOP)
     {
      SetpValue(returnValue,EnvAddSymbol(theEnv,"EXTRANEOUS-INPUT-AFTER-LAST-PARENTHESIS"));
      DeactivateErrorCapture(theEnv);
      ReturnExpression(theEnv,top);
      return(TRUE);
     }

   DeactivateErrorCapture(theEnv);

   ReturnExpression(theEnv,top);
   SetpType(returnValue,SYMBOL);
   SetpValue(returnValue,EnvFalseSymbol(theEnv));
   return(FALSE);
  }