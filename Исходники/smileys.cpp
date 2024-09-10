bool SmileyPackType::LoadSmileyFileXEP(CMString& tbuf, bool onlyInfo, CMString&)
{
	_TMatcher *m0, *m1, *m2;

	_TPattern *dbname_re = _TPattern::compile(_T("<DataBaseName>\\s*\"(.*?)\"\\s*</DataBaseName>"),
		_TPattern::MULTILINE_MATCHING);
	_TPattern *author_re = _TPattern::compile(_T("<PackageAuthor>\\s*\"(.*?)\"\\s*</PackageAuthor>"),
		_TPattern::MULTILINE_MATCHING);
	_TPattern *settings_re = _TPattern::compile(_T("<settings>(.*?)</settings>"),
		_TPattern::MULTILINE_MATCHING | _TPattern::DOT_MATCHES_ALL);

	m0 = settings_re->createTMatcher(tbuf);
	if (m0->findFirstMatch()) {
		CMString settings = m0->getGroup(1);

		m1 = author_re->createTMatcher(settings);
		if (m1->findFirstMatch()) {
			m_Author = m1->getGroup(1);
			DecodeHTML(m_Author);
		}
		delete m1;

		m1 = dbname_re->createTMatcher(settings);
		if (m1->findFirstMatch()) {
			m_Name = m1->getGroup(1);
			DecodeHTML(m_Name);
		}
		delete m1;
	}
	delete m0;

	delete dbname_re;
	delete author_re;
	delete settings_re;

	if (!onlyInfo) {
		_TPattern *record_re = _TPattern::compile(_T("<record.*?ImageIndex=\"(.*?)\".*?>(?:\\s*\"(.*?)\")?(.*?)</record>"),
			_TPattern::MULTILINE_MATCHING | _TPattern::DOT_MATCHES_ALL);
		_TPattern *expression_re = _TPattern::compile(_T("<Expression>\\s*\"(.*?)\"\\s*</Expression>"),
			_TPattern::MULTILINE_MATCHING);
		_TPattern *pastetext_re = _TPattern::compile(_T("<PasteText>\\s*\"(.*?)\"\\s*</PasteText>"),
			_TPattern::MULTILINE_MATCHING);
		_TPattern *images_re = _TPattern::compile(_T("<images>(.*?)</images>"),
			_TPattern::MULTILINE_MATCHING | _TPattern::DOT_MATCHES_ALL);
		_TPattern *image_re = _TPattern::compile(_T("<Image>(.*?)</Image>"),
			_TPattern::MULTILINE_MATCHING | _TPattern::DOT_MATCHES_ALL);
		_TPattern *imagedt_re = _TPattern::compile(_T("<!\\[CDATA\\[(.*?)\\]\\]>"),
			_TPattern::MULTILINE_MATCHING);

		m0 = images_re->createTMatcher(tbuf);
		if (m0->findFirstMatch()) {
			CMString images = m0->getGroup(1);

			m1 = imagedt_re->createTMatcher(images);
			if (m1->findFirstMatch()) {
				IStream* pStream = DecodeBase64Data(T2A_SM(m1->getGroup(1).c_str()));
				if (pStream != NULL) {
					if (m_hSmList != NULL) ImageList_Destroy(m_hSmList);
					m_hSmList = ImageList_Read(pStream);
					pStream->Release();
				}
			}
			delete m1;
		}
		delete m0;

		m0 = record_re->createTMatcher(tbuf);
		while (m0->findNextMatch()) {
			SmileyType *dat = new SmileyType;

			dat->SetRegEx(true);
			dat->SetImList(m_hSmList, _ttol(m0->getGroup(1).c_str()));
			dat->m_ToolText = m0->getGroup(2);
			DecodeHTML(dat->m_ToolText);

			CMString rec = m0->getGroup(3);

			m1 = expression_re->createTMatcher(rec);
			if (m1->findFirstMatch()) {
				dat->m_TriggerText = m1->getGroup(1);
				DecodeHTML(dat->m_TriggerText);
			}
			delete m1;

			m1 = pastetext_re->createTMatcher(rec);
			if (m1->findFirstMatch()) {
				dat->m_InsertText = m1->getGroup(1);
				DecodeHTML(dat->m_InsertText);
			}
			delete m1;
			dat->SetHidden(dat->m_InsertText.IsEmpty());

			m1 = image_re->createTMatcher(rec);
			if (m1->findFirstMatch()) {
				CMString images = m1->getGroup(1);

				m2 = imagedt_re->createTMatcher(images);
				if (m2->findFirstMatch()) {
					IStream* pStream = DecodeBase64Data(T2A_SM(m2->getGroup(1).c_str()));
					if (pStream != NULL) {
						dat->LoadFromImage(pStream);
						pStream->Release();
					}
				}
				delete m2;
			}
			delete m1;

			m_SmileyList.insert(dat);
		}
		delete m0;

		delete record_re;
		delete expression_re;
		delete pastetext_re;
		delete images_re;
		delete image_re;
		delete imagedt_re;
	}

	m_VisibleCount = m_SmileyList.getCount();

	AddTriggersToSmileyLookup();

	selec.x = 0;
	selec.y = 0;
	win.x = 0;
	win.y = 0;

	return true;
}