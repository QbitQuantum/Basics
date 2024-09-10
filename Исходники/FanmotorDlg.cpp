int CFanmotorDlg::rFWData(int fType, int nByte)
{
	success=1;
	CString s;
	int dat=0;
	int timeout_counter=0;
	long r;
	CByteArray baAddr;
	baAddr.SetSize (1);   
	baAddr.SetAt(0,fType); 
	COleVariant ReadAddress(baAddr); // Create ReadAddress argument
	VARIANT dataIn;
	VariantInit(&dataIn);

	///*Sleep(50);*/
	//long r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress, 
 //                                  1, &dataIn);  
	do{
		timeout_counter++;
		if (timeout_counter == TIMEOUT){
			DisplayInforMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Device is not available.\nPlease check your hardware connection and power supply!");
			success = 0;
		}
		r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress,nByte, &dataIn); 
	}while ((r !=34) && (timeout_counter != TIMEOUT));
	//{
		CString strByte;
		for (long i = 0; i < nByte; i++) {
			BYTE ReadByte;
			SafeArrayGetElement(dataIn.parray, &i, &ReadByte);
			strByte.Format(L"%02x",ReadByte);
			s += strByte;
		}
		dat=use_debugdlg_main.string2int(s,2*nByte);
		success=1;
	//}
	//else {ErrorMsg(r);};
	VariantClear(&dataIn);
	return dat;	
}