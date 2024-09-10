//在缓存中使用矩形查询
void CFeatureEditCache::QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,boost::dynamic_bitset<> &flags)
{
	using std::set;
	using namespace GEOMETRY::geom;
	//已经处理过的要素id
	std::set<long> ProcessList;

	long fid;
	Envelope  extent;
	Geometry *pGeometry;
	for(long i=m_lCursor;i>=0;i--)
	{
		fid =m_operationStack[i]->Fid;
		//首先查看这个要素是否已经被处理了
		if(ProcessList.find(fid)!=ProcessList.end())
		{
			continue;
		}

		//如果要素被删除了
		if(m_operationStack[i]->EditType==OP_DELETE)
		{
			flags[fid-1] =false;


		}
		else
		{
			pGeometry =m_operationStack[i]->pFeature->GetShape();
			if(!pGeometry)
			{
				continue;
			}
			extent =*(pGeometry->getEnvelopeInternal());
			//如果图形和矩形不想交
			if(!extent.intersects(pEnvelop))
			{
				flags[fid-1] =false;
			}
			else
			{
				flags[fid-1] =true;
			}

		}
		ProcessList.insert(fid);


	}

}