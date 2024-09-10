        void Init( void )
        {
            #ifdef _WIN32
            
            char       * common;
            std::string  apple;
            HMODULE      objc;
            HMODULE      foundation;

            if( InterlockedCompareExchange( reinterpret_cast< volatile LONG * >( &inited ), 1, 0 ) != 0 )
            {
                return;
            }

            #ifdef _WIN64
            common = nullptr;
            #else
            common = getenv( "COMMONPROGRAMFILES(x86)" );
            #endif

            if( common == nullptr )
            {
                common = getenv( "COMMONPROGRAMFILES" );
            }
            
            apple = std::string( common ) + "\\Apple\\Apple Application Support";

            SetDllDirectoryA( apple.c_str() );

            objc       = LoadLibraryA( ( apple + "\\objc.dll" ).c_str() );
            foundation = LoadLibraryA( ( apple + "\\Foundation.dll" ).c_str() );

            if( objc == nullptr || foundation == nullptr )
            {
                return;
            }
            
            Internal::objc_getClass               = ( Class        ( * )( const char * )                                       )GetProcAddress( objc, "objc_getClass" );
            Internal::objc_getMetaClass           = ( Class        ( * )( const char * )                                       )GetProcAddress( objc, "objc_getMetaClass" );
            Internal::objc_getProtocol            = ( Protocol *   ( * )( const char * )                                       )GetProcAddress( objc, "objc_getProtocol" );
            Internal::objc_msgSend                = ( id           ( * )( id, SEL, ... )                                       )GetProcAddress( objc, "objc_msgSend" );
            Internal::objc_msgSend_fpret          = ( double       ( * )( id, SEL, ... )                                       )GetProcAddress( objc, "objc_msgSend_fpret" );
            Internal::objc_msgSend_stret          = ( void         ( * )( void *, id, SEL, ... )                               )GetProcAddress( objc, "objc_msgSend_stret" );
            Internal::objc_msgSendSuper           = ( id           ( * )( struct objc_super *, SEL, ... )                      )GetProcAddress( objc, "objc_msgSendSuper" );
            Internal::objc_allocateClassPair      = ( Class        ( * )( Class, const char *, size_t )                        )GetProcAddress( objc, "objc_allocateClassPair" );
            Internal::objc_registerClassPair      = ( void         ( * )( Class )                                              )GetProcAddress( objc, "objc_registerClassPair" );
            Internal::sel_registerName            = ( SEL          ( * )( const char * )                                       )GetProcAddress( objc, "sel_registerName" );
            Internal::sel_getName                 = ( const char * ( * )( SEL )                                                )GetProcAddress( objc, "sel_getName" );
            Internal::object_getClass             = ( Class        ( * )( id )                                                 )GetProcAddress( objc, "object_getClass" );
            Internal::method_getImplementation    = ( IMP          ( * )( Method )                                             )GetProcAddress( objc, "method_getImplementation" );
            Internal::method_getName              = ( SEL          ( * )( Method )                                             )GetProcAddress( objc, "method_getName" );
            Internal::class_getSuperclass         = ( Class        ( * )( Class )                                              )GetProcAddress( objc, "class_getSuperclass" );
            Internal::class_getName               = ( const char * ( * )( Class )                                              )GetProcAddress( objc, "class_getName" );
            Internal::class_copyMethodList        = ( Method     * ( * )( Class, unsigned int * )                              )GetProcAddress( objc, "class_copyMethodList" );
            Internal::class_addIvar               = ( bool         ( * )( Class, const char *, size_t, uint8_t, const char * ) )GetProcAddress( objc, "class_addIvar" );
            Internal::class_addMethod             = ( bool         ( * )( Class, SEL, IMP, const char * )                      )GetProcAddress( objc, "class_addMethod" );
            Internal::class_addProtocol           = ( bool         ( * )( Class, Protocol * )                                  )GetProcAddress( objc, "class_addProtocol" );
            Internal::class_getInstanceVariable   = ( Ivar         ( * )( Class, const char * )                                )GetProcAddress( objc, "class_getInstanceVariable" );
            Internal::ivar_getOffset              = ( ptrdiff_t    ( * )( Ivar )                                               )GetProcAddress( objc, "ivar_getOffset" );
            Internal::NSLogv                      = ( void         ( * )( id, va_list )                                        )GetProcAddress( foundation, "NSLogv" );
            
            #else
            
            if( OSAtomicCompareAndSwap32( 0, 1, &inited ) == false )
            {
                return;
            }
            
            Internal::objc_getClass               = ::objc_getClass;
            Internal::objc_getMetaClass           = ::objc_getMetaClass;
            Internal::objc_getProtocol            = ::objc_getProtocol;
            Internal::objc_msgSend                = ::objc_msgSend;
            Internal::objc_msgSend_fpret          = ::objc_msgSend_fpret;
            Internal::objc_msgSend_stret          = ::objc_msgSend_stret;
            Internal::objc_msgSendSuper           = ::objc_msgSendSuper;
            Internal::objc_allocateClassPair      = ::objc_allocateClassPair;
            Internal::objc_registerClassPair      = ::objc_registerClassPair;
            Internal::sel_registerName            = ::sel_registerName;
            Internal::sel_getName                 = ::sel_getName;
            Internal::object_getClass             = ::object_getClass;
            Internal::method_getImplementation    = ::method_getImplementation;
            Internal::method_getName              = ::method_getName;
            Internal::class_getSuperclass         = ::class_getSuperclass;
            Internal::class_getName               = ::class_getName;
            Internal::class_copyMethodList        = ::class_copyMethodList;
            Internal::class_addIvar               = ::class_addIvar;
            Internal::class_addMethod             = ::class_addMethod;
            Internal::class_addProtocol           = ::class_addProtocol;
            Internal::class_getInstanceVariable   = ::class_getInstanceVariable;
            Internal::ivar_getOffset              = ::ivar_getOffset;
            Internal::NSLogv                      = ::NSLogv;
            
            #endif
        }