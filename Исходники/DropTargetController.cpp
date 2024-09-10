CDropTargetController::~CDropTargetController()
{
	AtlTrace("DropTargetController destroyed\n");

	if (pTargetImpl)
	{
//		if (FAILED(pTargetImpl->RevokeDragDrop()))
		 pTargetImpl->Release();
	}
}