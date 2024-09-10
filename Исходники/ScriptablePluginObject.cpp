bool
ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args,
                               uint32_t argCount, NPVariant *result)
/*
name : method name
args : arguments
argCount : number of arguments
result : return value
*/
{
	NPIdentifier test_id = NPN_GetStringIdentifier("test");
	if (name == test_id) {
		printf("temp = %s\n",getTemporaryPath());
		printf("home = %s\n",getHomePath());
		printf("firefox = %s\n",getFirefoxPath());
		printf("conf = %s\n",getConfPath());
		printf("classpath = %s\n",getClassPath());
		printf("spawn = %s\n",getSpawnPath());
		VOID_TO_NPVARIANT(*result);
		return true;
	}

	NPError err;
	if (!this->HasMethod(name))
		return false;
	VOID_TO_NPVARIANT(*result);

	//login.jsp test
	NPIdentifier doSignature_id = NPN_GetStringIdentifier("doSignature");
	NPIdentifier getPublicKeyContent_id = NPN_GetStringIdentifier("getPublicKeyContent");


	NPObject* sWindowNPObj;

	if ((err = NPN_GetValue(mNpp, NPNVWindowNPObject, &sWindowNPObj)) != NPERR_NO_ERROR) {
		printf("Error in getting NPNVWindowNPObject: %d\n",err);
		return false;
	}

	const char *tmpdir = getTemporaryPath();
	const char *classpath = getClassPath();
	const char *spawnpath = getSpawnPath();

	if (name == doSignature_id) {
		if ((argCount == 2) && (NPVARIANT_IS_STRING(args[0])) && (NPVARIANT_IS_STRING(args[1]))) {
			char *randomStr = NULL;
			char *tpmPass = NULL;
			NPString n_randomStr = NPVARIANT_TO_STRING(args[0]);
			NPString n_tpmPass = NPVARIANT_TO_STRING(args[1]);
			m_strFromNP(&randomStr,n_randomStr);
			m_strFromNP(&tpmPass,n_tpmPass);
			printf("input = %s, %s",randomStr, tpmPass);

			char* ret = NULL;
			char *fname = tempnam(tmpdir,"jni");
			if (fname == NULL)
				fname = "tmp";
			char* margs[12];
			margs[0] = (char*) spawn_file;
			margs[1] = "--file";
			margs[2] = fname;
			margs[3] = "--method";
			margs[4] = "doSignature";
			margs[5] = "--classpath";
			margs[6] = (char*) classpath;
			margs[7] = "--args";
			margs[8] = "2";
			margs[9] = randomStr;
			margs[10] = tpmPass;
			margs[11] = NULL;
			// in windows use registry to find Firefox directory
			// in other OS, use path _spawnvp
			int rval = _spawnv(_P_WAIT,spawnpath,margs);
			if (rval) {
				fprintf(stderr,"error = %d\n",rval);
			}
			else {
				ret = getFileContent(fname);
				if (ret) {
					STRINGZ_TO_NPVARIANT(ret,*result); 
				}
				else {
					fprintf(stderr,"cannot read output file");
				}
				unlink(fname);
			}
			free(fname);
		}
		else {
			NPString str;
			str.UTF8Characters = "alert('usage: doSignature(String, String)');";
			str.UTF8Length = strlen(str.UTF8Characters);
			NPN_Evaluate(this->mNpp, sWindowNPObj, &str, NULL);
		}
	}
	else if (name == getPublicKeyContent_id) {
		if (argCount == 0) {
			char *ret = NULL;
			char *fname = tempnam(tmpdir,"jni");
			if (fname == NULL)
				fname = "tmp";
			char* margs[8];
			margs[0] = (char*) spawn_file;
			margs[1] = "--file";
			margs[2] = fname;
			margs[3] = "--method";
			margs[4] = "getPublicKeyContent";
			margs[5] = "--classpath";
			margs[6] = (char*) classpath;
			margs[7] = NULL;
			int rval = _spawnv(_P_WAIT,spawnpath,margs);
			if (rval) {
				fprintf(stderr,"error = %d\n",rval);
			}
			else {
				ret = getFileContent(fname);
				if (ret) {
					STRINGZ_TO_NPVARIANT(ret,*result); 
				}
				else {
					fprintf(stderr,"cannot read output file");
				}
				unlink(fname);
			}
			free(fname);
		}
		else {
			NPString str;
			str.UTF8Characters = "alert('usage: getPublicKeyContent()');";
			str.UTF8Length = strlen(str.UTF8Characters);
			NPN_Evaluate(this->mNpp, sWindowNPObj, &str, NULL);
		}
	}
	NPN_ReleaseObject(sWindowNPObj);
  return true;
}