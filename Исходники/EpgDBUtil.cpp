BOOL CEpgDBUtil::AddEIT(WORD PID, const CEITTable* eit, __int64 streamTime)
{
	if( eit == NULL ){
		return FALSE;
	}
	CBlockLock lock(&this->dbLock);

	ULONGLONG key = _Create64Key(eit->original_network_id, eit->transport_stream_id, eit->service_id);

	//サービスのmapを取得
	map<ULONGLONG, SERVICE_EVENT_INFO>::iterator itr;
	SERVICE_EVENT_INFO* serviceInfo = NULL;

	itr = serviceEventMap.find(key);
	if( itr == serviceEventMap.end() ){
		serviceInfo = &serviceEventMap.insert(std::make_pair(key, SERVICE_EVENT_INFO())).first->second;
	}else{
		serviceInfo = &itr->second;
	}

	SI_TAG siTag;
	siTag.tableID = eit->table_id;
	siTag.version = eit->version_number;
	siTag.time = (DWORD)(streamTime / (10 * I64_1SEC));

	if( eit->table_id <= 0x4F && eit->section_number <= 1 ){
		//[p/f]
		if( siTag.time == 0 ){
			//チャンネル変更時の応答性のため、タイムスタンプ不明の[p/f]が来たらDB上の不明でない[p/f]をクリアする
			//EPGファイルを入力するときは古い[p/f]による上書きが発生するので、利用側で時系列にするかタイムスタンプを確定させる工夫が必要
			if( serviceInfo->nowEvent && serviceInfo->nowEvent->time != 0 ||
			    serviceInfo->nextEvent && serviceInfo->nextEvent->time != 0 ){
				serviceInfo->nowEvent.reset();
				serviceInfo->nextEvent.reset();
			}
		}
		if( eit->eventInfoList.empty() ){
			//空セクション
			if( eit->section_number == 0 ){
				if( serviceInfo->nowEvent && siTag.time >= serviceInfo->nowEvent->time ){
					serviceInfo->nowEvent.reset();
				}
			}else{
				if( serviceInfo->nextEvent && siTag.time >= serviceInfo->nextEvent->time ){
					serviceInfo->nextEvent.reset();
				}
			}
		}
	}
	//イベントごとに更新必要が判定
	for( size_t i=0; i<eit->eventInfoList.size(); i++ ){
		const CEITTable::EVENT_INFO_DATA* eitEventInfo = &eit->eventInfoList[i];
		map<WORD, std::unique_ptr<EVENT_INFO>>::iterator itrEvent;
		EVENT_INFO* eventInfo = NULL;

		if( eitEventInfo->running_status == 1 || eitEventInfo->running_status == 3 ){
			//非実行中または停止中
			_OutputDebugString(L"★非実行中または停止中イベント ONID:0x%04x TSID:0x%04x SID:0x%04x EventID:0x%04x %04d/%02d/%02d %02d:%02d",
				eit->original_network_id,  eit->transport_stream_id, eit->service_id, eitEventInfo->event_id,
				eitEventInfo->start_time.wYear, eitEventInfo->start_time.wMonth, eitEventInfo->start_time.wDay, eitEventInfo->start_time.wHour, eitEventInfo->start_time.wMinute
				);
			continue;
		}

#ifdef DEBUG_EIT
		wsprintfA(g_szDebugEIT, "%c%04x.%02x%02x.%02d.%d\r\n", eit->table_id <= 0x4F ? 'P' : 'S',
			eitEventInfo->event_id, eit->table_id, eit->section_number, eit->version_number, siTag.time % 1000000);
#endif
		//[actual]と[other]は等価に扱う
		//[p/f]と[schedule]は各々完全に独立してデータベースを作成する
		if( eit->table_id <= 0x4F && eit->section_number <= 1 ){
			//[p/f]
			if( eit->section_number == 0 ){
				if( eitEventInfo->StartTimeFlag == FALSE ){
					OutputDebugString(L"Invalid EIT[p/f]\r\n");
				}else if( serviceInfo->nowEvent == NULL || siTag.time >= serviceInfo->nowEvent->time ){
					if( serviceInfo->nowEvent == NULL || serviceInfo->nowEvent->event_id != eitEventInfo->event_id ){
						//イベント入れ替わり
						serviceInfo->nowEvent.reset();
						if( serviceInfo->nextEvent && serviceInfo->nextEvent->event_id == eitEventInfo->event_id ){
							serviceInfo->nowEvent.swap(serviceInfo->nextEvent);
							serviceInfo->nowEvent->time = 0;
						}
					}
					if( serviceInfo->nowEvent == NULL ){
						eventInfo = new EVENT_INFO;
						serviceInfo->nowEvent.reset(eventInfo);
						eventInfo->event_id = eitEventInfo->event_id;
						eventInfo->time = 0;
						eventInfo->tagBasic.version = 0xFF;
						eventInfo->tagBasic.time = 0;
						eventInfo->tagExt.version = 0xFF;
						eventInfo->tagExt.time = 0;
					}else{
						eventInfo = serviceInfo->nowEvent.get();
					}
				}
			}else{
				if( serviceInfo->nextEvent == NULL || siTag.time >= serviceInfo->nextEvent->time ){
					if( serviceInfo->nextEvent == NULL || serviceInfo->nextEvent->event_id != eitEventInfo->event_id ){
						serviceInfo->nextEvent.reset();
						if( serviceInfo->nowEvent && serviceInfo->nowEvent->event_id == eitEventInfo->event_id ){
							serviceInfo->nextEvent.swap(serviceInfo->nowEvent);
							serviceInfo->nextEvent->time = 0;
						}
					}
					if( serviceInfo->nextEvent == NULL ){
						eventInfo = new EVENT_INFO;
						serviceInfo->nextEvent.reset(eventInfo);
						eventInfo->event_id = eitEventInfo->event_id;
						eventInfo->time = 0;
						eventInfo->tagBasic.version = 0xFF;
						eventInfo->tagBasic.time = 0;
						eventInfo->tagExt.version = 0xFF;
						eventInfo->tagExt.time = 0;
					}else{
						eventInfo = serviceInfo->nextEvent.get();
					}
				}
			}
		}else if( PID != 0x0012 || eit->table_id > 0x4F ){
			//[schedule]もしくは(H-EITでないとき)[p/f after]
			//TODO: イベント消滅には対応していない(クラス設計的に対応は厳しい)。EDCB的には実用上のデメリットはあまり無い
			if( eitEventInfo->StartTimeFlag == FALSE || eitEventInfo->DurationFlag == FALSE ){
				OutputDebugString(L"Invalid EIT[schedule]\r\n");
			}else{
				itrEvent = serviceInfo->eventMap.find(eitEventInfo->event_id);
				if( itrEvent == serviceInfo->eventMap.end() ){
					eventInfo = new EVENT_INFO;
					eventInfo->event_id = eitEventInfo->event_id;
					serviceInfo->eventMap[eventInfo->event_id].reset(eventInfo);
					eventInfo->time = 0;
					eventInfo->tagBasic.version = 0xFF;
					eventInfo->tagBasic.time = 0;
					eventInfo->tagExt.version = 0xFF;
					eventInfo->tagExt.time = 0;
				}else{
					eventInfo = itrEvent->second.get();
				}
			}
		}
		if( eventInfo ){
			//開始時間等はタイムスタンプのみを基準に更新
			if( siTag.time >= eventInfo->time ){
				eventInfo->StartTimeFlag = eitEventInfo->StartTimeFlag;
				eventInfo->start_time = eitEventInfo->start_time;
				eventInfo->DurationFlag = eitEventInfo->DurationFlag;
				eventInfo->durationSec = (eitEventInfo->durationHH * 60 + eitEventInfo->durationMM) * 60 + eitEventInfo->durationSS;
				eventInfo->freeCAFlag = eitEventInfo->free_CA_mode;
				eventInfo->time = siTag.time;
			}
			//記述子はテーブルバージョンも加味して更新(単に効率のため)
			if( siTag.time >= eventInfo->tagExt.time ){
				if( eit->version_number != eventInfo->tagExt.version ||
				    eit->table_id != eventInfo->tagExt.tableID ||
				    siTag.time > eventInfo->tagExt.time + 180 ){
					if( AddExtEvent(eventInfo, &eitEventInfo->descriptorList) != FALSE ){
						eventInfo->tagExt = siTag;
					}
				}else{
					eventInfo->tagExt.time = siTag.time;
				}
			}
			//[schedule extended]以外
			if( (eit->table_id < 0x58 || 0x5F < eit->table_id) && (eit->table_id < 0x68 || 0x6F < eit->table_id) ){
				if( eit->table_id > 0x4F && eventInfo->tagBasic.version != 0xFF && eventInfo->tagBasic.tableID <= 0x4F ){
					//[schedule][p/f after]とも運用するサービスがあれば[p/f after]を優先する(今のところサービス階層が分離しているのであり得ないはず)
					_OutputDebugString(L"Conflicts EIT[schedule][p/f after] SID:0x%04x EventID:0x%04x\r\n", eit->service_id, eventInfo->event_id);
				}else if( siTag.time >= eventInfo->tagBasic.time ){
					if( eit->version_number != eventInfo->tagBasic.version ||
					    eit->table_id != eventInfo->tagBasic.tableID ||
					    siTag.time > eventInfo->tagBasic.time + 180 ){
						AddBasicInfo(eventInfo, &eitEventInfo->descriptorList, eit->original_network_id, eit->transport_stream_id);
					}
					eventInfo->tagBasic = siTag;
				}
			}
		}
	}

	if( eit->original_network_id == 0x0003 ){
		return TRUE;
	}
	
	//セクションステータス
	if( PID != 0x0012 ){
		//L-EIT
		if( eit->table_id <= 0x4F ){
			if( serviceInfo->lastTableID != eit->table_id ||
			    serviceInfo->sectionList[0].version != eit->version_number + 1 ){
				serviceInfo->lastTableID = 0;
			}
			if( serviceInfo->lastTableID == 0 ){
				//リセット
				memset(&serviceInfo->sectionList.front(), 0, sizeof(SECTION_FLAG_INFO) * 8);
				for( int i = 1; i < 8; i++ ){
					//第0テーブル以外のセクションを無視
					memset(serviceInfo->sectionList[i].ignoreFlags, 0xFF, sizeof(serviceInfo->sectionList[0].ignoreFlags));
				}
				serviceInfo->lastTableID = eit->table_id;
			}
			//第0セグメント以外のセクションを無視
			memset(serviceInfo->sectionList[0].ignoreFlags + 1, 0xFF, sizeof(serviceInfo->sectionList[0].ignoreFlags) - 1);
			//第0セグメントの送られないセクションを無視
			for( int i = eit->segment_last_section_number % 8 + 1; i < 8; i++ ){
				serviceInfo->sectionList[0].ignoreFlags[0] |= 1 << i;
			}
			serviceInfo->sectionList[0].version = eit->version_number + 1;
			serviceInfo->sectionList[0].flags[0] |= 1 << (eit->section_number % 8);
		}

	}else{
		//H-EIT
		if( eit->table_id > 0x4F ){
			BYTE& lastTableID = eit->table_id % 16 >= 8 ? serviceInfo->lastTableIDExt : serviceInfo->lastTableID;
			vector<SECTION_FLAG_INFO>& sectionList = eit->table_id % 16 >= 8 ? serviceInfo->sectionExtList : serviceInfo->sectionList;
			if( sectionList.empty() ){
				//拡張情報はないことも多いので遅延割り当て
				sectionList.resize(8);
			}
			if( lastTableID != eit->last_table_id ){
				lastTableID = 0;
			}else if( sectionList[eit->table_id % 8].version != 0 &&
			          sectionList[eit->table_id % 8].version != eit->version_number + 1 ){
				OutputDebugString(L"EIT[schedule] updated\r\n");
				lastTableID = 0;
			}
			if( lastTableID == 0 ){
				//リセット
				memset(&sectionList.front(), 0, sizeof(SECTION_FLAG_INFO) * 8);
				for( int i = eit->last_table_id % 8 + 1; i < 8; i++ ){
					//送られないテーブルのセクションを無視
					memset(sectionList[i].ignoreFlags, 0xFF, sizeof(sectionList[0].ignoreFlags));
				}
				lastTableID = eit->last_table_id;
			}
			//送られないセグメントのセクションを無視
			memset(sectionList[eit->table_id % 8].ignoreFlags + eit->last_section_number / 8 + 1, 0xFF,
				sizeof(sectionList[0].ignoreFlags) - eit->last_section_number / 8 - 1);
			if( eit->table_id % 8 == 0 && streamTime > 0 ){
				//放送済みセグメントのセクションを無視
				memset(sectionList[0].ignoreFlags, 0xFF, streamTime / (3 * 60 * 60 * I64_1SEC) % 8);
			}
			//このセグメントの送られないセクションを無視
			for( int i = eit->segment_last_section_number % 8 + 1; i < 8; i++ ){
				sectionList[eit->table_id % 8].ignoreFlags[eit->section_number / 8] |= 1 << i;
			}
			sectionList[eit->table_id % 8].version = eit->version_number + 1;
			sectionList[eit->table_id % 8].flags[eit->section_number / 8] |= 1 << (eit->section_number % 8);
		}
	}

	return TRUE;
}