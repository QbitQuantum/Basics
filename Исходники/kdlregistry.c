/* 
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= **
 *
 * Open registry and obtain our log file location
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= **
 */
VOID OpenRegKeyStorage( IN PDEVICE_OBJECT theDeviceObject )
{

HANDLE                           hkey;
PVOID                            Data;
NTSTATUS                         Status;
UNICODE_STRING                   KeyName;
UNICODE_STRING                   KeyValue;
ULONG                            ResultLength;
PKEY_VALUE_PARTIAL_INFORMATION   KeyValueInfo;
OBJECT_ATTRIBUTES                KeyObjectAttributes;
OBJECT_ATTRIBUTES                SubKeyObjectAttributes;


    // DDK : "Macro initializes the opaque OBJECT_ATTRIBUTES structure, which specifies 
    //        the properties of an object handle to routines that open handles."
    InitializeObjectAttributes ( &KeyObjectAttributes,                    // InitializedAttributes
                                 &gRegistryPath,                          // ObjectName
                                 OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,// Attributes
                                 NULL,                                    // RootDirectory
                                 NULL );                                  // SecurityDescriptor

    // Open a handle to the driver regkey
    Status = ZwOpenKey( &hkey,                 // KeyHandle
                        KEY_READ,              // DesiredAccess
		                &KeyObjectAttributes );// ObjectAttributes

    // If we fail this check we most likely have more problems then we can deal with anyways
	if ( !NT_SUCCESS( Status ) )
	{
KdPrint( ("ZwOpenKey() Failure in OpenRegKeyFile()\n") );
	}


    RtlInitUnicodeString( &KeyName, L"Storage" );
	// Open our subkey for our log file location
	Status = ZwQueryValueKey( hkey,
                              &KeyName,
                              KeyValuePartialInformation,
                              NULL,
                              0,
                              &ResultLength );

    // Error catch if the key was not found
    if ( Status == STATUS_INVALID_PARAMETER  ) 
	{
KdPrint( ("ZwQueryValueKey() Failed in OpenRegKey()\n") );
	}

    // Allocate some memory for our returned key structure
    KeyValueInfo = ( PKEY_VALUE_PARTIAL_INFORMATION ) ExAllocatePoolWithTag( NonPagedPool, 
		                                                                     ResultLength, 
																		     POOL_TAG_REGISTRY_STORAGE_KEY );
    // Requery the key with proper size requirements of the return structure
    Status = ZwQueryValueKey( hkey,
                              &KeyName,
                              KeyValuePartialInformation,
                              KeyValueInfo,
                              ResultLength,
                              &ResultLength );

    // Allocate memory for the return file path
	Data = ExAllocatePoolWithTag( NonPagedPool, 
		                          ResultLength  + sizeof( WCHAR ),
							      POOL_TAG_REGISTRY_STORAGE ); 

    RtlZeroMemory( Data, ResultLength + sizeof( WCHAR ) );

    RtlCopyMemory( Data, (PVOID) KeyValueInfo->Data, KeyValueInfo->DataLength );

    RtlInitUnicodeString( &KeyValue, Data );

    // DDK : "Macro initializes the opaque OBJECT_ATTRIBUTES structure, which specifies 
    //        the properties of an object handle to routines that open handles."
	InitializeObjectAttributes( &SubKeyObjectAttributes,                 // InitializedAttributes
		                        &KeyValue,                               // ObjectName
								OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,// Attributes
								NULL,                                    // RootDirectory
								NULL );                                  // SecurityDescriptor

   // Create our log file on disk
   CreateLogFile( theDeviceObject, SubKeyObjectAttributes );

   // Free working key value
   ExFreePoolWithTag( Data , POOL_TAG_REGISTRY_STORAGE );
   // Free key
   ExFreePoolWithTag( KeyValueInfo, POOL_TAG_REGISTRY_STORAGE_KEY );
   // Close the regkey
   ZwClose( hkey );
}