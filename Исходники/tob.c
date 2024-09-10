BOOLEAN
obtest( void )
{
    ULONG i;
    HANDLE Handles[ 2 ];
    NTSTATUS Status;
    OBJECT_TYPE_INITIALIZER ObjectTypeInitializer;

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    RtlInitString( &ObjectTypeAName, "ObjectTypeA" );
    RtlInitString( &ObjectTypeBName, "ObjectTypeB" );

    RtlZeroMemory( &ObjectTypeInitializer, sizeof( ObjectTypeInitializer ) );
    ObjectTypeInitializer.Length = sizeof( ObjectTypeInitializer );
    ObjectTypeInitializer.ValidAccessMask = -1;

    ObjectTypeInitializer.PoolType = NonPagedPool;
    ObjectTypeInitializer.MaintainHandleCount = TRUE;
    ObjectTypeInitializer.DumpProcedure = DumpAProc;
    ObjectTypeInitializer.OpenProcedure = OpenAProc;
    ObjectTypeInitializer.CloseProcedure = CloseAProc;
    ObjectTypeInitializer.DeleteProcedure = DeleteAProc;
    ObjectTypeInitializer.ParseProcedure = ParseAProc;
    ObCreateObjectType(
        &ObjectTypeAName,
        &ObjectTypeInitializer,
        (PSECURITY_DESCRIPTOR)NULL,
        &ObjectTypeA
        );

    ObjectTypeInitializer.PoolType = NonPagedPool;
    ObjectTypeInitializer.MaintainHandleCount = FALSE;
    ObjectTypeInitializer.GenericMapping = MyGenericMapping;
    ObjectTypeInitializer.DumpProcedure = DumpBProc;
    ObjectTypeInitializer.OpenProcedure = NULL;
    ObjectTypeInitializer.CloseProcedure = NULL;
    ObjectTypeInitializer.DeleteProcedure = DeleteBProc;
    ObjectTypeInitializer.ParseProcedure = NULL;
    ObCreateObjectType(
        &ObjectTypeBName,
        &ObjectTypeInitializer,
        (PSECURITY_DESCRIPTOR)NULL,
        &ObjectTypeB
        );

    ObpDumpTypes( NULL );

    RtlInitString( &DirectoryName, "\\MyObjects" );
    InitializeObjectAttributes( &DirectoryObjA,
                                &DirectoryName,
                                OBJ_PERMANENT |
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );
    NtCreateDirectoryObject( &DirectoryHandle,
                             0,
                             &DirectoryObjA
                           );
    NtClose( DirectoryHandle );

    RtlInitString( &ObjectAName, "\\myobjects\\ObjectA" );
    InitializeObjectAttributes( &ObjectAObjA,
                                &ObjectAName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );

    RtlInitString( &ObjectBName, "\\myobjects\\ObjectB" );
    InitializeObjectAttributes( &ObjectBObjA,
                                &ObjectBName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );

    Status = ObCreateObject(
        KernelMode,
        ObjectTypeA,
        &ObjectAObjA,
        KernelMode,
        NULL,
        (ULONG)sizeof( OBJECTTYPEA ),
        0L,
        0L,
        (PVOID *)&ObjectBodyA
        );

    ObjectA = (POBJECTTYPEA)ObjectBodyA;
    ObjectA->TypeALength = sizeof( *ObjectA );
    for (i=0; i<4; i++) {
        ObjectA->Stuff[i] = i+1;
        }
    KeInitializeEvent( &ObjectA->Event, NotificationEvent, TRUE );

    Status = ObCreateObject(
        KernelMode,
        ObjectTypeB,
        &ObjectBObjA,
        KernelMode,
        NULL,
        (ULONG)sizeof( OBJECTTYPEB ),
        0L,
        0L,
        (PVOID *)&ObjectBodyB
        );

    ObjectB = (POBJECTTYPEB)ObjectBodyB;
    ObjectB->TypeBLength = sizeof( *ObjectB );
    for (i=0; i<16; i++) {
        ObjectB->Stuff[i] = i+1;
        }
    KeInitializeSemaphore ( &ObjectB->Semaphore, 2L, 2L );

    Status = ObInsertObject(
        ObjectBodyA,
        SYNCHRONIZE | 0x3,
        NULL,
        1,
        &ObjectBodyA,
        &ObjectHandleA1
        );

    DbgPrint( "Status: %lx  ObjectBodyA: %lx  ObjectHandleA1: %lx\n",
             Status, ObjectBodyA, ObjectHandleA1
           );

    Status = ObInsertObject(
        ObjectBodyB,
        SYNCHRONIZE | 0x1,
        NULL,
        1,
        &ObjectBodyB,
        &ObjectHandleB1
        );

    DbgPrint( "Status: %lx  ObjectBodyB: %lx  ObjectHandleB1: %lx\n",
             Status, ObjectBodyB, ObjectHandleB1
           );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    RtlInitString( &ObjectAName, "\\MyObjects\\ObjectA" );
    InitializeObjectAttributes( &ObjectAObjA,
                                &ObjectAName,
                                OBJ_OPENIF,
                                NULL,
                                NULL
                              );

    Status = ObCreateObject(
        KernelMode,
        ObjectTypeA,
        &ObjectAObjA,
        KernelMode,
        NULL,
        (ULONG)sizeof( OBJECTTYPEA ),
        0L,
        0L,
        (PVOID *)&ObjectBodyA1
        );


    Status = ObInsertObject(
        ObjectBodyA1,
        SYNCHRONIZE | 0x3,
        NULL,
        1,
        &ObjectBodyA2,
        &ObjectHandleA2
        );

    DbgPrint( "Status: %lx  ObjectBodyA1: %lx  ObjectBodyA2: %lx  ObjectHandleA2: %lx\n",
             Status, ObjectBodyA1, ObjectBodyA2, ObjectHandleA2
           );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );
    NtClose( ObjectHandleA2 );
    ObDereferenceObject( ObjectBodyA2 );    // ObInsertObject,ObjectPointerBias

    NtWaitForSingleObject( ObjectHandleB1, TRUE, NULL );
    Handles[ 0 ] = ObjectHandleA1;
    Handles[ 1 ] = ObjectHandleB1;
    NtWaitForMultipleObjects( 2, Handles, WaitAny, TRUE, NULL );

    ObReferenceObjectByHandle(
        ObjectHandleA1,
        0L,
        ObjectTypeA,
        KernelMode,
        &ObjectBodyA,
        NULL
        );

    ObReferenceObjectByHandle(
        ObjectHandleB1,
        0L,
        ObjectTypeB,
        KernelMode,
        &ObjectBodyB,
        NULL
        );
    DbgPrint( "Reference Handle %lx = %lx\n", ObjectHandleA1, ObjectBodyA );

    DbgPrint( "Reference Handle %lx = %lx\n", ObjectHandleB1, ObjectBodyB );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    ObReferenceObjectByPointer(
        ObjectBodyA,
        0L,
        ObjectTypeA,
        KernelMode
        );

    ObReferenceObjectByPointer(
        ObjectBodyB,
        0L,
        ObjectTypeB,
        KernelMode
        );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    RtlInitString( &ObjectAPathName, "\\MyObjects\\ObjectA" );
    RtlInitString( &ObjectBPathName, "\\MyObjects\\ObjectB" );
    ObReferenceObjectByName(
        &ObjectAPathName,
        OBJ_CASE_INSENSITIVE,
        0L,
        ObjectTypeA,
        KernelMode,
        NULL,
        &ObjectBodyA
        );

    ObReferenceObjectByName(
        &ObjectBPathName,
        OBJ_CASE_INSENSITIVE,
        0L,
        ObjectTypeB,
        KernelMode,
        NULL,
        &ObjectBodyB
        );

    DbgPrint( "Reference Name %s = %lx\n", ObjectAPathName.Buffer,
            ObjectBodyA );

    DbgPrint( "Reference Name %s = %lx\n", ObjectBPathName.Buffer,
            ObjectBodyB );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    ObDereferenceObject( ObjectBodyA );     // ObInsertObject,ObjectPointerBias
    ObDereferenceObject( ObjectBodyB );

    ObDereferenceObject( ObjectBodyA );     // ObReferenceObjectByHandle
    ObDereferenceObject( ObjectBodyB );

    ObDereferenceObject( ObjectBodyA );     // ObReferenceObjectByPointer
    ObDereferenceObject( ObjectBodyB );

    ObDereferenceObject( ObjectBodyA );     // ObReferenceObjectByName
    ObDereferenceObject( ObjectBodyB );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    InitializeObjectAttributes( &ObjectAObjA,
                                &ObjectAPathName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );
    ObOpenObjectByName(
        &ObjectAObjA,
        0L,
        NULL,
        ObjectTypeA,
        KernelMode,
        NULL,
        &ObjectHandleA2
        );

    InitializeObjectAttributes( &ObjectBObjA,
                                &ObjectBPathName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );
    ObOpenObjectByName(
        &ObjectBObjA,
        0L,
        NULL,
        ObjectTypeB,
        KernelMode,
        NULL,
        &ObjectHandleB2
        );

    DbgPrint( "Open Object Name %s = %lx\n", ObjectAPathName.Buffer,
            ObjectHandleA2 );

    DbgPrint( "Open Object Name %s = %lx\n", ObjectBPathName.Buffer,
            ObjectHandleB2 );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    NtClose( ObjectHandleA1 );
    NtClose( ObjectHandleB1 );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    ObReferenceObjectByHandle(
        ObjectHandleA2,
        0L,
        ObjectTypeA,
        KernelMode,
        &ObjectBodyA,
        NULL
        );

    ObReferenceObjectByHandle(
        ObjectHandleB2,
        0L,
        ObjectTypeB,
        KernelMode,
        &ObjectBodyB,
        NULL
        );
    DbgPrint( "Reference Handle %lx = %lx\n", ObjectHandleA2, ObjectBodyA );

    DbgPrint( "Reference Handle %lx = %lx\n", ObjectHandleB2, ObjectBodyB );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    ObOpenObjectByPointer(
        ObjectBodyA,
        OBJ_CASE_INSENSITIVE,
        0L,
        NULL,
        ObjectTypeA,
        KernelMode,
        &ObjectHandleA1
        );

    ObOpenObjectByPointer(
        ObjectBodyB,
        OBJ_CASE_INSENSITIVE,
        0L,
        NULL,
        ObjectTypeB,
        KernelMode,
        &ObjectHandleB1
        );

    DbgPrint( "Open Object Pointer %lx = %lx\n", ObjectBodyA,
            ObjectHandleA1 );

    DbgPrint( "Open Object Pointer %lx = %lx\n", ObjectBodyB,
            ObjectHandleB1 );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    ObReferenceObjectByHandle(
        ObjectHandleA1,
        0L,
        ObjectTypeA,
        KernelMode,
        &ObjectBodyA,
        NULL
        );

    ObReferenceObjectByHandle(
        ObjectHandleB1,
        0L,
        ObjectTypeB,
        KernelMode,
        &ObjectBodyB,
        NULL
        );
    DbgPrint( "Reference Handle %lx = %lx\n", ObjectHandleA1, ObjectBodyA );

    DbgPrint( "Reference Handle %lx = %lx\n", ObjectHandleB1, ObjectBodyB );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    ObDereferenceObject( ObjectBodyA );     // ObReferenceObjectByHandle
    ObDereferenceObject( ObjectBodyB );

    ObDereferenceObject( ObjectBodyA );     // ObReferenceObjectByHandle
    ObDereferenceObject( ObjectBodyB );

    NtClose( ObjectHandleA1 );
    NtClose( ObjectHandleB1 );

    NtClose( ObjectHandleA2 );
    NtClose( ObjectHandleB2 );

    ObpDumpObjectTable( ObpGetObjectTable(), NULL );

    TestFunction = NULL;

    return( TRUE );
}