//----handles the storage of data----//
void swapFiles()
{
	OpenWrite(hFileHandle2,nIoResultRead,sFileName2,nFileSize2);
	OpenRead(hFileHandle,nIoResult,sFileName1,nFileSize);
	float tempVar;
	char tempX, tempY, tempTheta, z;
  while(nIoResult != ioRsltEndOfFile)
  {
  	for(z = 0; z<numNeuralUnits; z++)
  	{
      ReadFloat(hFileHandle,nIoResult,tempVar);
      if(nIoResult == ioRsltEndOfFile) {break;}
      WriteFloat(hFileHandle2,nIoResultRead,tempVar);
    }
    if(nIoResult == ioRsltEndOfFile) {break;}
    ReadByte(hFileHandle, nIoResult, tempX);
    ReadByte(hFileHandle, nIoResult, tempY);
    ReadByte(hFileHandle, nIoResult, tempTheta);
    WriteByte(hFileHandle2,nIoResultRead,tempX);
    WriteByte(hFileHandle2,nIoResultRead,tempY);
    WriteByte(hFileHandle2,nIoResultRead,tempTheta);
  }
	char x;
  for(x = 0; x<numNeuralUnits; x++)
  {
    WriteFloat(hFileHandle2, nIoResult, localTemp.localArray[x]);
  }
  WriteByte(hFileHandle2, nIoResult, poseWorld.maxActivatedCell.x);
  WriteByte(hFileHandle2, nIoResult, poseWorld.maxActivatedCell.y);
  WriteByte(hFileHandle2, nIoResult, poseWorld.maxActivatedCell.theta);
  Close(hFileHandle2,nIoResultRead);
  Close(hFileHandle,nIoResult);
  Delete(sFileName1,nIoResult);
  Rename(sFileName1,nIoResult,sFileName2);
}