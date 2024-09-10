uint8 COM_Menu_Enter(uint8 Index,uint8 *Buf)
{
	typedef   void 	(*FuncUint8)(uint8);
	const COM_MenuStruct *CurMenu;
	if(Index>=Menu_OptionLength(MenuList))return 0;
	CurMenu=&MenuList[Index];
	USART_WriteDatas(USART2,&Buf[0],20);
	switch(CurMenu->Type)
	{
  		case VT_Task:if(CurMenu->Value)((Func)CurMenu->Value)();break;
//		case VT_TaskUint8:if(CurMenu->Value)((FuncUint8)CurMenu->Value)(CurMenu->Note);break;
		  case VT_Uint8:*(uint8 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
  		case VT_Int8:*(int8 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
  		case VT_Uint16:*(uint16 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
			case VT_ROMUint32:*(uint32 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
			case VT_Float:*(float *)(CurMenu->Value)=GetStringToNumber(Buf);break;
			case VT_U32BIT:if(Strstr((const char *)Buf,"T")>0)*(uint32 *)(CurMenu->Value)|=BIT(CurMenu->Note);else *(uint32 *)(CurMenu->Value)&=~BIT(CurMenu->Note);break;
			case VT_BOOL:if(Strstr((const char *)Buf,"T")>0)*(uint8 *)(CurMenu->Value)=True;else *(uint8 *)(CurMenu->Value)=False;break;
//		case VT_IP:*(uint32 *)(CurMenu->Value)=MUI_GetIP(*(uint32 *)(CurMenu->Value),IT_Num|IT_Dot);break;
//		case VT_Color:*(uint16 *)(CurMenu->Value)=MUI_GetColor(*(uint16 *)(CurMenu->Value),IT_Num|IT_Dot);break;
		case VT_Str:BufferCoppy(&Buf[0],(uint8 *)(CurMenu->Value),CurMenu->Note);break;
	}
	return 1;
}