int win32_tape_device::tape_op(struct mtop *mt_com)
{
   DWORD result = NO_ERROR;
   int   index;

   if (m_fd < 3 || m_fd >= (int)(NUMBER_HANDLE_ENTRIES + 3) ||
       TapeHandleTable[m_fd - 3].OSHandle == INVALID_HANDLE_VALUE) {
      errno = EBADF;
      return -1;
   }

   PTAPE_HANDLE_INFO pHandleInfo = &TapeHandleTable[m_fd - 3];
   switch (mt_com->mt_op) {
   case MTRESET:
   case MTNOP:
   case MTSETDRVBUFFER:
      break;
   case MTRAS1:
   case MTRAS2:
   case MTRAS3:
   case MTSETDENSITY:
      errno = ENOTTY;
      result = (DWORD)-1;
      break;
   case MTFSF:
      for (index = 0; index < mt_com->mt_count; index++) {
         result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, 1, 0, FALSE);
         if (result == NO_ERROR) {
            pHandleInfo->ulFile++;
            pHandleInfo->bEOF = true;
            pHandleInfo->bEOT = false;
         }
      }
      break;
   case MTBSF:
      for (index = 0; index < mt_com->mt_count; index++) {
         result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, (DWORD)-1, ~0, FALSE);
         if (result == NO_ERROR) {
            pHandleInfo->ulFile--;
            pHandleInfo->bBlockValid = false;
            pHandleInfo->bEOD = false;
            pHandleInfo->bEOF = false;
            pHandleInfo->bEOT = false;
         }
      }
      break;
   case MTFSR:
      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_RELATIVE_BLOCKS, 0, mt_com->mt_count, 0, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOD = false;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
      } else if (result == ERROR_FILEMARK_DETECTED) {
         pHandleInfo->bEOF = true;
      }
      break;
   case MTBSR:
      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_RELATIVE_BLOCKS, 0, -mt_com->mt_count, ~0, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOD = false;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
      } else if (result == ERROR_FILEMARK_DETECTED) {
         pHandleInfo->ulFile--;
         pHandleInfo->bBlockValid = false;
         pHandleInfo->bEOD = false;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
      }
      break;
   case MTWEOF:
      result = WriteTapemark(pHandleInfo->OSHandle, TAPE_FILEMARKS, mt_com->mt_count, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOF = true;
         pHandleInfo->bEOT = false;
         pHandleInfo->ulFile += mt_com->mt_count;
         pHandleInfo->bBlockValid = true;
         pHandleInfo->ullFileStart = 0;
      }
      break;
   case MTREW:
      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_REWIND, 0, 0, 0, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOD = false;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
         pHandleInfo->ulFile = 0;
         pHandleInfo->bBlockValid = true;
         pHandleInfo->ullFileStart = 0;
      }
      break;
   case MTOFFL:
      result = PrepareTape(pHandleInfo->OSHandle, TAPE_UNLOAD, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOD = false;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
         pHandleInfo->ulFile = 0;
         pHandleInfo->ullFileStart = 0;
      }
      break;
   case MTRETEN:
      result = PrepareTape(pHandleInfo->OSHandle, TAPE_TENSION, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOD = false;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
         pHandleInfo->ulFile = 0;
         pHandleInfo->bBlockValid = true;
         pHandleInfo->ullFileStart = 0;
      }
      break;
   case MTBSFM:
      for (index = 0; index < mt_com->mt_count; index++) {
         result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, (DWORD)-1, ~0, FALSE);
         if (result == NO_ERROR) {
            result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, 1, 0, FALSE);
            pHandleInfo->bEOD = false;
            pHandleInfo->bEOF = false;
            pHandleInfo->bEOT = false;
         }
      }
      break;
   case MTFSFM:
      for (index = 0; index < mt_com->mt_count; index++) {
         result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, mt_com->mt_count, 0, FALSE);
         if (result == NO_ERROR) {
            result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, (DWORD)-1, ~0, FALSE);
            pHandleInfo->bEOD = false;
            pHandleInfo->bEOF = false;
            pHandleInfo->bEOT = false;
         }
      }
      break;
   case MTEOM:
      while (1) {
         result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_FILEMARKS, 0, 1, 0, FALSE);
         if (result != NO_ERROR) {
            pHandleInfo->bEOF = false;

            if (result == ERROR_END_OF_MEDIA) {
               pHandleInfo->bEOD = true;
               pHandleInfo->bEOT = true;
               return 0;
            }
            if (result == ERROR_NO_DATA_DETECTED) {
               pHandleInfo->bEOD = true;
               pHandleInfo->bEOT = false;
               return 0;
            }
            break;
         } else {
            pHandleInfo->bEOF = true;
            pHandleInfo->ulFile++;
         }
      }
      break;
   case MTERASE:
      result = EraseTape(pHandleInfo->OSHandle, TAPE_ERASE_LONG, FALSE);
      if (result == NO_ERROR) {
         pHandleInfo->bEOD = true;
         pHandleInfo->bEOF = false;
         pHandleInfo->bEOT = false;
         pHandleInfo->ulFile = 0;
         pHandleInfo->bBlockValid = true;
         pHandleInfo->ullFileStart = 0;
      }
      break;
   case MTSETBLK: {
      TAPE_SET_MEDIA_PARAMETERS SetMediaParameters;

      SetMediaParameters.BlockSize = mt_com->mt_count;
      result = SetTapeParameters(pHandleInfo->OSHandle, SET_TAPE_MEDIA_INFORMATION, &SetMediaParameters);
      break;
   }
   case MTSEEK: {
      TAPE_POSITION_INFO TapePositionInfo;

      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_ABSOLUTE_BLOCK, 0, mt_com->mt_count, 0, FALSE);

      memset(&TapePositionInfo, 0, sizeof(TapePositionInfo));
      DWORD dwPosResult = GetTapePositionInfo(pHandleInfo->OSHandle, &TapePositionInfo);
      if (dwPosResult == NO_ERROR && TapePositionInfo.FileSetValid) {
         pHandleInfo->ulFile = (ULONG)TapePositionInfo.FileNumber;
      } else {
         pHandleInfo->ulFile = ~0U;
      }
      break;
   }
   case MTTELL: {
      DWORD partition;
      DWORD offset;
      DWORD offsetHi;

      result = GetTapePosition(pHandleInfo->OSHandle, TAPE_ABSOLUTE_BLOCK, &partition, &offset, &offsetHi);
      if (result == NO_ERROR) {
         return offset;
      }
      break;
   }
   case MTFSS:
      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_SETMARKS, 0, mt_com->mt_count, 0, FALSE);
      break;
   case MTBSS:
      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_SPACE_SETMARKS, 0, -mt_com->mt_count, ~0, FALSE);
      break;
   case MTWSM:
      result = WriteTapemark(pHandleInfo->OSHandle, TAPE_SETMARKS, mt_com->mt_count, FALSE);
      break;
   case MTLOCK:
      result = PrepareTape(pHandleInfo->OSHandle, TAPE_LOCK, FALSE);
      break;
   case MTUNLOCK:
      result = PrepareTape(pHandleInfo->OSHandle, TAPE_UNLOCK, FALSE);
      break;
   case MTLOAD:
      result = PrepareTape(pHandleInfo->OSHandle, TAPE_LOAD, FALSE);
      break;
   case MTUNLOAD:
      result = PrepareTape(pHandleInfo->OSHandle, TAPE_UNLOAD, FALSE);
      break;
   case MTCOMPRESSION: {
      TAPE_GET_DRIVE_PARAMETERS  GetDriveParameters;
      TAPE_SET_DRIVE_PARAMETERS  SetDriveParameters;
      DWORD                      size;

      size = sizeof(GetDriveParameters);

      result = GetTapeParameters(pHandleInfo->OSHandle, GET_TAPE_DRIVE_INFORMATION, &size, &GetDriveParameters);

      if (result == NO_ERROR) {
         SetDriveParameters.ECC = GetDriveParameters.ECC;
         SetDriveParameters.Compression = (BOOLEAN)mt_com->mt_count;
         SetDriveParameters.DataPadding = GetDriveParameters.DataPadding;
         SetDriveParameters.ReportSetmarks = GetDriveParameters.ReportSetmarks;
         SetDriveParameters.EOTWarningZoneSize = GetDriveParameters.EOTWarningZoneSize;

         result = SetTapeParameters(pHandleInfo->OSHandle, SET_TAPE_DRIVE_INFORMATION, &SetDriveParameters);
      }
      break;
   }
   case MTSETPART:
      result = SetTapePosition(pHandleInfo->OSHandle, TAPE_LOGICAL_BLOCK, mt_com->mt_count, 0, 0, FALSE);
      break;
   case MTMKPART:
      if (mt_com->mt_count == 0) {
         result = CreateTapePartition(pHandleInfo->OSHandle, TAPE_INITIATOR_PARTITIONS, 1, 0);
      } else {
         result = CreateTapePartition(pHandleInfo->OSHandle, TAPE_INITIATOR_PARTITIONS, 2, mt_com->mt_count);
      }
      break;
   default:
      errno = ENOTTY;
      result = (DWORD)-1;
      break;
   }

   if ((result == NO_ERROR && pHandleInfo->bEOF) ||
       (result == ERROR_FILEMARK_DETECTED && mt_com->mt_op == MTFSR)) {

      TAPE_POSITION_INFO TapePositionInfo;

      if (GetTapePositionInfo(pHandleInfo->OSHandle, &TapePositionInfo) == NO_ERROR) {
         pHandleInfo->bBlockValid = true;
         pHandleInfo->ullFileStart = TapePositionInfo.BlockNumber;
      }
   }

   switch (result) {
   case NO_ERROR:
   case (DWORD)-1:   /* Error has already been translated into errno */
      break;
   case ERROR_FILEMARK_DETECTED:
      errno = EIO;
      break;
   case ERROR_END_OF_MEDIA:
      pHandleInfo->bEOT = true;
      errno = EIO;
      break;
   case ERROR_NO_DATA_DETECTED:
      pHandleInfo->bEOD = true;
      errno = EIO;
      break;
   case ERROR_NO_MEDIA_IN_DRIVE:
      pHandleInfo->bEOF = false;
      pHandleInfo->bEOT = false;
      pHandleInfo->bEOD = false;
      errno = ENOMEDIUM;
      break;
   case ERROR_INVALID_HANDLE:
   case ERROR_ACCESS_DENIED:
   case ERROR_LOCK_VIOLATION:
      errno = EBADF;
      break;
   default:
      errno = EIO;
      break;
   }

   return result == NO_ERROR ? 0 : -1;
}