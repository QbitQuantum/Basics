void CmpSeabaseDDL::createSeabaseRoutine(
				      StmtDDLCreateRoutine * createRoutineNode,
				      NAString &currCatName, 
                                      NAString &currSchName)
{
  Lng32 retcode = 0;
 
  ComObjectName routineName(createRoutineNode->getRoutineName());
  ComAnsiNamePart currCatAnsiName(currCatName);
  ComAnsiNamePart currSchAnsiName(currSchName);
  routineName.applyDefaults(currCatAnsiName, currSchAnsiName);
  const NAString catalogNamePart = 
    routineName.getCatalogNamePartAsAnsiString();
  const NAString schemaNamePart = 
    routineName.getSchemaNamePartAsAnsiString(TRUE);
  const NAString objectNamePart = 
    routineName.getObjectNamePartAsAnsiString(TRUE);
  const NAString extRoutineName = routineName.getExternalName(TRUE);
  ComRoutineType rType          = createRoutineNode->getRoutineType();
  ComRoutineLanguage language   = createRoutineNode->getLanguageType();
  ComRoutineParamStyle ddlStyle = createRoutineNode->getParamStyle();
  ComRoutineParamStyle style    = ddlStyle;
  NABoolean isJava              = (language == COM_LANGUAGE_JAVA);

  // Check to see if user has the authority to create the routine
  ExeCliInterface cliInterface(STMTHEAP, NULL, NULL, 
    CmpCommon::context()->sqlSession()->getParentQid());
  Int32 objectOwnerID = SUPER_USER;
  Int32 schemaOwnerID = SUPER_USER;
  ComSchemaClass schemaClass;

  retcode = verifyDDLCreateOperationAuthorized(&cliInterface,
                                               SQLOperation::CREATE_ROUTINE,
                                               catalogNamePart,
                                               schemaNamePart,
                                               schemaClass,
                                               objectOwnerID,
                                               schemaOwnerID);
  if (retcode != 0)
  {
     handleDDLCreateAuthorizationError(retcode,catalogNamePart,schemaNamePart);
     return;
  }
  
  ExpHbaseInterface * ehi = NULL;

  ehi = allocEHI();
  if (ehi == NULL)
    {
      processReturn();
      return;
    }
  
  retcode = existsInSeabaseMDTable(&cliInterface, 
				   catalogNamePart, schemaNamePart, 
                                   objectNamePart, COM_USER_DEFINED_ROUTINE_OBJECT, 
                                   TRUE, FALSE);
  if (retcode < 0)
    {
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  if (retcode == 1) // already exists
    {
      *CmpCommon::diags() << DgSqlCode(-1390)
			  << DgString0(extRoutineName);
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  
  ComObjectName libName(createRoutineNode->
                        getLibraryName().getQualifiedNameAsAnsiString());
  libName.applyDefaults(currCatAnsiName, currSchAnsiName);	
  NAString libCatNamePart = libName.getCatalogNamePartAsAnsiString();
  NAString libSchNamePart = libName.getSchemaNamePartAsAnsiString(TRUE);
  NAString libObjNamePart = libName.getObjectNamePartAsAnsiString(TRUE);
  const NAString extLibraryName = libName.getExternalName(TRUE);
  char externalPath[512] ;
  Lng32 cliRC = 0;
	
  // this call needs to change
  Int64 libUID = getObjectUID(&cliInterface, 
                              libCatNamePart, 
                              libSchNamePart, 
                              libObjNamePart,
                              COM_LIBRARY_OBJECT_LIT);

  if (libUID < 0)
    {
      processReturn();    
      return;
    }

  if (libUID == 0) // does not exist
    {
      *CmpCommon::diags() << DgSqlCode(-1361)
			  << DgString0(extLibraryName);
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  // read the library path name from the LIBRARIES metadata table

  char * buf = new(STMTHEAP) char[200];
  str_sprintf(buf, "select library_filename from %s.\"%s\".%s"
              " where library_uid = %Ld for read uncommitted access",
              getSystemCatalog(), SEABASE_MD_SCHEMA, SEABASE_LIBRARIES, libUID);

  cliRC = cliInterface.fetchRowsPrologue(buf, TRUE/*no exec*/);
  if (cliRC < 0)
    {
      cliInterface.retrieveSQLDiagnostics(CmpCommon::diags());
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  cliRC = cliInterface.clearExecFetchClose(NULL, 0);
  if (cliRC < 0)
    {
      cliInterface.retrieveSQLDiagnostics(CmpCommon::diags());
      deallocEHI(ehi); 
      processReturn();
      return;
    }
  if (cliRC == 100) // did not find the row
    {
      *CmpCommon::diags() << DgSqlCode(-1231)
                          << DgString0(extRoutineName);
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  char * ptr = NULL;
  Lng32 len = 0;
  cliInterface.getPtrAndLen(1, ptr, len);
  str_cpy_all(externalPath, ptr, len);
  externalPath[len] = '\0'; 

  // determine language and parameter styles based on the library
  // type, unless already specified
  if (!createRoutineNode->isLanguageTypeSpecified())
    {
      NAString extPath(externalPath);
      size_t lastDot = extPath.last('.');
      NAString libSuffix;

      if (lastDot != NA_NPOS)
        libSuffix = extPath(lastDot,extPath.length()-lastDot);

      libSuffix.toUpper();

      if (libSuffix == ".JAR")
        {
          isJava = TRUE;
          language = COM_LANGUAGE_JAVA;
        }
      else if (libSuffix == ".SO" ||
               libSuffix == ".DLL")
        {
          // a known C/C++ library, set
          // language and parameter style below
        }
      else
        {
          // language not specified and library name
          // is inconclusive, issue an error
          *CmpCommon::diags() << DgSqlCode( -3284 )
                              << DgString0( externalPath );
          processReturn();
        }
    }

  // set parameter style and also language, if not already
  // specified, based on routine type and type of library
  if (isJava)
    {
      // library is a jar file

      if (rType == COM_PROCEDURE_TYPE)
        // Java stored procedures use the older Java style
        style = COM_STYLE_JAVA_CALL;
      else
        // Java UDFs use the newer Java object style
        style = COM_STYLE_JAVA_OBJ;
    }
  else
    {
      // assume the library is a DLL with C or C++ code
      if (rType == COM_TABLE_UDF_TYPE &&
          (language == COM_LANGUAGE_CPP ||
           !createRoutineNode->isLanguageTypeSpecified()))
        {
          // Table UDFs (TMUDFs) default to the C++ interface
          language = COM_LANGUAGE_CPP;
          style    = COM_STYLE_CPP_OBJ;
        }
      else if (rType == COM_SCALAR_UDF_TYPE &&
               (language == COM_LANGUAGE_C ||
                !createRoutineNode->isLanguageTypeSpecified()))
        {
          // scalar UDFs default to C and SQL parameter style
          language = COM_LANGUAGE_C;
          style    = COM_STYLE_SQL;
        }
      else
        {
          // some invalid combination of routine type, language and
          // library type
          *CmpCommon::diags() << DgSqlCode(-3286);
          processReturn();
          return;
        }
    } // C/C++ DLL

  if (createRoutineNode->isParamStyleSpecified() &&
      ddlStyle != style)
    {
      // An unsupported PARAMETER STYLE was specified
      *CmpCommon::diags() << DgSqlCode(-3280);
      processReturn();
      return;
    }

  NAString externalName;
  if (language == COM_LANGUAGE_JAVA &&
      style == COM_STYLE_JAVA_CALL)
    {
      // the external name is a Java method signature
      externalName = createRoutineNode->getJavaClassName();
      externalName += "." ;
      externalName += createRoutineNode->getJavaMethodName();
    }
  else
    // the external name is a C/C++ entry point or a
    // Java class name
    externalName = createRoutineNode->getExternalName();

  // Verify that current user has authority to create the routine
  // User must be DB__ROOT or have privileges
  if (isAuthorizationEnabled() && !ComUser::isRootUserID())
    {

      // For now, go get privileges directly.  If we ever cache routines, then
      // make sure privileges are stored in the cache.
      NAString privMgrMDLoc;
      CONCAT_CATSCH(privMgrMDLoc, getSystemCatalog(), SEABASE_PRIVMGR_SCHEMA);
      PrivMgrCommands privInterface(privMgrMDLoc.data(), CmpCommon::diags());
      PrivMgrUserPrivs privs;
      PrivStatus retcode = privInterface.getPrivileges(libUID, COM_LIBRARY_OBJECT, 
                                                       ComUser::getCurrentUser(), privs);
      if (retcode != STATUS_GOOD)
        {
          if (CmpCommon::diags()->getNumber(DgSqlCode::ERROR_) == 0)
            SEABASEDDL_INTERNAL_ERROR("checking routine privilege");
          processReturn();
          return;
        }

      // Requester must have USAGE privilege on the library
      NABoolean hasPriv = TRUE;
      if ( !privs.hasUsagePriv() )
        {
          *CmpCommon::diags() << DgSqlCode( -4481 )
                              << DgString0( "USAGE" )
                              << DgString1( extLibraryName.data());
          processReturn();
          return;
        }
    }

  ElemDDLParamDefArray &routineParamArray =
        createRoutineNode->getParamArray();
  Lng32 numParams = routineParamArray.entries();

  if ((createRoutineNode->getRoutineType() == COM_SCALAR_UDF_TYPE) &&
      (numParams > 32))
    {
      *CmpCommon::diags() << DgSqlCode( -1550 )
                          << DgString0( extRoutineName )
                          << DgInt0( numParams );
      deallocEHI(ehi); 
      processReturn();
      return;
    }
#define MAX_SIGNATURE_LENGTH 8193
  // Allocate buffer for generated signature
  char sigBuf[MAX_SIGNATURE_LENGTH];
  sigBuf[0] = '\0';

  if (style == COM_STYLE_JAVA_CALL) 
  {
     // validate routine for Java call based on signature
     Lng32 numJavaParam = 0;
     ComFSDataType *paramType = new ComFSDataType[numParams];
     ComUInt32     *subType   = new ComUInt32    [numParams];
     ComColumnDirection *direction = new ComColumnDirection[numParams];
     NAType *genericType;

     // Gather the param attributes for LM from the paramDefArray previously
     // populated and from the routineparamList generated from paramDefArray.

     for (CollIndex i = 0; (Int32)i < numParams; i++)
     {
       paramType[i] = (ComFSDataType)routineParamArray[i]->getParamDataType()->getFSDatatype();
       subType[i] = 0;  // default
       // Set subType for special cases detected by LM
       switch ( paramType[i] )
       {
         case COM_SIGNED_BIN16_FSDT :
         case COM_SIGNED_BIN32_FSDT :
         case COM_SIGNED_BIN64_FSDT :
         case COM_UNSIGNED_BIN16_FSDT :
         case COM_UNSIGNED_BIN32_FSDT :
         case COM_UNSIGNED_BPINT_FSDT :
         {
           genericType = routineParamArray[i]->getParamDataType() ;
           if (genericType->getTypeName() == LiteralNumeric)
             subType[i] = genericType->getPrecision();
           else
             subType[i] = 0 ;

           break;
         }

         case COM_DATETIME_FSDT :
         {
           genericType = routineParamArray[i]->getParamDataType() ;
           DatetimeType & datetimeType = (DatetimeType &) *genericType;
            if (datetimeType.getSimpleTypeName() EQU "DATE")
              subType[i] = 1 ;
            else if (datetimeType.getSimpleTypeName() EQU "TIME")
              subType[i] = 2;
            else if (datetimeType.getSimpleTypeName() EQU "TIMESTAMP")
              subType[i] = 3;
         }
       } // end switch paramType[i]

       direction[i] = (ComColumnDirection) routineParamArray[i]->getParamDirection();
     }
    
     // If the syntax specified a signature, pass that to LanguageManager.
     NAString specifiedSig( createRoutineNode->getJavaSignature() );
     char* optionalSig;
     if ( specifiedSig.length() == 0 )
       optionalSig = NULL;
     else
       optionalSig = (char *)specifiedSig.data();
     
     ComBoolean isJavaMain =
       ((str_cmp_ne(createRoutineNode->getJavaMethodName(), "main") == 0) ? TRUE : FALSE);

     LmResult createSigResult;
     LmJavaSignature *lmSignature =  new (STMTHEAP) LmJavaSignature(NULL,
                                                                    STMTHEAP);
     createSigResult = lmSignature->createSig(paramType, subType, direction,
                                              numParams, COM_UNKNOWN_FSDT, 0,
                                              createRoutineNode->getMaxResults(), optionalSig, isJavaMain, sigBuf,
                                              MAX_SIGNATURE_LENGTH,
                                              CmpCommon::diags());
     NADELETE(lmSignature, LmJavaSignature, STMTHEAP);
     delete [] paramType;
     delete [] subType;
     delete [] direction;

     // Lm returned error. Lm fills diags area, so no need to worry about diags.
     if (createSigResult == LM_ERR)
     {
       *CmpCommon::diags() << DgSqlCode(-1231)
			  << DgString0(extRoutineName);
       deallocEHI(ehi); 
       processReturn();
       return;
     }

     numJavaParam = (isJavaMain ? 1 : numParams);

     if (validateRoutine(&cliInterface, 
                         createRoutineNode->getJavaClassName(),
                         createRoutineNode->getJavaMethodName(),
                         externalPath,
                         sigBuf,
                         numJavaParam,
                         createRoutineNode->getMaxResults(),
                         optionalSig))
     {
       *CmpCommon::diags() << DgSqlCode(-1231)
                           << DgString0(extRoutineName);
       deallocEHI(ehi); 
       processReturn();
       return;
     }
  }
  else if (style == COM_STYLE_JAVA_OBJ ||
           style == COM_STYLE_CPP_OBJ)
  {
    // validate existence of the C++ or Java class in the library
    Int32 routineHandle = NullCliRoutineHandle;
    NAString externalPrefix(externalPath);
    NAString externalNameForValidation(externalName);
    NAString containerName;

    if (language == COM_LANGUAGE_C || language == COM_LANGUAGE_CPP)
      {
        // separate the actual DLL name from the prefix
        char separator = '/';
        size_t separatorPos = externalPrefix.last(separator);

        if (separatorPos != NA_NPOS)
          {
            containerName = externalPrefix(separatorPos+1,
                                           externalPrefix.length()-separatorPos-1);
            externalPrefix.remove(separatorPos,
                                  externalPrefix.length()-separatorPos);
          }
        else
          {
            // assume the entire string is a local name
            containerName = externalPrefix;
            externalPrefix = ".";
          }
      }
    else
      {
        // For Java, the way the language manager works is that the
        // external path is the fully qualified name of the jar and
        // the container is the class name (external name).  We load
        // the container (the class) by searching in the path (the
        // jar). The external name is the method name, which in this
        // case is the constructor of the class, <init>.

        // leave externalPrevix unchanged, fully qualified jar file
        containerName = externalName;
        externalNameForValidation = "<init>";
      }

    // use a CLI call to validate that the library contains the routine
    if (cliInterface.getRoutine(
             NULL, // No InvocationInfo specified in this step
             0,
             NULL,
             0,
             (Int32) language,
             (Int32) style,
             externalNameForValidation.data(),
             containerName.data(),
             externalPrefix.data(),
             extLibraryName.data(),
             &routineHandle,
             CmpCommon::diags()) != LME_ROUTINE_VALIDATED)
      {
        if (routineHandle != NullCliRoutineHandle)
          cliInterface.putRoutine(routineHandle,
                                  CmpCommon::diags());

        CMPASSERT(CmpCommon::diags()->mainSQLCODE() < 0);
        processReturn();
        return;
      }

    cliInterface.putRoutine(routineHandle,
                            CmpCommon::diags());
  }

  ComTdbVirtTableColumnInfo * colInfoArray = (ComTdbVirtTableColumnInfo*)
    new(STMTHEAP) ComTdbVirtTableColumnInfo[numParams];

  if (buildColInfoArray(&routineParamArray, colInfoArray))
    {
      processReturn();
      return;
    }

  ComTdbVirtTableTableInfo * tableInfo = new(STMTHEAP) ComTdbVirtTableTableInfo[1];
  tableInfo->tableName = NULL,
  tableInfo->createTime = 0;
  tableInfo->redefTime = 0;
  tableInfo->objUID = 0;
  tableInfo->objOwnerID = objectOwnerID;
  tableInfo->schemaOwnerID = schemaOwnerID;
  tableInfo->isAudited = 1;
  tableInfo->validDef = 1;
  tableInfo->hbaseCreateOptions = NULL;
  tableInfo->numSaltPartns = 0;
  tableInfo->rowFormat = COM_UNKNOWN_FORMAT_TYPE;
  tableInfo->objectFlags = 0;

  Int64 objUID = -1;
  if (updateSeabaseMDTable(&cliInterface, 
			   catalogNamePart, schemaNamePart, objectNamePart,
			   COM_USER_DEFINED_ROUTINE_OBJECT,
			   "N",
			   tableInfo,
			   numParams,
			   colInfoArray,
			   0, NULL,
			   0, NULL,
                           objUID))
    {
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  if (objUID == -1)
    {
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  NAString udrType;
  getRoutineTypeLit(createRoutineNode->getRoutineType(), udrType);
  NAString languageType;
  getLanguageTypeLit(language, languageType);
  NAString sqlAccess;
  getSqlAccessLit(createRoutineNode->getSqlAccess(), sqlAccess);
  NAString paramStyle;
  getParamStyleLit(style, paramStyle);
  NAString transactionAttributes;
  getTransAttributesLit(createRoutineNode->getTransactionAttributes(), transactionAttributes);
  NAString parallelism;
  getParallelismLit(createRoutineNode->getParallelism(), parallelism);
  NAString externalSecurity;
  getExternalSecurityLit(createRoutineNode->getExternalSecurity(), externalSecurity);
  NAString executionMode;
  getExecutionModeLit(createRoutineNode->getExecutionMode(), executionMode);
  

  char * query = new(STMTHEAP) char[2000+MAX_SIGNATURE_LENGTH];
  str_sprintf(query, "insert into %s.\"%s\".%s values (%Ld, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %Ld, '%s' )",
	      getSystemCatalog(), SEABASE_MD_SCHEMA, SEABASE_ROUTINES,
	      objUID,
              udrType.data(),
              languageType.data(),
              createRoutineNode->isDeterministic() ? "Y" : "N" ,
              sqlAccess.data(),
              createRoutineNode->isCallOnNull() ? "Y" : "N" ,
              createRoutineNode->isIsolate() ? "Y" : "N" ,
              paramStyle.data(),
              transactionAttributes.data(),
              createRoutineNode->getMaxResults(),
              createRoutineNode->getStateAreaSize(),
              externalName.data(),
              parallelism.data(),
              createRoutineNode->getUserVersion().data(),
              externalSecurity.data(),
              executionMode.data(),
              libUID,
              sigBuf);
  
  cliRC = cliInterface.executeImmediate(query);
  NADELETEBASIC(query, STMTHEAP);
  if (cliRC < 0)
    {
      cliInterface.retrieveSQLDiagnostics(CmpCommon::diags());
      processReturn();
      return;
    }

  char * query1 = new(STMTHEAP) char[1000];
  str_sprintf(query1, "insert into %s.\"%s\".%s values (%Ld, %Ld)",
	      getSystemCatalog(), SEABASE_MD_SCHEMA, SEABASE_LIBRARIES_USAGE,
	      libUID, objUID);
  
  cliRC = cliInterface.executeImmediate(query1);
  NADELETEBASIC(query1, STMTHEAP);
  if (cliRC < 0)
    {
      cliInterface.retrieveSQLDiagnostics(CmpCommon::diags());
      processReturn();
      return;
    }

  // hope to remove this call soon by setting the valid flag to Y sooner
  if (updateObjectValidDef(&cliInterface, 
			   catalogNamePart, schemaNamePart, objectNamePart,
			   COM_USER_DEFINED_ROUTINE_OBJECT_LIT,
			   "Y"))
    {
      deallocEHI(ehi); 
      processReturn();
      return;
    }

  processReturn();
  return;
}