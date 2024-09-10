BOOL CSoftInfoQueryTask::TaskProcess(CTaskMgr *pMgr)
{
	do
	{
		ISQLiteComDatabase3 *pDB = _pSoftQuery->GetDBPtr();
		if(pMgr->IsExited()) break;

		// 1.查询本地缓存
		{
			SoftInfo2List resultList;
			CCacheSoftInfoOpr softInfoOpr(pDB);
			SoftQueryInfoIter endQuery = _softQueryInfoList.end();
			for(SoftQueryInfoIter it = _softQueryInfoList.begin(); it != endQuery; )
			{
				wstring grade;
				if(softInfoOpr.Query(it->_id, grade) && !grade.empty())
				{
					resultList.push_back(SoftInfo2(it->_id, grade));
					_softQueryInfoList.erase(it++);
				}
				else
				{
					++it;
				}
			}

			// 3.通知用户
			if(pMgr->IsExited()) break;
			if(!resultList.empty())
			{
				CSoftInfoEnum softInfoEnum(resultList);
				_pSoftQuery->GetNotify()->SoftQueryNotify(&softInfoEnum, _pParams);
			}
		}

		// 2.查询网络
		if(!_softQueryInfoList.empty())
		{
			if(pMgr->IsExited()) break;

			SoftInfo2List resultList;
			try{ QueryByNetwork(_softQueryInfoList, resultList); } catch(...) {}

			// 处理返回结果
			if(!resultList.empty())
			{
				if(pMgr->IsExited()) break;
				{
					CSoftInfoEnum softInfoEnum(resultList);
					_pSoftQuery->GetNotify()->SoftQueryNotify(&softInfoEnum, _pParams);
				}
				if(pMgr->IsExited()) break;

				// 保存到本地缓存
				pDB->BeginTransaction();
				{
					__time32_t now = _time32(NULL);
					CCacheSoftInfoOpr softInfoOpr(pDB);

					SoftInfo2CIter end = resultList.end();
					for(SoftInfo2CIter it = resultList.begin(); it != end; ++it)
					{
						softInfoOpr.Insert(it->_id, it->_grade, now);
					}
				}
				pDB->CommitTransaction();
			}
		}
	}
	while(FALSE);

	return FALSE;
}