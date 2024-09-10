//===============================================================================================
//===== Функция IO Control
//===============================================================================================
NTSTATUS IoCtlMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	MegaDriverData *pdata;
	NTSTATUS status = STATUS_SUCCESS;
	ULONG BytesCount =0; // Число переданных/полученных байт (пока 0)	
	PIO_STACK_LOCATION IrpStack=IoGetCurrentIrpStackLocation(Irp);
	UCHAR *buff;//for byte

	// Получаем указатель на расширение устройства
	PEXAMPLE_DEVICE_EXTENSION dx = (PEXAMPLE_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

	// Выделяем из IRP значение IOCTL кода (причина вызова)
	ULONG ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	//лог
	DbgPrint(" >MegaDriver: IoCtlDriver - we are in");

	//--------------------------------------------------------------------------------------------------------------
	switch(ControlCode)
	{
		//тут нам прислали структурку с двумя строкаме
	case IOCTL_SEND_DATA_STRUCT:
		BytesCount = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
		if(DataSize == BytesCount) 
		{
			//===================================================================================================
			//===== Получаем параметры
			//===================================================================================================
			DbgPrint(" >MegaDriver: IoCtlDriver -> Check BufferIn Size - [ok]");

			//проверяем параметр
			if(((MegaDriverData*)Irp->AssociatedIrp.SystemBuffer)->procToFind == NULL)
			{
				DbgPrint(" >MegaDriver: IoCtlDriver -> Input Params == NULL");
				break;//сваливаем нахер, ибо иначе может быть бсод...
			}
			//copy data
			strcpy(gData.procToFind, ((MegaDriverData*)Irp->AssociatedIrp.SystemBuffer)->procToFind);
			strcpy(gData.procToOpen, ((MegaDriverData*)Irp->AssociatedIrp.SystemBuffer)->procToOpen);
			//show what we have
			DbgPrint(" >MegaDriver: IoCtlDriver -> Input Params:");
			DbgPrint(" >MegaDriver: IoCtlDriver -> procToFind %s", gData.procToFind);
			DbgPrint(" >MegaDriver: IoCtlDriver -> procToOpen %s", gData.procToOpen);
			//if not BSOD =)
			gInited = TRUE;
			//Шикарно... тут мы приняли параметрЫ !!!

			//создаем нотифаер на создание нового процесса в системе
			PsSetCreateProcessNotifyRoutine(NotifyRoutine, FALSE);

			//===================================================================================================
			//===== Чонить отсылаем обратно
			//===================================================================================================
			pdata = (MegaDriverData*)Irp->AssociatedIrp.SystemBuffer;
			strcpy(gData.status, "all data accepted");//нипашет пока 
			strcpy(pdata->procToFind, "11111111111");
			strcpy(pdata->procToOpen, "22222222222");
			if(FindProcess(FindBuffer))
			{
				DbgPrint(" >MegaDriver: +++ PROCESS FOUND +++");
				strcpy(pdata->status, "found");
			}
			else
			{
				strcpy(pdata->status, "not found");
			}
			Irp->IoStatus.Information = sizeof(gData);

			DbgPrint(" >MegaDriver: IoCtlDriver -> Status: %s", pdata->status);


			//осталось всеголишь найти нужный процесс)))


			//IoRequestDpc( //create DPC
			//IoInitializeDpcRequest
			//KeInsertQueueDpc
			//PsCreateSystemThread//IRQL_PASSIVE_LEVEL
			//WriteToFile("First test string from IoCtl \r\n");
			//---------



		}
		else DbgPrint(" >MegaDriver: IoCtlDriver -> Check BufferIn Size - [failed]");
		break;
	case IOCTL_JUST_CHECK_STATUS:
		pdata = (MegaDriverData*)Irp->AssociatedIrp.SystemBuffer;
		strcpy(gData.status, "all data accepted");//нипашет пока 
		strcpy(pdata->procToFind, "11111111111");
		strcpy(pdata->procToOpen, "22222222222");
		if(FindProcess(FindBuffer))
		{
			DbgPrint(" >MegaDriver: +++ PROCESS FOUND +++");
			strcpy(pdata->status, "found");
		}
		else
		{
			strcpy(pdata->status, "not found");
		}
		Irp->IoStatus.Information = sizeof(gData);

		DbgPrint(" >MegaDriver: IoCtlDriver -> Status: %s", pdata->status);
		break;
	default:
		DbgPrint(" >MegaDriver: IoCtlDriver -> UnKnown ControlCode");
	}
	//--------------------------------------------------------------------------------------------------------------



	IoCompleteRequest(Irp, IO_NO_INCREMENT);//завершаем обработку запроса

	return STATUS_SUCCESS;
}