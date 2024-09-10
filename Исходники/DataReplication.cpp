bool FObjectReplicator::ReceivedBunch( FInBunch& Bunch, const FReplicationFlags& RepFlags, bool& bOutHasUnmapped )
{
	UObject* Object = GetObject();

	if ( Object == NULL )
	{
		UE_LOG(LogNet, Verbose, TEXT("ReceivedBunch: Object == NULL"));
		return false;
	}

	UPackageMap * PackageMap = OwningChannel->Connection->PackageMap;

	const bool bIsServer = ( OwningChannel->Connection->Driver->ServerConnection == NULL );

	const FClassNetCache * ClassCache = OwningChannel->Connection->Driver->NetCache->GetClassNetCache( ObjectClass );

	if ( ClassCache == NULL )
	{
		UE_LOG(LogNet, Error, TEXT("ReceivedBunch: ClassCache == NULL: %s"), *Object->GetFullName());
		return false;
	}

	bool bThisBunchReplicatedProperties = false;

	// Read first field
	const FFieldNetCache * FieldCache = ReadField( ClassCache, Bunch );

	if ( Bunch.IsError() )
	{
		UE_LOG(LogNet, Error, TEXT("ReceivedBunch: Error reading field 1: %s"), *Object->GetFullName());
		return false;
	}

	if ( FieldCache == NULL )
	{
		// There are no actual replicated properties or functions in this bunch. That is ok - we may have gotten this
		// actor/sub-object because we want the client to spawn one (but we aren't actually replicating properties on it)
		return true;
	}

	while ( FieldCache )
	{
		// Receive properties from the net.
		UProperty* ReplicatedProp = NULL;

		while ( FieldCache && ( ReplicatedProp = Cast< UProperty >( FieldCache->Field ) ) != NULL )
		{
			NET_CHECKSUM( Bunch );

			// Server shouldn't receive properties.
			if ( bIsServer )
			{
				UE_LOG(LogNet, Error, TEXT("Server received unwanted property value %s in %s"), *ReplicatedProp->GetName(), *Object->GetFullName());
				return false;
			}
		
			bThisBunchReplicatedProperties = true;

			if ( !bHasReplicatedProperties )
			{
				bHasReplicatedProperties = true;		// Persistent, not reset until PostNetReceive is called
				PreNetReceive();
			}

			bool DebugProperty = false;
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			{
				static IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("net.Replication.DebugProperty"));
				if (CVar && !CVar->GetString().IsEmpty() && ReplicatedProp->GetName().Contains(CVar->GetString()) )
				{
					UE_LOG(LogRep, Log, TEXT("Replicating Property[%d] %s on %s"), ReplicatedProp->RepIndex, *ReplicatedProp->GetName(), *Object->GetName());
					DebugProperty = true;
				}
			}
#endif
			if ( !Retirement[ ReplicatedProp->RepIndex ].CustomDelta )
			{
				bool bLocalHasUnmapped = false;
				// We hijack a non custom delta property to signify we are using FRepLayout to read the entire property block
				if ( !RepLayout->ReceiveProperties( ObjectClass, RepState, (void*)Object, Bunch, bLocalHasUnmapped ) )
				{
					UE_LOG(LogRep, Error, TEXT("ReceiveProperties FAILED %s in %s"), *ReplicatedProp->GetName(), *Object->GetFullName());
					return false;
				}

				if ( bLocalHasUnmapped )
				{
					bOutHasUnmapped = true;
				}
			}
			else
			{
				// Receive array index.
				uint32 Element = 0;
				if ( ReplicatedProp->ArrayDim != 1 )
				{
					check( ReplicatedProp->ArrayDim >= 2 );

					Bunch.SerializeIntPacked( Element );

					if ( Element >= (uint32)ReplicatedProp->ArrayDim )
					{
						UE_LOG(LogRep, Error, TEXT("Element index too large %s in %s"), *ReplicatedProp->GetName(), *Object->GetFullName());
						return false;
					}
				}

				// Pointer to destination.
				uint8* Data = ReplicatedProp->ContainerPtrToValuePtr<uint8>((uint8*)Object, Element);
				TArray<uint8>	MetaData;
				const PTRINT DataOffset = Data - (uint8*)Object;

				// Receive custom delta property.
				UStructProperty * StructProperty = Cast< UStructProperty >( ReplicatedProp );

				if ( StructProperty == NULL )
				{
					// This property isn't custom delta
					UE_LOG(LogRepTraffic, Error, TEXT("Property isn't custom delta %s"), *ReplicatedProp->GetName());
					return false;
				}

				UScriptStruct * InnerStruct = StructProperty->Struct;

				if ( !( InnerStruct->StructFlags & STRUCT_NetDeltaSerializeNative ) )
				{
					// This property isn't custom delta
					UE_LOG(LogRepTraffic, Error, TEXT("Property isn't custom delta %s"), *ReplicatedProp->GetName());
					return false;
				}

				UScriptStruct::ICppStructOps * CppStructOps = InnerStruct->GetCppStructOps();

				check( CppStructOps );
				check( !InnerStruct->InheritedCppStructOps() );

				FNetDeltaSerializeInfo Parms;

				FNetSerializeCB NetSerializeCB( OwningChannel->Connection->Driver );

				Parms.DebugName			= StructProperty->GetName();
				Parms.Struct			= InnerStruct;
				Parms.Map				= PackageMap;
				Parms.Reader			= &Bunch;
				Parms.NetSerializeCB	= &NetSerializeCB;

				// Call the custom delta serialize function to handle it
				CppStructOps->NetDeltaSerialize( Parms, Data );

				if ( Bunch.IsError() )
				{
					UE_LOG(LogNet, Error, TEXT("ReceivedBunch: NetDeltaSerialize - Bunch.IsError() == true: %s"), *Object->GetFullName());
					return false;
				}

				if ( Parms.bOutHasMoreUnmapped )
				{
					UnmappedCustomProperties.Add( DataOffset, StructProperty );
					bOutHasUnmapped = true;
				}

				// Successfully received it.
				UE_LOG(LogRepTraffic, Log, TEXT(" %s - %s"), *Object->GetName(), *ReplicatedProp->GetName());

				// Notify the Object if this var is RepNotify
				QueuePropertyRepNotify( Object, ReplicatedProp, Element, MetaData );
			}	
			
			// Read next field
			FieldCache = ReadField( ClassCache, Bunch );

			if ( Bunch.IsError() )
			{
				UE_LOG(LogNet, Error, TEXT("ReceivedBunch: Error reading field 2: %s"), *Object->GetFullName());
				return false;
			}
		}

		// Handle function calls.
		if ( FieldCache && Cast< UFunction >( FieldCache->Field ) )
		{
			FName Message = FieldCache->Field->GetFName();
			UFunction * Function = Object->FindFunction( Message );

			if ( Function == NULL )
			{
				UE_LOG(LogNet, Error, TEXT("ReceivedBunch: Function == NULL: %s"), *Object->GetFullName());
				return false;
			}

			if ( ( Function->FunctionFlags & FUNC_Net ) == 0 )
			{
				UE_LOG(LogRep, Error, TEXT("Rejected non RPC function %s in %s"), *Message.ToString(), *Object->GetFullName());
				return false;
			}

			if ( ( Function->FunctionFlags & ( bIsServer ? FUNC_NetServer : ( FUNC_NetClient | FUNC_NetMulticast ) ) ) == 0 )
			{
				UE_LOG(LogRep, Error, TEXT("Rejected RPC function due to access rights %s in %s"), *Message.ToString(), *Object->GetFullName());
				return false;
			}

			UE_LOG(LogRepTraffic, Log, TEXT("      Received RPC: %s"), *Message.ToString());

			// Get the parameters.
			FMemMark Mark(FMemStack::Get());
			uint8* Parms = new(FMemStack::Get(),MEM_Zeroed,Function->ParmsSize)uint8;

			// Use the replication layout to receive the rpc parameter values
			TSharedPtr<FRepLayout> FuncRepLayout = OwningChannel->Connection->Driver->GetFunctionRepLayout( Function );

			FuncRepLayout->ReceivePropertiesForRPC( Object, Function, OwningChannel, Bunch, Parms );

			if ( Bunch.IsError() )
			{
				UE_LOG(LogRep, Error, TEXT("ReceivedBunch: ReceivePropertiesForRPC - Bunch.IsError() == true: Function: %s, Object: %s"), *Message.ToString(), *Object->GetFullName());
				return false;
			}

			// validate that the function is callable here
			const bool bCanExecute = ( !bIsServer || RepFlags.bNetOwner );		// we are client or net owner

			if ( bCanExecute )
			{
				// Call the function.
				RPC_ResetLastFailedReason();

				Object->ProcessEvent( Function, Parms );

				if ( RPC_GetLastFailedReason() != NULL )
				{
					UE_LOG(LogRep, Error, TEXT("ReceivedBunch: RPC_GetLastFailedReason: %s"), RPC_GetLastFailedReason());
					return false;
				}
			}
			else
			{
				UE_LOG(LogRep, Verbose, TEXT("Rejected unwanted function %s in %s"), *Message.ToString(), *Object->GetFullName());

				if ( !OwningChannel->Connection->TrackLogsPerSecond() )	// This will disconnect the client if we get here too often
				{
					UE_LOG(LogRep, Error, TEXT("Rejected too many unwanted functions %s in %s"), *Message.ToString(), *Object->GetFullName());
					return false;
				}
			}

			// Destroy the parameters.
			//warning: highly dependent on UObject::ProcessEvent freeing of parms!
			for ( UProperty * Destruct=Function->DestructorLink; Destruct; Destruct=Destruct->DestructorLinkNext )
			{
				if( Destruct->IsInContainer(Function->ParmsSize) )
				{
					Destruct->DestroyValue_InContainer(Parms);
				}
			}

			Mark.Pop();

			if ( Object == NULL || Object->IsPendingKill() )
			{
				// replicated function destroyed Object
				return true;		// FIXME: Should this return false to kick connection?  Seems we'll cause a read misalignment here if we don't
			}

			// Next.
			FieldCache = ReadField( ClassCache, Bunch );

			if ( Bunch.IsError() )
			{
				UE_LOG(LogNet, Error, TEXT("ReceivedBunch: Error reading field 3: %s"), *Object->GetFullName());
				return false;
			}
		}
		else if ( FieldCache )
		{
			UE_LOG(LogRep, Error, TEXT("ReceivedBunch: Invalid replicated field %i in %s"), FieldCache->FieldNetIndex, *Object->GetFullName());
			return false;
		}
	}

	return true;
}