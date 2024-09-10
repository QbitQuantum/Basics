void Initialize (IN USHORT Length_In)
{
    OBJECT_ATTRIBUTES	ObjectAttributes;

    STRING		DeviceName;
    USHORT		j;
    char		TestPkt[] = "WOW 32 Simulator on NT\n\r";

    RtlInitString(&DeviceName, "\\Device\\Serial1");

    //
    // set attributes
    //

    ObjectAttributes.Length = sizeof(OBJECT_ATTRIBUTES);
    ObjectAttributes.RootDirectory = NULL;
    ObjectAttributes.ObjectName = &DeviceName;
    ObjectAttributes.Attributes = OBJ_INHERIT;
    ObjectAttributes.SecuriAR) SECONDBYTE(Size);
	TransmitPkt[10] = EOT;

	if (!Xceive((USHORT)(Size+5), 11)) {
	    DbgPrint ("Sim32GetVDMPSZPointer.....Unsuccessful \a\a\n");
	    return NULL;
	}

	RtlMoveMemory(Ptr, &ReceivePkt[4], Size);
    } else {