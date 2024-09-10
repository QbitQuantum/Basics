intptr_t WINAPI MkDirDlgProc(HANDLE hDlg,intptr_t Msg,intptr_t Param1,void* Param2)
{
	switch (Msg)
	{
		case DN_LISTCHANGE:
			{
				if (Param1 == MKDIR_COMBOBOX_LINKTYPE)
				{
					SendDlgMessage(hDlg, DM_ENABLE, MKDIR_EDIT_LINKPATH, ToPtr(Param2 != 0));
				}
			}
			break;
		case DN_CLOSE:
		{
			if (Param1==MKDIR_OK)
			{
				string strDirName=reinterpret_cast<LPCWSTR>(SendDlgMessage(hDlg,DM_GETCONSTTEXTPTR,MKDIR_EDIT,0));
				Opt.MultiMakeDir=(SendDlgMessage(hDlg,DM_GETCHECK,MKDIR_CHECKBOX,0)==BSTATE_CHECKED);

				// это по поводу создания одиночного каталога, который
				// начинается с пробела! Чтобы ручками не заключать
				// такой каталог в кавычки
				if (Opt.MultiMakeDir && !wcspbrk(strDirName,L";,\""))
				{
					QuoteSpaceOnly(strDirName);
				}

				// нужно создать только ОДИН каталог
				if (!Opt.MultiMakeDir)
				{
					// уберем все лишние кавычки
					Unquote(strDirName);
					// возьмем в кавычки, т.к. могут быть разделители
					InsertQuote(strDirName);
				}

				UserDefinedList* pDirList=reinterpret_cast<UserDefinedList*>(SendDlgMessage(hDlg,DM_GETDLGDATA,0,0));

				if (!pDirList->Set(strDirName))
				{
					Message(MSG_WARNING,1,MSG(MWarning),MSG(MIncorrectDirList),MSG(MOk));
					return FALSE;
				}
			}
		}
		break;
	default:
		break;
	}

	return DefDlgProc(hDlg,Msg,Param1,Param2);
}