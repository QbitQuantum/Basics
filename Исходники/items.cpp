STDMETHODIMP C_Items::Retrieve(I_Archive * arc)
{
	if (!arc)
		return E_POINTER;

	C_STLException::install();

	//TODO - templatize this function and stick it in a base class.
	try {

		BSTR bs = NULL;
		unsigned int len = 0;

		if (S_OK != arc->RetrieveString(&bs)) {
			return E_FAIL;
		}

		String s(bs);
		s.toLower();
		String::FreeBSTR(&bs);

		static String tags[5] = {
			_T("mmp:item"),
			_T("mmp:text"),
			_T("mmp:node"),
			_T("mmp:picture"),
			_T("mmp:branch")
		};

		typedef enum ematches {
			plainitem,
			text,
			node,
			picture,
			branch
		};

		static String types[4] = {
			_T("node"),
			_T("text-block"),
			_T("picture"),
			_T("branch")
		};

		ematches match = plainitem;

		CLSID clsid;
		IID iid;

		StringPtr ptr(s.Find(tags[plainitem]));
		StringPtr ptrKill(s.Find(tags[plainitem]));

		for (unsigned int test = plainitem; test <= branch; test++) {

			ptr = s.Find(tags[test]);

			if (ptr.isValid()) {

				ptrKill = s.Find(String(_T("/")) + tags[test]);
				match = static_cast<ematches>(test);

				break;
			}
		}

		switch (match) {
		case node:
			clsid = CLSID_Node;
			iid = IID_I_Node;
			break;
		case text:
			clsid = CLSID_TextBlock;
			iid = IID_I_TextBlock;
			break;
		case picture:
			clsid = CLSID_Picture;
			iid = IID_I_Picture;
			break;
		case branch:
			clsid = CLSID_Branch;
			iid = IID_I_Branch;
			break;
		}

		while (ptr.isValid() && !ptrKill.isValid()) {//Check this is the start of an item...

			C_ItemPtr item;

			/////////////////////////////////////////////////////
			//	In a paste operation, the object's GUID must be ignored
			//	- a new object is being created with its own identity.
			BOOL b = FALSE;
			BOOL bPreserveID = TRUE;
			BSTR bs = NULL;

			arc->get_PreserveIdentities(&bPreserveID);

			if (bPreserveID) {

				/////////////////////////////////////////////////////
				//	Get the GUID to identify the object. Check if it 
				//	exists already - if so, divert the serialisation data
				//	to the existing object and add a reference to the 
				//	Children collection.
				String sUUID;

				StringPtr ptrUUID = s.Find(_T("uuid"));

				if (ptrUUID.isValid()) {

					StringPtr ptrLeft = s.Find(_T("\""), ptrUUID);
					ptrLeft++;

					if (ptrLeft.isValid()) {

						StringPtr ptrRight = s.Find(_T("\""), ptrLeft);

						if (ptrRight.isValid()) {
							sUUID = s.Mid(ptrLeft.Index(), ptrRight.Index() - ptrLeft.Index());
						}
						else {
							sUUID = s.Right(s.GetLength() - ptrLeft.Index());
						}

						T_SafeArray<char> buffer(sUUID.GetLength() + 1);

						::_stprintf(buffer[0], _T("%s\0"), sUUID.toLPCTSTR());

						GUID guid = String(buffer[0]).toGUID();

						map<GUID, I_MapItem*>::iterator it = m_S_Items.find(guid);

						if (it != m_S_Items.end()) {

							//The object with this GUID already exists in the item map
							item = (*it).second;

							_ASSERTE(item);

							if (item) {

								VARIANT v;

								C_UniquePtr unique(item);

								if (unique) {
									unique->get_UID(&bs);
								}

								VariantInit(&v);
								v.vt = VT_BSTR;
								v.bstrVal = bs;

								get_Exists(v, &b);

								if (!b) {

									//	Add the item to the collection
									Add(bs, item);
									b = TRUE;
								}
							}
						}
					}
				}
			}

			if (b) {

				if (bs) {
					String::FreeBSTR(&bs);
				}
			}
			else {

				if (match == plainitem) {

					int type = -1;

					StringPtr ptrType = s.Find(_T("type"));
					String sType;

					if (ptrType.isValid()) {

						StringPtr ptrLeft = s.Find(_T("\""), ptrType);

						if (ptrLeft.isValid()) {

							ptrLeft++;
							StringPtr ptrRight = s.Find(_T("\""), ptrLeft);

							if (ptrRight.isValid()) {
								sType = s.Mid(ptrLeft.Index(), ptrRight.Index() - ptrLeft.Index());
							}
							else {
								sType = s.Right(s.GetLength() - ptrLeft.Index());
							}

							for (int n = 0; n < 4; n++) {

								if (sType == types[n]) {

									type = n;

									switch (type) {
									case 0:
										clsid = CLSID_Node;
										iid = IID_I_Node;
										break;
									case 1:
										clsid = CLSID_TextBlock;
										iid = IID_I_TextBlock;
										break;
									case 2:
										clsid = CLSID_Picture;
										iid = IID_I_Picture;
										break;
									case 3:
										clsid = CLSID_Branch;
										iid = IID_I_Branch;
										break;
									}

									break;
								}
							}
						}
					}

					if (type < 0) {

						/////////////////////////////////////////////////////
						//	Get the CLSID and IID to identify the object's type
						String sCLSID;
						StringPtr ptrCLSID = s.Find(_T("clsid"));
						StringPtr ptrLeft = s.Find(_T("\""), ptrCLSID);
						ptrLeft++;
						StringPtr ptrRight = s.Find(_T("\""), ptrLeft);

						if (ptrRight.isValid()) {
							sCLSID = s.Mid(ptrLeft.Index(), ptrRight.Index() - ptrLeft.Index());
						}
						else {
							sCLSID = s.Right(s.GetLength() - ptrLeft.Index());
						}

						bs = sCLSID.toBSTR();
						CLSIDFromString(bs, &clsid);
						String::FreeBSTR(&bs);

						String sIID;
						StringPtr ptrIID = s.Find(_T("iid"));
						ptrLeft = s.Find(_T("\""), ptrIID);
						ptrLeft++;
						ptrRight = s.Find(_T("\""), ptrLeft);

						if (ptrRight.isValid()) {
							sIID = s.Mid(ptrLeft.Index(), ptrRight.Index() - ptrLeft.Index());
						}
						else {
							sIID = s.Right(s.GetLength() - ptrLeft.Index());
						}

						bs = sIID.toBSTR();
						IIDFromString(bs, &iid);
						String::FreeBSTR(&bs);
					}
				}

				//	TODO: Drop the string parameter
				item = NewItem(clsid, iid, String(_T("")));
			}

			if (item) {

				arc->Rollback();

				C_PersistentPtr persist(item);

				if (persist) {

					persist->Serialise(arc);

					C_DrawingStrategyPtr strategy(item);

					if (strategy) {
						strategy->putref_Parent(m_pParent);
					}

					BOOL bHasFocus = FALSE;

					item->get_HasFocus(&bHasFocus);

					if (bHasFocus) {

						I_ECBDiagram *map = NULL;

						if (m_pParent) {
							m_pParent->get_Map(&map);
						}

						if (map) {

							map->putref_CurrentSelection(item);
							map->Release();
						}
					}
				}
			}

			if (match == plainitem) {

				//	Discard closing tag
				if (S_OK != arc->RetrieveString(&bs)) {
					return E_FAIL;
				}

				s = bs;
				String::FreeBSTR(&bs);

				s = s.toLower();
				ptr = s.Find(tags[match]);
				ptrKill = s.Find(String(_T("/")) + tags[match]);
			}
			else {
				break;
			}
		}

		if (match == plainitem && !ptrKill.isValid()) {

			//...if it isn't, it doesn't belong here!
			arc->Rollback();
		}

		//	Sort the items as soon as they're retrieved
		Sort();
	}
	catch (C_STLNonStackException const &exception) {
		exception.Log(_T("Exception in C_Items::Retrieve"));
	}

	return S_OK;
}