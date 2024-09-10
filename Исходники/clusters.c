BOOL AddClusterReceiver(
	struct MidiCluster *cluster,
	struct Node *node,
	ULONG *ErrorCode,
	struct CamdBase *CamdBase
){
	struct MidiLink *midilink;
	struct DriverData *driverdata;
	struct MyMidiCluster *mycluster=(struct MyMidiCluster *)cluster;

	if(node->ln_Type!=NT_USER-MLTYPE_NTypes){
	  driverdata=FindSenderDriverInCluster(cluster);
	  if(driverdata!=NULL){
			if(driverdata->isInOpen==FALSE && driverdata->isOutOpen==FALSE){
				if(OpenDriver(driverdata,ErrorCode,CamdBase)==FALSE){
					return FALSE;
				}
	  
				driverdata->isInOpen=TRUE;
			}
		}
		midilink=(struct MidiLink *)node;
		ObtainSemaphore(&mycluster->semaphore);
		midilink->ml_Location=cluster;
	}else{
		/* The receiver is a hardware-receiver, not a midilink. */
		ObtainSemaphore(&mycluster->semaphore);
	}

	Enqueue(&cluster->mcl_Receivers,node);
	ReleaseSemaphore(&mycluster->semaphore);

	return TRUE;
}