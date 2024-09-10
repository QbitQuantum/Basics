	void PolycodePlayer::runFile(String fileName) {
		
		Logger::log("Running %s\n", fileName.c_str());
		
		L=lua_open();
		
		/*
		 luaopen_base(L);	// load basic libs (eg. print)
		 luaopen_math(L);
		 luaopen_table(L);
		 luaopen_package(L);
		 */
		luaL_openlibs(L);
		
		luaopen_Polycode(L);
		//luaopen_Tau(L);	// load the wrappered module
		
		
		lua_getfield(L, LUA_GLOBALSINDEX, "package");	// push "package"
		lua_getfield(L, -1, "loaders");					// push "package.loaders"
		lua_remove(L, -2);								// remove "package"
		
		// Count the number of entries in package.loaders.
		// Table is now at index -2, since 'nil' is right on top of it.
		// lua_next pushes a key and a value onto the stack.
		int numLoaders = 0;
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) 
		{
			lua_pop(L, 1);
			numLoaders++;
		}
		
		lua_pushinteger(L, numLoaders + 1);
		lua_pushcfunction(L, MyLoader);
		lua_rawset(L, -3);
		
		// Table is still on the stack.  Get rid of it now.
		lua_pop(L, 1);		
		
		lua_register(L, "debugPrint", debugPrint);			
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "class");		
		lua_call(L, 1, 0);

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "Polycode");		
		lua_call(L, 1, 0);		
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "defaults");		
		lua_call(L, 1, 0);
		
		for(int i=0; i < loadedModules.size(); i++) {
			String moduleName = loadedModules[i];
#ifdef _WINDOWS
			TCHAR _tempPath[4098];
			TCHAR tempPath[4098];
			GetTempPathW(4098, _tempPath);
			GetLongPathNameW(_tempPath, tempPath, 4098);
			String moduleDestPath = String(tempPath) + String("\\") + moduleName+ String(".dll");
#else
			String moduleDestPath = String("/tmp/") + moduleName+ String(".dylib");
#endif
			String moduleLoadCall = String("luaopen_") + moduleName;
			lua_getfield(L, LUA_GLOBALSINDEX, "require");
			lua_pushstring(L, moduleName.c_str());		
			lua_call(L, 1, 0);

			lua_getfield(L, LUA_GLOBALSINDEX, "package");
			lua_getfield(L, -1, "loadlib");	
			lua_pushstring(L, moduleDestPath.c_str());
			lua_pushstring(L, moduleLoadCall.c_str());			
			lua_call(L, 2, 1);
			lua_setfield(L, LUA_GLOBALSINDEX, "f");			
			
			lua_getfield(L, LUA_GLOBALSINDEX, "f");
			lua_getfield(L, LUA_GLOBALSINDEX, "__core__services__instance");						
			lua_call(L, 1, 0);			
			//local f = package.loadlib("/Users/ivansafrin/Desktop/Workshop/HelloPolycodeLUA/libPolycode2DPhysicsModule.dylib", "luaopen_Physics2D")
			//f(Polycore.CoreServices_getInstance())
					
		}

		String fileData = "";

		OSFILE *inFile = OSBasics::open(fileName, "r");	
		if(inFile) {
			Logger::log("Opened entrypoint file...");
			OSBasics::seek(inFile, 0, SEEK_END);	
			long progsize = OSBasics::tell(inFile);
			OSBasics::seek(inFile, 0, SEEK_SET);
			char *buffer = (char*)malloc(progsize+1);
			memset(buffer, 0, progsize+1);
			OSBasics::read(buffer, progsize, 1, inFile);
			fileData = String(buffer);		
			free(buffer);
			OSBasics::close(inFile);	
		} else {
			Logger::log("Error opening entrypoint file (%s)\n", fileName.c_str());
		}
		
		
		String postpend = ""; //" \nif update == nil then\nfunction update(e)\nend\nend\nwhile CORE:Update() do\nupdate(CORE:getElapsed())\nend";
		
		//String fullScript = prepend + prepend2 + prepend3 + fileData;// + postpend;
		String fullScript = fileData;
		//String fullScript = fileData;// + postpend;
		
		doneLoading = true;
		
		//lua_gc(L, LUA_GCSTOP, 0);
		
		
/*
		lua_pushliteral(L, "debug");
		lua_gettable(L, LUA_GLOBALSINDEX);
		lua_pushliteral(L, "traceback");  // correct fn name?
		lua_gettable(L, -2);

*/				
		
		//CoreServices::getInstance()->getCore()->lockMutex(CoreServices::getRenderMutex());			
		if (report(L, luaL_loadstring(L, fullScript.c_str()) || lua_pcall(L, 0,0,0))) {
			
			//CoreServices::getInstance()->getCore()->unlockMutex(CoreServices::getRenderMutex());			
			Logger::log("CRASH LOADING SCRIPT FILE\n");
//			exit(1);				
		} else  {
		//	CoreServices::getInstance()->getCore()->unlockMutex(CoreServices::getRenderMutex());			
			if (report(L, luaL_loadstring(L, postpend.c_str()) || lua_pcall(L, 0,0,0))) {	
//				exit(1);
				Logger::log("CRASH IN SCRIPT EXECUTION FILE\n");			
			} else  {

			}
		}

	}