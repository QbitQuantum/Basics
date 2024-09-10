BOOLEAN Deletion_Parameters(LIST Tokens, pDeletionStruct pDeletionParameters, pSTRING pCommandLine)
{
  Token    CurrentToken;         /* Used to hold the token being examined. */
  CARDINAL Error = 0;            /* Used to hold the error return code from LIST operations. */
  BOOLEAN  ReturnValue = FALSE;  /* Used to hold the function return value. */
  pSTRING   pDriveName = NULL;
  pSTRING   pPartitionName = NULL;
  pSTRING   pDriveNumber = NULL;
  pSTRING   pVolumeName = NULL;
  unsigned int TokenPosition;


  /* Get the current token so that we can examine it. */
  GetToken(Tokens,sizeof(Token),&CurrentToken,&TokenPosition,&Error);
  if ( Error )
  {
     /* Report any errors accessing the token list as an internal error! */
     ReportError(Internal_Error);
     return ReturnValue;
  } /* endif */

  /* The next token must be the keyword ALL, PARTITION, or VOLUME */
  switch (CurrentToken.TokenType) {
  case All_CLI:
     pDeletionParameters->NameType = NoNameType;
     pDeletionParameters->DeletionOption = Deletion_None;
     /* All found, advance to next token */
     NextToken(Tokens,&Error);
     SkipOptionalWhitespace(Tokens);

     /* The token following the ALL keyword must be a comma */
     if ( IsComma(Tokens) ) {
        SkipOptionalWhitespace(Tokens);
        GetToken(Tokens,sizeof(Token),&CurrentToken,&TokenPosition,&Error);
        if ( Error) {
           /* Report any errors accessing the token list as an internal error! */
           ReportError(Internal_Error);
           return ReturnValue;
        } /* endif */

        switch (CurrentToken.TokenType) {
        case Compatibility:
           pDeletionParameters->DeletionOption = Deletion_All_Compatibility;
           NextToken(Tokens,&Error);
           ReturnValue = TRUE;
           break;
        case Logical:
           pDeletionParameters->DeletionOption = Deletion_All_Logical;
           NextToken(Tokens,&Error);
           ReturnValue = TRUE;
           break;
        case LVM:
           pDeletionParameters->DeletionOption = Deletion_All_LVM;
           NextToken(Tokens,&Error);
           ReturnValue = TRUE;
           break;
        case Primary:
           pDeletionParameters->DeletionOption = Deletion_All_Primary;
           NextToken(Tokens,&Error);
           ReturnValue = TRUE;
           break;
        case Unused:
           pDeletionParameters->DeletionOption = Deletion_All_Unused;
           NextToken(Tokens,&Error);
           ReturnValue = TRUE;
           break;
        case Volumes:
           pDeletionParameters->DeletionOption = Deletion_All_Volumes;
           NextToken(Tokens,&Error);
           ReturnValue = TRUE;
           break;
        case Eof:
        case SemiColon:
           ReportParseError(Expected_Deletion_Suboption, Tokens, pCommandLine);
           break;
        default:
           ReportParseError(Expected_Deletion_Suboption, Tokens, pCommandLine);
        } /* endswitch */
     } else {
        ReportParseError(Expected_Comma, Tokens, pCommandLine);
     } /* endif */
     break;
  case Partition:
     pDeletionParameters->DeletionOption = Deletion_Partition;
     /* Partition found, advance to next token */
     NextToken(Tokens,&Error);
     SkipOptionalWhitespace(Tokens);

     /* The token following the PARTITION keyword must be a comma */
     if ( IsComma(Tokens) ) {
        SkipOptionalWhitespace(Tokens);
        GetToken(Tokens,sizeof(Token),&CurrentToken,&TokenPosition,&Error);
        if ( Error) {
           /* Report any errors accessing the token list as an internal error! */
           ReportError(Internal_Error);
           return ReturnValue;
        } /* endif */

        /* The token following PARTITION must be a drive number or drive name */
        /* If it is a drive number */
        if ( Drive_Number(Tokens, &pDriveNumber) ) {
           pDeletionParameters->NameType = DriveNumberType;
           pDeletionParameters->pDrive = pDriveNumber;
        } else {
           /* If it is a drive name */
           if ( Drive_Name(Tokens, Comma, &pDriveName) ) {
              pDeletionParameters->NameType = DriveNameType;
              pDeletionParameters->pDrive = pDriveName;
           } else {
              ReportParseError(Expected_Drive_Number_or_Name, Tokens, pCommandLine);
              return ReturnValue;
           } /* endif */
        } /* endif */

        SkipOptionalWhitespace(Tokens);
        /* The next token is a comma, the one following it must be a parition name */
        if ( IsComma(Tokens) ) {
           SkipOptionalWhitespace(Tokens);
           GetToken(Tokens,sizeof(Token),&CurrentToken,&TokenPosition,&Error);
           if ( Error ) {
              /* Report any errors accessing the token list as an internal error! */
              ReportError(Internal_Error);
              return ReturnValue;
           } /* endif */

           pPartitionName = NULL;
           /* The next tokens, up to the next semicolon, must be a Partition name. */
           if ( Partition_Name(Tokens, SemiColon, &pPartitionName) ) {
              pDeletionParameters->pPartitionName = pPartitionName;
              ReturnValue = TRUE;
           } else {
             ReportParseError(Expected_Partition_Name, Tokens, pCommandLine);
           } /* endif */
        } else {
           /* Since the next token was not a comma, assume that the optional */
           /* partition name was not specified. */
           /* When the partition name is not specified, the parser indicates */
           /* that all paritions on the specified drive are to be deleted. */
           pDeletionParameters->DeletionOption = Deletion_Partitions;
           ReturnValue = TRUE;
        } /* endif */
     } else {
        ReportParseError(Expected_Comma, Tokens, pCommandLine);
     } /* endif */
     break;
  case Volume:
     pDeletionParameters->DeletionOption = Deletion_Volume;
     /* Volume found, advance to next token */
     NextToken(Tokens,&Error);
     SkipOptionalWhitespace(Tokens);
     /* The next non-whitespace token must be a comma */
     if ( IsComma(Tokens) ) {
        SkipOptionalWhitespace(Tokens);
        GetToken(Tokens,sizeof(Token),&CurrentToken,&TokenPosition,&Error);
        if ( Error ) {
           ReportError(Internal_Error);
           return ReturnValue;
        } /* endif */

        pVolumeName = NULL;
        /* The next tokens, up to the next semicolon, must be a volume name. */
        if ( Volume_Name(Tokens, SemiColon, &pVolumeName) ) {
           pDeletionParameters->pVolumeName = pVolumeName;
           ReturnValue = TRUE;
        } else {
          ReportParseError(Expected_Volume_Name, Tokens, pCommandLine);
        } /* endif */
     } else {
       ReportParseError(Expected_Comma, Tokens, pCommandLine);
     } /* endif */
     break;
  default:
     ReportParseError(Expected_Deletion_Option, Tokens, pCommandLine);
     break;
  } /* endswitch */

  /* Report any errors accessing the token list as an internal error! */
  if ( Error )
    ReportError(Internal_Error);

  return ReturnValue;

}