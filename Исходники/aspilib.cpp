//***************************************************************************
//*                                                                         *
//*  BOOL init(ULONG bufsize)                                               *
//*                                                                         *
//*  This inits the ASPI library and ASPI router driver.                    *
//*  Allocates the data buffer and passes its address to the driver         *
//*  Returns:                                                               *
//*    TRUE - Success                                                       *
//*    FALSE - Unsuccessful initialization of driver and library            *
//*                                                                         *
//*  Preconditions: ASPI router device driver has to be loaded              *
//*                                                                         *
//***************************************************************************
BOOL scsiObj::init(ULONG bufsize)
{
  BOOL  success;
  ULONG rc;

  rc = DosAllocMem(&buffer, bufsize, OBJ_TILE | PAG_READ | PAG_WRITE | PAG_COMMIT);
  if (rc) return FALSE;
  success=openDriver();                         // call openDriver member function
  if (!success) return FALSE;
  success=initSemaphore();                      // call initSemaphore member function
  if (!success) return FALSE;

  success=initBuffer();

  return TRUE;
}