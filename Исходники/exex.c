integer ExeX()			/* execute an X command */
{
	ptrdiff_t TmpSiz;

	DBGFEN(1,"ExeX",NULL);
	if (EStTop == EStBot) {			/* if no numeric argument */
		NArgmt = 1;			/* default is 1X */
	} else {
		UMinus();			/* if it's -X, make it -1X */
		if (GetNmA() == FAILURE) {	/* get numeric argument */
			DBGFEX(1,DbgFNm,"FAILURE, GetNmA() failed");
			return FAILURE;
		}
	}


	if (IncCBP() == FAILURE) {		/* move to char after X */
		DBGFEX(1,DbgFNm,"FAILURE, IncCBP() failed");
		return FAILURE;
	}

	if (FindQR() == FAILURE) {		/* find q-register values */
		DBGFEX(1,DbgFNm,"FAILURE, FindQR() failed");
		return FAILURE;
	}

	if (!(CmdMod & COLON)) {		/* if no colon modifier */
		if (QR->Start != NULL) {	/* if text area not empty */
			ZFree((voidptr)QR->Start);/* free allocated memory */
			QR->Start = QR->End_P1 = NULL;
		}
	}

	if ((CmdMod & MARGIS) == '\0') {	/* if it's nXq (not m,nXq) */
		NArgmt = Ln2Chr(NArgmt);
		if (NArgmt > 0) {
			if (MakRom((size_t)NArgmt) == FAILURE) {
				DBGFEX(1,DbgFNm,"FAILURE, MakRom() failed");
				return FAILURE;
			}
			MEMMOVE(QR->End_P1, GapEnd+1, (size_t)NArgmt);
			QR->End_P1 += NArgmt;
		} else if (NArgmt < 0) {
			if (MakRom((size_t)-NArgmt) == FAILURE) {
				DBGFEX(1,DbgFNm,"FAILURE, MakRom() failed");
				return FAILURE;
			}
			MEMMOVE(QR->End_P1, GapBeg+NArgmt, (size_t)-NArgmt);
			QR->End_P1 -= NArgmt;
		}
	} else if (NArgmt != MArgmt) {		/* else (it's m,nXq) */
		MEMMOVE(ErrTxt, "m,nX", 5);
		if (GetAra() == FAILURE) {
			DBGFEX(1,DbgFNm,"FAILURE, GetAra() failed");
			return FAILURE;
		}
		if ((AraBeg < GapBeg) && (AraEnd > GapEnd)) {
			TmpSiz = (GapBeg-AraBeg) + (AraEnd-GapEnd);
			if (TmpSiz > 0) {
				if (MakRom((size_t)TmpSiz) == FAILURE) {
					DBGFEX(1,DbgFNm,"FAILURE, MakRom() failed");
					return FAILURE;
				}
				MEMMOVE(QR->End_P1,
					AraBeg,
					(size_t)(GapBeg - AraBeg));
				QR->End_P1 += GapBeg-AraBeg;
				MEMMOVE(QR->End_P1,
					GapEnd+1,
					(size_t)(AraEnd - GapEnd));
				QR->End_P1 += AraEnd-GapEnd;
			}
		} else {			/* else area is contiguous */
			TmpSiz = (AraEnd - AraBeg) + 1;
			if (TmpSiz > 0) {
				if (MakRom((size_t)TmpSiz) == FAILURE) {
					DBGFEX(1,DbgFNm,"FAILURE, MakRom() failed");
					return FAILURE;
				}
				MEMMOVE(QR->End_P1, AraBeg, (size_t)TmpSiz);
				QR->End_P1 += TmpSiz;
			}
		}
	}

	CmdMod = '\0';			/* clear modifiers flags */

	DBGFEX(1,DbgFNm,"SUCCESS");
	return SUCCESS;
}