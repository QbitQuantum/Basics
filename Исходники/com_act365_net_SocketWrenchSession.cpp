JNIEXPORT jint JNICALL Java_com_act365_net_SocketWrenchSession__1deinstallProvider( JNIEnv* env , jclass , jint protocol )
{
    int nDeinstalled = 0 ;

#ifdef WIN32

    int i = -1 ;

    // Find the installed service providers for the given protocol.

    int protocolList[1];

    protocolList[0] = (int) protocol ;

    if( ( nProtocols = WSAEnumProtocolsW( protocolList , protocolBuffer , & protocolBufferSize ) ) == SOCKET_ERROR ){

        jclass exceptionClass = env -> FindClass("java/net/SocketException");
            
        SocketUtils::throwError( env , exceptionClass , "WSAEnumProtocols()" );

        env -> DeleteLocalRef( exceptionClass );

        return nDeinstalled ;
    }

    // Find the path of the DLL in which the services are implemented. 
    // (It's assumed that they're all implemented in a single MS DLL).

    int errorCode = 0 , dllPathLength = maxDllPathLength ;

    if( nProtocols > 0 ){
        WSCGetProviderPath( & protocolBuffer[0].ProviderId , dllPath , & dllPathLength , & errorCode );
    }

    if( errorCode > 0 ){

        jclass exceptionClass = env -> FindClass("java/net/SocketException");
            
        SocketUtils::throwError( env , exceptionClass , "WSCGetProviderPath()" );

        env -> DeleteLocalRef( exceptionClass );

        return nDeinstalled ;
    }

    // Deinstall.
    

    while( ++ i < nProtocols && ! errorCode ){        
        nDeinstalled += WSCDeinstallProvider( & protocolBuffer[i].ProviderId , & errorCode );
    }

    if( errorCode > 0 ){

        jclass exceptionClass = env -> FindClass("java/net/SocketException");
            
        SocketUtils::throwError( env , exceptionClass , "WSCDeinstallProvider()" );

        env -> DeleteLocalRef( exceptionClass );
    }

#endif

    return nDeinstalled ;
}