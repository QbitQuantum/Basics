bool Burmese::processPhoneticInput()
{
	wchar_t burglishData[BGLEN]={0};
	int idx=0;bool isPatsint=false;
	bool bufferFull=false;

	this->clearPhoneticMenuData(); //clear all
	
	wcscpy(burglishData,charBuff);

	if (len(burglishData)<1) 
		return false;
		
	for(int i=0; i<BCLEN;i++){ //loop for consonent
		if(bufferFull) break;
		if(burglishData[0]>65 && burglishData[0]<65+26){
			isPatsint = true;
			burglishData[0]=burglishData[0]+32;
		}
		if(wcsstr(burglishData, _bc[i].key)==burglishData){ //find "m" in "man", ==burglishData means find at firstpos :P
			for(int i1=0; i1<4;i1++){ //loop for sub items
				if(bufferFull) break;
				if(_bc[i].val[i1]==0) break; // if no more sub items break it
				
				wchar_t burmeseData[BMLEN]={0};

				if(cmp(L"a",burglishData)!=0) //only done when it is start with "a"
					sub(burmeseData,burglishData,_bc[i].key, L""); //copy non-consonent part in displayData
				else
					wcscpy(burmeseData,burglishData);
			
				if(len(burmeseData)==0) 
					wcscpy(burmeseData,L"a");//if only type consonent, append "a"

				for(int j=0; j<BVLEN;j++){ //loop for vowel
					if(bufferFull) break;
					if(wcscmp(burmeseData, _bv[j].key)==0){ // match "an"
						for(int j1=0; j1<10;j1++){ //loop for sub items
							if(_bv[j].val[j1]==0) 
								break; // if no more sub items break it
						  
							wchar_t displayData[BMLEN]={0};
							
							if(isPatsint){
								wcscpy(burglishData,_bc[i].val[i1]);
								burglishData[0]=toLower(burglishData[0]);
								sub(burmeseData,_bv[j].val[j1],L"$1", burglishData);
								
								wcscpy(displayData,L"---");
								
							}else{
								sub(burmeseData,_bv[j].val[j1],L"$1", _bc[i].val[i1]); //replace "in" with burmese "a sat", displayData is reused
							}
							
							wcscat(displayData,burmeseData);
							
							//copying data into menu array
							wcscpy(menuItem[idx/MROW][idx%MROW].burglish,burglishData);
							wcscpy(menuItem[idx/MROW][idx%MROW].burmese,burmeseData);
	
							if((idx++)>=MLEN) {
								bufferFull=true;
								break;
							}
	
						}
					}
				}
			}
		}
	}
	menuLength=idx;
	this->processCustomDictionary();
	this->processPhoneticMenuAutoCorrect();
	
	#ifndef _TEST
		LPVOID lpOut;
		lpOut = VirtualAlloc(NULL, 20, MEM_COMMIT, PAGE_READWRITE);
		for(int Row = 0; Row < MROW; Row++)
		{
			for(int Col = 0; Col < MCOL; Col++)
			{
				if( wcslen(menuItem[Col][Row].burmese) <= 0) break;
				wcscpy((wchar_t*)lpOut,menuItem[Col][Row].burmese);
				lpOut = DoSourceReplace(lpOut,20,Zawgyi_One,curFontIndex);
				LiveConvert(Zawgyi_One,curFontIndex,(wchar_t*)lpOut);
				lpOut = replace(L"\u103B\u102B",L"\u102B\u103A",(wchar_t*)lpOut,10, curFontIndex);
				wcscpy(menuItem[Col][Row].burmese,(wchar_t*)lpOut);
			}
		}
	#endif
	
	return menuLength>0;
};