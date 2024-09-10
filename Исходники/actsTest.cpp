int main(void)
{
  ArACTSBlob blob;
  double xRel, yRel;
  int i;

  acts.openPort(NULL);
  acts.requestPacket();
  while(1)
  {
    if (acts.receiveBlobInfo())
      {
	//acts.receiveBlobInfo();
	for (i = 0; i < 8; i++)
	  if (acts.getNumBlobs(i) >= 1 && acts.getBlob(i, 1, &blob))
	    {
	      xRel = (double)(blob.getXCG() - WIDTH/2.0) / (double)WIDTH;
	      yRel = (double)(blob.getYCG() - HEIGHT/2.0) / (double)HEIGHT;
	      printf("Chan %d xRel %.4f yRel %.4f    ", i, xRel, yRel);
	      blob.log();
	    }
	acts.requestPacket();
	ArUtil::sleep(80);
      }
    ArUtil::sleep(5);
  }

}