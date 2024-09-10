//=============================================================================
//フラッシュを浴びた状態の処理
//=============================================================================
void CDraw3DObject::FlashedState(  )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->GetObjectType() == OBJ_ENEMY )
		{
			pChara->FlashedState();
		}	
	}
}