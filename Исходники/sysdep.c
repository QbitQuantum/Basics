globle void gensystem(
  void *theEnv)
  {
   char *commandBuffer = NULL;
   int bufferPosition = 0;
   unsigned bufferMaximum = 0;
   int numa, i;
   DATA_OBJECT tempValue;
   char *theString;

   /*===========================================*/
   /* Check for the corret number of arguments. */
   /*===========================================*/

   if ((numa = EnvArgCountCheck(theEnv,"system",AT_LEAST,1)) == -1) return;

   /*============================================================*/
   /* Concatenate the arguments together to form a single string */
   /* containing the command to be sent to the operating system. */
   /*============================================================*/

   for (i = 1 ; i <= numa; i++)
     {
      EnvRtnUnknown(theEnv,i,&tempValue);
      if ((GetType(tempValue) != STRING) &&
          (GetType(tempValue) != SYMBOL))
        {
         SetHaltExecution(theEnv,TRUE);
         SetEvaluationError(theEnv,TRUE);
         ExpectedTypeError2(theEnv,"system",i);
         return;
        }

     theString = DOToString(tempValue);

     commandBuffer = AppendToString(theEnv,theString,commandBuffer,&bufferPosition,&bufferMaximum);
    }

   if (commandBuffer == NULL) return;

   /*=======================================*/
   /* Execute the operating system command. */
   /*=======================================*/

#if VAX_VMS
   if (SystemDependentData(theEnv)->PauseEnvFunction != NULL) (*SystemDependentData(theEnv)->PauseEnvFunction)(theEnv);
   VMSSystem(commandBuffer);
   putchar('\n');
   if (SystemDependentData(theEnv)->ContinueEnvFunction != NULL) (*SystemDependentData(theEnv)->ContinueEnvFunction)(theEnv,1);
   if (SystemDependentData(theEnv)->RedrawScreenFunction != NULL) (*SystemDependentData(theEnv)->RedrawScreenFunction)(theEnv);
#endif

#if   UNIX_7 || UNIX_V || IBM_MSC || IBM_TBC || IBM_ICB || IBM_ZTC || IBM_SC || IBM_MCW || IBM_GCC
   if (SystemDependentData(theEnv)->PauseEnvFunction != NULL) (*SystemDependentData(theEnv)->PauseEnvFunction)(theEnv);
   system(commandBuffer);
   if (SystemDependentData(theEnv)->ContinueEnvFunction != NULL) (*SystemDependentData(theEnv)->ContinueEnvFunction)(theEnv,1);
   if (SystemDependentData(theEnv)->RedrawScreenFunction != NULL) (*SystemDependentData(theEnv)->RedrawScreenFunction)(theEnv);
#else

#if ! VAX_VMS
   EnvPrintRouter(theEnv,WDIALOG,
            "System function not fully defined for this system.\n");
#endif

#endif

   /*==================================================*/
   /* Return the string buffer containing the command. */
   /*==================================================*/

   rm(theEnv,commandBuffer,bufferMaximum);

   return;
  }