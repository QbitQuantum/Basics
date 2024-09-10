//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : マップデータロード
//	Description : 任意のマップデータをロードする
//	Arguments   : id / ステージID
//	Returns     : 成否(true:成功)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
bool CMapData::LoadData(int id)
{
	// ----- 初期化処理
	m_pFieldBlock.clear();
	m_pLayoutBlock.clear();
	m_pLayoutObject.clear();

	// ----- マップデータ読み込み
	std::ifstream ifs(MAPDATA_LIST[id]);
	if (ifs.fail()) {
#ifdef _DEBUG_MESSAGEBOX
		LPTSTR str = new TCHAR[256];
		_swprintf(str, _T("MapData::Load map data error! stage ID %d."), id);
		MessageBox(NULL, str, _T("error"), MB_OK | MB_ICONERROR);
		delete[] str;
#endif
		return false;
	}
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);

	// ----- マップデータ登録
	// 登録準備
	std::stringstream ss(str);
	std::string tmp;

	// 開始位置読み込み
	getline(ss, tmp, ',');		// X座標登録
	m_startPoint.x = stof(tmp);
	getline(ss, tmp, ',');		// Y座標登録
	m_startPoint.y = stof(tmp);
	getline(ss, tmp);			// 改行をスキップ

	// 左右壁位置読み込み
	getline(ss, tmp, ',');		// 左壁のX座標登録
	m_leftWallX = stof(tmp);
	getline(ss, tmp, ',');		// 右壁のX座標登録
	m_rightWallX = stof(tmp);
	getline(ss, tmp);			// 改行をスキップ

	// 上下壁位置読み込み
	getline(ss, tmp, ',');		// 上壁のY座標登録
	m_topWallY = stof(tmp);
	getline(ss, tmp, ',');		// 下壁のY座標登録
	m_bottomWallY = stof(tmp);
	getline(ss, tmp);			// 改行をスキップ

	// フィールドブロックのデータ読み込み
	CCharacter* pObj = NULL;
	CFieldBlock* pFBlock = NULL;
	int			eid = 0;
	int			prevBid = -1;
	int			cnt = 0;
	float		width = 0.0f;
	float		height = 0.0f;
	D3DXVECTOR3	color(0.0f, 0.0f, 0.0f);
	int			type = -1;
	while (getline(ss, tmp, ',')) {
		switch (cnt % MAX_DATAPARAM) {
		case DP_BID:
			break;

		case DP_EID:
			eid = stoi(tmp);
			if (eid <= 0) {
				pFBlock = CFieldBlock::Create();
				pFBlock->Init();
			}
			break;

		case DP_TEX:
		{
#ifdef _MULTI_THREAD_NOWLOADING
			EnterCriticalSection(CGame::GetCriticalSection());
#endif
			LPTSTR ws = new TCHAR[tmp.size() + 1];
			mbstowcs(ws, tmp.c_str(), tmp.size());
			ws[tmp.size()] = '\0';
			pObj = CCharacter::Create(ws);
			pObj->Init();
			delete[] ws;
#ifdef _MULTI_THREAD_NOWLOADING
			LeaveCriticalSection(CGame::GetCriticalSection());
#endif
			break;
		}

		case DP_POSX:
			pObj->TranslateX(stof(tmp));
			break;

		case DP_POSY:
			pObj->TranslateY(stof(tmp));
			break;

		case DP_POSZ:
			pObj->TranslateZ(stof(tmp));
			break;

		case DP_WIDTH:
			width = stof(tmp);
			break;

		case DP_HEIGHT:
			height = stof(tmp);
			pObj->Resize(D3DXVECTOR2(width, height));
			break;

		case DP_ANGLE:
			pObj->RotateZ(stof(tmp));
			break;

		case DP_COLR:
			color.x = stof(tmp);
			break;

		case DP_COLG:
			color.y = stof(tmp);
			break;

		case DP_COLB:
			color.z = stof(tmp);
			pObj->SetColor(color);
			break;

		case DP_COLA:
			pObj->SetAlpha(stoi(tmp));
			break;

		case DP_COLFLG:
			if (eid <= 0) {
				m_pFieldBlock.push_back(pFBlock);
			}
			if(stoi(tmp) > 0)
				m_pFieldBlock.back()->SetElement(pObj);
			break;

		case DP_TYPE:
		{
			// 0:普通のフィールドブロック
			// 1:クリア条件フィールドブロック
			// 2:障害フィールドブロック
			// 3:レイアウトブロック
			// 4:レイアウトオブジェクト
			type = stoi(tmp);
			switch(type)
			{
				case BT_NORMAL:
				case BT_CLEAR:
				case BT_OVER:
					m_pFieldBlock.back()->SetType(type);
					break;
		
				case BT_LAYOUT:
					m_pLayoutBlock.push_back(pObj);
					break;

				case BT_LAYOUTOBJ:
					m_pLayoutObject.push_back(pObj);
					break;
			}
				
			break;
		}

		case DP_TEX_NO:
			if(type == BT_LAYOUTOBJ)
				m_pLayoutObject.back()->UVDivision(stoi(tmp), LAYOUTOBJ_HFRAME, LAYOUTOBJ_VFRAME);
			break;

		default:
			break;
		}

		++cnt;	// 次のデータへ
		if (cnt >= MAX_DATAPARAM) {
			getline(ss, tmp);		// 改行をスキップ
			cnt = 0;
		}
	}

	return true;
}