// Do our list content drawing here (what we see when the list is collapsed, for cObjType_DropList only)
bool	oFontDropDown::drawListContents(EXTListLineInfo *pInfo, EXTCompInfo* pECI) {
	// Draw our text
    if (pInfo->mLine > 0) {
        EXTfldval *	calcFld;
        EXTfldval fval;
			
        ECOgetProperty(mHWnd,anumListCalc,fval);
        qstring	calculation(fval);
			
        calcFld = newCalculation(calculation, pECI);
		
        if (calcFld != NULL) {
            EXTfldval	result;
            calcFld->evalCalculation(result, pECI->mLocLocp, NULL, qfalse);
            qstring		text(result);
				
            GDItextSpecStruct   textSpec = mCanvas->textSpec();
            str255              fontName;
            qpoint              leftTop(pInfo->mLineRect.left+10, pInfo->mLineRect.top);
            
#ifndef iswin32
            leftTop.h += 2;
#endif
        
            // get our font name
            EXTfldval fontNameFld;
            str255  fontNameStr;
            pInfo->mListPtr->getColVal(pInfo->mLine, mFontColumn, fftCharacter, 0, fontNameFld);
            fontNameFld.getChar(fontNameStr);
            GDIsetFontName(&textSpec.mFnt, fontNameStr.cString(), fontNameStr.length());

            // and draw our text
            mCanvas->drawText(text.cString(), leftTop, textSpec);
		
            delete calcFld;
        };
    };

	return true;
};