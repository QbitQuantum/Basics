static void JabberIqResultAdvancedSearch( XmlNode *iqNode, void *userdata )
{
	TCHAR* type;
	int    id;

	U_TCHAR_MAP mColumnsNames(10);
	LIST<void>  SearchResults(2);

	if ((( id = JabberGetPacketID( iqNode )) == -1 ) || (( type = JabberXmlGetAttrValue( iqNode, "type" )) == NULL )) {
		JSendBroadcast( NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, ( HANDLE ) id, 0 );
		return;
	}

	if ( !lstrcmp( type, _T("result"))) {
		XmlNode* queryNode=JabberXmlGetNthChild(iqNode,"query",1);
		XmlNode* xNode = JabberXmlGetChildWithGivenAttrValue( queryNode, "x", "xmlns", _T("jabber:x:data"));
		if (xNode) {
			//1. Form search results info
			XmlNode* reportNode=JabberXmlGetNthChild(xNode,"reported",1);
			if (reportNode) {
				int i = 1;
				while ( XmlNode* fieldNode = JabberXmlGetNthChild( reportNode, "field", i++ )) {
					TCHAR* var = JabberXmlGetAttrValue( fieldNode, "var" );
					if ( var ) {
						TCHAR * Label=JabberXmlGetAttrValue(fieldNode,"label");
						mColumnsNames.insert(var, (Label!=NULL) ? Label : var);
			}	}	}

			int i=1;
			XmlNode* itemNode;
			while ( itemNode = JabberXmlGetNthChild( xNode, "item", i++ )) {
				U_TCHAR_MAP *pUserColumn = new U_TCHAR_MAP(10);
				int j = 1;
				while ( XmlNode* fieldNode = JabberXmlGetNthChild( itemNode, "field", j++ )) {
					if (TCHAR * var=JabberXmlGetAttrValue(fieldNode,"var" )) {
						if (TCHAR * Text=(JabberXmlGetChild(fieldNode,"value")->text)) {
							if (!mColumnsNames[var])
								mColumnsNames.insert(var,var);
							pUserColumn->insert(var,Text);
				}	}	}

				SearchResults.insert((void*)pUserColumn);
			}
		}
		else {
			//2. Field list search results info
			int i=1;
			while ( XmlNode* itemNode = JabberXmlGetNthChild( queryNode, "item", i++ )) {
				U_TCHAR_MAP *pUserColumn=new U_TCHAR_MAP(10);
				
				TCHAR* jid = JabberXmlGetAttrValue( itemNode, "jid" );
				TCHAR* keyReturned;
				mColumnsNames.insertCopyKey( _T("jid"),_T("jid"),&keyReturned, CopyKey, DestroyKey );
				mColumnsNames.insert( _T("jid"), keyReturned );
				pUserColumn->insertCopyKey( _T("jid"), jid, NULL, CopyKey, DestroyKey );

				for ( int j=0; j < itemNode->numChild; j++ ) {
					XmlNode* child = itemNode->child[j];
					if ( child->name ) {
						TCHAR * szColumnName=a2t(child->name);
						if ( child->text && child->text[0] != _T('\0')) {
							TCHAR *keyReturned;
							mColumnsNames.insertCopyKey(szColumnName,_T(""),&keyReturned, CopyKey, DestroyKey);
							mColumnsNames.insert(szColumnName,keyReturned);
							pUserColumn->insertCopyKey(szColumnName,child->text,NULL, CopyKey, DestroyKey);
							mir_free(szColumnName);
				}	}	}

				SearchResults.insert((void*)pUserColumn);
		}	}
	}
	else if (!lstrcmp( type, _T("error"))) {
		TCHAR * code=NULL;
		TCHAR * description=NULL;
		TCHAR buff[255];
		XmlNode* errorNode = JabberXmlGetChild( iqNode, "error" );
		if (errorNode) {
			code = JabberXmlGetAttrValue(errorNode,"code");
			description = errorNode->text;
		}

		_sntprintf(buff,SIZEOF(buff),TranslateT("Error %s %s\r\nTry to specify more detailed"),code ? code : _T(""),description?description:_T(""));
		JSendBroadcast( NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, ( HANDLE ) id, 0 );
		if (searchHandleDlg )
			SetDlgItemText(searchHandleDlg,IDC_INSTRUCTIONS,buff);
		else
			MessageBox(NULL, buff, TranslateT("Search error"), MB_OK|MB_ICONSTOP);
		return;
	}

	JabberSearchReturnResults((HANDLE)id, (void*)&SearchResults, (U_TCHAR_MAP *)&mColumnsNames);

	for (int i=0; i < SearchResults.getCount(); i++ )
		delete ((U_TCHAR_MAP *)SearchResults[i]);

	//send success to finish searching
	JSendBroadcast( NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, ( HANDLE ) id, 0 );
}