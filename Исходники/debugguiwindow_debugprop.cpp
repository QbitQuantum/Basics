	void DebugGuiWindowDebugProp::create( DebugGui& debugGui )
	{
		m_inputAction	= InputAction_Invalid;
		m_inputTimer	= 0.0;
		m_holdTimer		= 0.0;
		m_pInputNode	= nullptr;
		m_pSelectedNode	= nullptr;

		m_baseLayout.create();
		m_baseLayout.setExpandChildren( false );

		DebugGuiWindow::create( debugGui, "Debug Properties", m_baseLayout );

		LinkedList< DebugProp >& debugProperties = debugprop::getProperties();

		SizedArray<string> folderNames;
		folderNames.create( debugProperties.getCount() * 5u );

		for (DebugProp& prop : debugProperties)
		{
			string pathName;
			pathName += prop.getModule();
			pathName += "/";
			pathName += prop.getFullName();
			pathName = pathName.toLower();

			int currentIndex = 0;
			while ( currentIndex < (int)pathName.getLength() )
			{
				int nextIndex = pathName.indexOf( '/', currentIndex );
				if ( nextIndex == -1 )
				{
					break;
				}

				const string folderName = pathName.subString( 0, nextIndex );
				if ( folderNames.getIndexOf( folderName ) == TIKI_SIZE_T_MAX )
				{
					folderNames.push( folderName );
				}

				currentIndex = nextIndex + 1;
			}

		}

		m_folderNodes.create( folderNames.getCount() );
		m_propNodes.create( debugProperties.getCount() );

		for (uint folderIndex = 0u; folderIndex < m_folderNodes.getCount(); ++folderIndex)
		{
			const string& name = folderNames[ folderIndex ];
			TreeFolderNode& node = m_folderNodes[ folderIndex ];

			node.id		= folderIndex;
			node.type	= TreeNodeType_Folder;

			int lastIndex = name.lastIndexOf( '/' ) + 1;
			const string nodeName = name.subString( lastIndex, name.getLength() - lastIndex );

			node.fullLayout.create();
			node.nodeLayout.create();
			node.spaceLayout.create();
			node.chilrenLayout.create();

			setLayoutParameters( node.fullLayout );
			setLayoutParameters( node.nodeLayout );
			setLayoutParameters( node.spaceLayout );
			setLayoutParameters( node.chilrenLayout );

			node.expandButton.create( "+" );
			node.nameLabel.create( nodeName.cStr() );

			node.nodeLayout.addChildControl( &node.expandButton );
			node.nodeLayout.addChildControl( &node.nameLabel );

			node.spacer.create( vector::create( 25.0f, 0.0f ) );

			node.spaceLayout.addChildControl( &node.spacer );
			node.spaceLayout.addChildControl( &node.chilrenLayout );

			node.fullLayout.addChildControl( &node.nodeLayout );
			node.fullLayout.addChildControl( &node.spaceLayout );

			node.parentIndex = TIKI_SIZE_T_MAX;
			if ( lastIndex == 0 )
			{
				m_baseLayout.addChildControl( &node.fullLayout );
			}
			else
			{
				const string parentName = name.subString( 0, lastIndex - 1 );
				for (uint parentIndex = 0u; parentIndex < folderIndex; ++parentIndex)
				{
					if ( folderNames[ parentIndex ] == parentName )
					{
						node.parentIndex = parentIndex;
					}
				}
				TIKI_ASSERT( node.parentIndex != TIKI_SIZE_T_MAX );
			}
		}

		uint propIndex = 0;
		for (DebugProp& prop : debugProperties)
		{
			TreePropNode& node = m_propNodes[ propIndex ];

			node.id			= propIndex;
			node.type		= TreeNodeType_Property;
			node.pProperty	= &prop;

			node.nodeLayout.create();
			setLayoutParameters( node.nodeLayout );

			node.nameLabel.create( prop.getName() );
			node.valueAlignment.create( DebugGuiAlignment::OrientationFlags_X, vector::create( 400.0f, 0.0f ) );
			setDebugPropText( node.valueLabel, prop );

			node.nodeLayout.addChildControl( &node.nameLabel );
			node.nodeLayout.addChildControl( &node.valueAlignment );
			node.nodeLayout.addChildControl( &node.valueLabel );

			string pathName;
			pathName += prop.getModule();
			pathName += "/";
			pathName += prop.getFullName();
			pathName = pathName.toLower();
			pathName = pathName.subString( 0, pathName.lastIndexOf( '/' ) );

			node.parentIndex = TIKI_SIZE_T_MAX;
			for (uint parentIndex = 0u; parentIndex < m_folderNodes.getCount(); ++parentIndex)
			{
				if (folderNames[ parentIndex ] == pathName )
				{
					node.parentIndex = parentIndex;
				}
			}
			TIKI_ASSERT( node.parentIndex != TIKI_SIZE_T_MAX );

			propIndex++;
		}

		folderNames.dispose();

		setRectangle( Rectangle( 20.0, 40.0f, 200.0f, 400.0f ) );
	}