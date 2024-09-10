VError VRIAServerSolution::_Open( VSolution* inDesignSolution, VRIAServerSolutionOpeningParameters *inOpeningParameters)
{
	if (fState.opened)
		return VE_OK;
	
	VError err = VE_OK;

	if (!testAssert(fDesignSolution == NULL))
		err = VE_UNKNOWN_ERROR;

	if (err == VE_OK && inDesignSolution == NULL)
		err = ThrowError( VE_RIA_INVALID_DESIGN_SOLUTION);

	if (err == VE_OK)
	{
		fDesignSolution = inDesignSolution;
		fDesignSolution->GetName( fName);

		CopyRefCountable( &fOpeningParameters, inOpeningParameters);

		if (fOpeningParameters == NULL)
		{
			fOpeningParameters = new VRIAServerSolutionOpeningParameters();
			if (fOpeningParameters == NULL)
				err = ThrowError( VE_MEMORY_FULL);
		}

		if (err == VE_OK)
			fState.inMaintenance = fOpeningParameters->GetOpeningMode() == eSOM_FOR_MAINTENANCE;

		if (err == VE_OK && !fState.inMaintenance)
		{
			VSize		nNameLength = fName. GetLength ( ) * 2 + 1;
			char*		szchName = new char [ nNameLength ];
			fName. ToCString ( szchName, nNameLength );
			fprintf ( stdout, "Publishing solution \"%s\"\n", szchName );
			delete [ ] szchName;
		}

		if (err == VE_OK && !fState.inMaintenance)
		{
			const VFolder *			vfRoot = RetainFolder ( );
			if ( vfRoot != 0 )
			{
				VJSGlobalContext::SetSourcesRoot ( *vfRoot );
				vfRoot-> Release ( );
				VJSGlobalContext::AllowDebuggerLaunch ( );
			}
		}

		fLoggerID = L"com.wakanda-software." + fName;

		if (err == VE_OK && !fState.inMaintenance)
		{
			// Create a messages logger
			VFolder *logFolder = RetainLogFolder( true);
			if (logFolder != NULL)
			{
				fLogger = new VLog4jMsgFileLogger( *logFolder,  fName + L"_log");
				if (fLogger == NULL)
				{
					err = ThrowError( VE_MEMORY_FULL);
				}
				else
				{
					VRIAServerApplication::Get()->SetLogger( fLogger);
					fLogger->Start();
				}

				logFolder->Release();
			}
			else
			{
				err = ThrowError( VE_RIA_LOG_FOLDER_NOT_FOUND);
			}
		}

		StUseLogger logger;

		if (err == VE_OK && !fState.inMaintenance)
		{
			// Create a log file reader
			fLogReader = new VLog4jMsgFileReader();
			if (fLogReader == NULL)
				err = ThrowError( VE_MEMORY_FULL);
			else
				fLogger->AttachReader( fLogReader);
		}

		if (err == VE_OK || fState.inMaintenance)
		{
			StErrorContextInstaller errContext;
			VMicrosecondsCounter usCounter;
			
			usCounter.Start();

			logger.Log( fLoggerID, eL4JML_Information, L"Opening the solution");

			if (err == VE_OK && !fState.inMaintenance)
			{
				fJSRuntimeDelegate = new VRIAServerSolutionJSRuntimeDelegate( this);
				if (fJSRuntimeDelegate == NULL)
					err = ThrowError( VE_MEMORY_FULL);
			}

			if (err == VE_OK && !fState.inMaintenance)
			{
				fJSContextPool = VRIAServerApplication::Get()->GetJSContextMgr()->CreateJSContextPool( err, this);
			}
	
			if (err == VE_OK || fState.inMaintenance)
			{
				// Load all available settings files
				err = _LoadFileSettings();
				if (err != VE_OK)
					err = ThrowError( VE_RIA_CANNOT_LOAD_SETTINGS_FILES);
			}

			if  (err == VE_OK || fState.inMaintenance)
			{
				// Load the database settings
				err = _LoadDatabaseSettings();
				if (err != VE_OK)
					err = ThrowError( VE_RIA_CANNOT_LOAD_DATABASE_SETTINGS);
			}

			if (err == VE_OK || fState.inMaintenance)
			{
				// Load users and groups directory
				fUAGDirectory = _OpenUAGDirectory( err);
				if (err != VE_OK)
					err = ThrowError( VE_RIA_CANNOT_LOAD_UAG_DIRECTORY);
			}

			if (err == VE_OK || fState.inMaintenance)
			{
				// Build the ServerAdmin project file path
				VFilePath serverAdminProjectPath;
				VFolder *folder = VRIAServerApplication::Get()->RetainApplicationResourcesFolder();
				if (folder != NULL)
				{
					folder->GetPath( serverAdminProjectPath);
					serverAdminProjectPath.ToSubFolder( L"Default Solution");
					serverAdminProjectPath.ToSubFolder( L"Admin");	// sc 18/02/2011 "ServerAdmin" become "Admin"
					serverAdminProjectPath.SetFileName( L"ServerAdmin", false);
					serverAdminProjectPath.SetExtension( RIAFileKind::kProjectFileExtension);
				}
				ReleaseRefCountable( &folder);

				// Opening the applications
				if (fApplicationsMutex.Lock())
				{
					// Note: the ServerAdmin project may be the project of the default solution
					// or the ServerAdmin project added to a solution which has none admin project.
					bool hasAdmin = false;
					VProject *serverAdminProject = fDesignSolution->GetProjectFromFilePathOfProjectFile( serverAdminProjectPath);

					bool ignoreProjectOpeningErrors = !fSettings.GetStopIfProjectFails();
					fGarbageCollect = fSettings.GetGarbageCollect();

					VectorOfProjects designProjects;
					fDesignSolution->GetVectorOfProjects( designProjects);
					for (VectorOfProjects::iterator iter = designProjects.begin() ; iter != designProjects.end() && (err == VE_OK || fState.inMaintenance) ; ++iter)
					{
						if (*iter != NULL)
						{
							VRIAServerProject *application = NULL;

							// Create opening parameters
							VRIAServerProjectOpeningParameters *projectOpeningParams = new VRIAServerProjectOpeningParameters();
							if (projectOpeningParams != NULL)
							{
								projectOpeningParams->SetOpeningMode( fState.inMaintenance ? ePOM_FOR_MAINTENANCE : ePOM_FOR_RUNNING);

								sLONG defaultAdminPort = 0;
								if (*iter == serverAdminProject && fOpeningParameters->GetCustomAdministratorHttpPort( defaultAdminPort))
									projectOpeningParams->SetCustomHttpPort( defaultAdminPort);
															
								// for Default solution, pass the WebAdmin opening parameters
								application = VRIAServerProject::OpenProject( err, this, *iter, projectOpeningParams);
								if ((application != NULL) && (err == VE_OK || fState.inMaintenance))
								{
									VUUID uuid;
									xbox_assert(application->GetUUID( uuid));
									
									fApplicationsCollection.push_back( VRefPtr<VRIAServerProject>(application));
									fApplicationsMap[uuid] = VRefPtr<VRIAServerProject>(application);
									hasAdmin |= application->IsAdministrator();

									if (!fState.inMaintenance)
									{
										VString			vstrHostName;
										VString			vstrIP;
										sLONG			nPort = 0;
										VString			vstrPattern;
										VString			vstrPublishName;
										VError			vErrorS = application-> GetPublicationSettings ( vstrHostName, vstrIP, nPort, vstrPattern, vstrPublishName );
										xbox_assert ( vErrorS == VE_OK );
										vstrPublishName. Clear ( );
										application-> GetName ( vstrPublishName );

										VString			vstrMessage;
										vstrMessage. AppendCString ( "\tProject \"" );
										vstrMessage. AppendString ( vstrPublishName );
										vstrMessage. AppendCString ( "\" published at " );
										vstrMessage. AppendString ( vstrIP );
										vstrMessage. AppendCString ( " on port " );
										vstrMessage. AppendLong ( nPort );
										vstrMessage. AppendCString ( "\n" );

										VSize		nNameLength = vstrMessage. GetLength ( ) * 2 + 1;
										char*		szchName = new char [ nNameLength ];
										vstrMessage. ToCString ( szchName, nNameLength );
										fprintf ( stdout, szchName );
										delete [ ] szchName;
									}
								}

								ReleaseRefCountable( &projectOpeningParams);
							}
							else
							{
								err = ThrowError( VE_MEMORY_FULL);
							}

							if (err != VE_OK)
							{
								VString name;
								(*iter)->GetName( name);

								VErrorBase *errBase = CreateErrorBase( VE_RIA_CANNOT_OPEN_PROJECT, &name, NULL);
								logger.LogMessageFromErrorBase( fLoggerID, errBase);
								ReleaseRefCountable( &errBase);

								if (!fState.inMaintenance)
								{
									if (application != NULL)
										application->Close();

									if (ignoreProjectOpeningErrors)
										err = VE_OK;
									else
										err = VE_RIA_CANNOT_OPEN_PROJECT;
								}
							}
							ReleaseRefCountable( &application);
						}
					}

					if (!hasAdmin && !fState.inMaintenance && (err == VE_OK))
					{
						VFile file( serverAdminProjectPath);
						if (file.Exists())
						{
							VURL url( serverAdminProjectPath);
							fDesignSolution->AddExistingProject( url, false);

							VProject *designProject = fDesignSolution->GetProjectFromFilePathOfProjectFile( serverAdminProjectPath);
							if (designProject != NULL)
							{
								VRIAServerProject *application = NULL;

								// Create opening parameters
								VRIAServerProjectOpeningParameters *projectOpeningParams = new VRIAServerProjectOpeningParameters();
								if (projectOpeningParams != NULL)
								{
									projectOpeningParams->SetOpeningMode( ePOM_FOR_RUNNING);

									sLONG defaultAdminPort = 0;
									if (fOpeningParameters->GetCustomAdministratorHttpPort( defaultAdminPort))
										projectOpeningParams->SetCustomHttpPort( defaultAdminPort);

									application = VRIAServerProject::OpenProject( err, this, designProject, projectOpeningParams);
									if (application != NULL && err == VE_OK)
									{
										VUUID uuid;
										xbox_assert(application->GetUUID( uuid));

										fApplicationsCollection.push_back( VRefPtr<VRIAServerProject>(application));
										fApplicationsMap[uuid] = VRefPtr<VRIAServerProject>(application);
									}
									ReleaseRefCountable( &projectOpeningParams);
								}
								else
								{
									err = ThrowError( VE_MEMORY_FULL);
								}

								if (err != VE_OK)
								{
									VString name;
									designProject->GetName( name);

									VErrorBase *errBase = CreateErrorBase( VE_RIA_CANNOT_OPEN_PROJECT, &name, NULL);
									logger.LogMessageFromErrorBase( fLoggerID, errBase);
									ReleaseRefCountable( &errBase);

									if (application != NULL)
										application->Close();

									if (ignoreProjectOpeningErrors)
										err = VE_OK;
									else
										err = VE_RIA_CANNOT_OPEN_PROJECT;
								}
								ReleaseRefCountable( &application);
							}
						}
					}

					fApplicationsMutex.Unlock();
				}
			}

			logger.LogMessagesFromErrorContext( fLoggerID, errContext.GetContext());

			if (err == VE_OK)
			{
				VString logMsg;
				logMsg.Printf( "Solution opened (duration: %i ms)", usCounter.Stop()/1000);
				logger.Log( fLoggerID, eL4JML_Information, logMsg);
			}
		}
	}

	fState.opened = true;

	return err;
}