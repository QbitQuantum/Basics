	//////////////////////////////////////////////////////////////////////////
	//
	// Class MemoryViewDebugger
	// 
	// 罗嘉飞  2011、5、26  内存显示
	//
	void MemoryViewDebugger::Debug( VCPU* pCPU, LPVOID param )
	{
		auto IR = pCPU->GetIR();
		if ( IR->m_elements[ 0 ] == "leave" )  {flag = 0; m_funcId.pop();}
		else if ( IR->m_elements[ 0 ] == "mov" && IR->m_elements[ 1 ] == "d1" ) {flag = 1;m_funcId.push( pCPU->Getdreg()[ 1 ] );}

		if ( !m_funcId.empty() ) 
		{
			if ( m_funcId.top()  !=  pCPU->Getdreg()[ 1 ] ) 
				flag = 1;
		}
		if ( flag == 1 )
		{
			// 获取语法器
			IParser* pParser = (IParser*)m_callBack( NULL );
			// 获取符号表
			Environment& env = (Environment)pParser->GetTables();

			MemorySpy* pProWnd = *(MemorySpy**)( m_callBack( (LPVOID)1 ) );

			dword_pointer pebp = pCPU->Getebp();

			dword_pointer pesp = pCPU->Getesp();

			dword eip = pCPU->Geteip();

			//dword c=*(pebp+8);
			//dword d=*(pesp+8);

			//////////////////



			PropertiesInsertItem temp;
			WatchPropertiesListType* ValList = new std::list< PropertiesInsertItem >;


			//////////////////////
			DWORD pc = pCPU->Geteip();	// PC

			/*dword func_id = pCPU->Getdreg()[ 1 ];*/

			dword func_id = m_funcId.top();    //每次都去栈顶

			//m_funcId.push(func_id);

			Table* table;

			auto iter=env.m_tableList.begin();

			for (;iter!=env.m_tableList.end();iter++) 
			{
				if( iter->second.GetID()==func_id)
				{
					break;
				}
			}

			if ( iter == env.m_tableList.end() )	return;

			table = &iter->second;
			/*(table)->m_symbolList;*/

			for ( auto symbol = table->GetLocalVarTable().begin(); symbol != table->GetLocalVarTable().end(); ++symbol )
			{
				temp.varname=symbol->second.name;
				temp.val=*(dword_pointer)( ((uchar_pointer)pebp) - symbol->second.offset);
				ValList->push_back(temp);
			}

			/*table->m_paramSymbolList;*/
			for ( auto symbol = table->GetParamTable().begin(); symbol != table->GetParamTable().end(); ++symbol )
			{
				temp.varname=symbol->second.name;
				temp.val=*(dword_pointer)( ((uchar_pointer)pebp) - symbol->second.offset + 4);
				ValList->push_back(temp);
			}

			if ( listComp != *ValList )
			{

				listComp = *ValList;
				//pProWnd->PostMessageA( WM_CLEAR_ALL_ITEMS );
				pProWnd->PostMessageA( WM_INSERT_ITEM, (WPARAM)ValList, 0 );
			}
			else
			{
				delete ValList;
			}
			
		}
	}