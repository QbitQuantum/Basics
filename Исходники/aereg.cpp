JNIEXPORT void JNICALL 
Java_org_gudy_azureus2_platform_win32_access_impl_AEWin32AccessInterface_deleteValueW(
	JNIEnv		*env,
	jclass		cla,
	jint		_type, 
	jstring		_subkey_name,
	jstring		_value_name )
{
	HKEY		key;
	HKEY		subkey;
	WCHAR		subkey_name[1024];
	WCHAR		value_name[1024];

	jstring		result	= NULL;

	key	= mapHKEY( env, _type );

	if ( key == NULL ){

		return;
	}

	if ( !jstringToCharsW( env, _subkey_name, subkey_name, sizeof( subkey_name ))){

		return;
	}

	if ( !jstringToCharsW( env, _value_name, value_name, sizeof( value_name ))){

		return;
	}

	if ( RegOpenKeyW( key, subkey_name, &subkey ) == ERROR_SUCCESS ){


		RegCloseKey(subkey);

		if ( SHDeleteValueW( key, subkey_name, value_name ) != ERROR_SUCCESS ){

			throwException( env, "deleteValue", "SHDeleteValue failed" );
		}
	}
}