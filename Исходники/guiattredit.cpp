void GUIAttrEdit::handleMsg( ZMsg *msg ) {
	float lineH = getLineH();

	int scroll = getAttrI( "scroll" );

	float x = zmsgF(localX);
	float y = zmsgF(localY);

	if( zmsgIs(type,Key) && zmsgIs(which,wheelforward) ) {
		if( contains(x,y) ) {
			scroll-=2;
			scroll = max( -10, scroll );
			scroll = min( view.count-5, scroll );
			setAttrI( "scroll", scroll );
			mouseOver = (int)( (myH-y) / lineH );
			mouseOver += scroll;
			mouseOver = selected > view.count-1 ? view.count-1 : mouseOver;
			zMsgUsed();
		}
	}
	else if( zmsgIs(type,Key) && zmsgIs(which,wheelbackward) ) {
		if( contains(x,y) ) {
			scroll+=2;
			scroll = max( -10, scroll );
			scroll = min( view.count-5, scroll );
			setAttrI( "scroll", scroll );
			mouseOver = (int)( (myH-y) / lineH );
			mouseOver += scroll;
			mouseOver = selected > view.count-1 ? view.count-1 : mouseOver;
			zMsgUsed();
		}
	}
	else if( zmsgIs(type,MouseMove) ) {
		mouseOver = (int)( (myH-y) / lineH );
		mouseOver += scroll;
		mouseOver = selected > view.count-1 ? view.count-1 : mouseOver;
	}

	else if( zmsgIs(type,MouseClickOn) && zmsgIs(dir,D) && zmsgI(ctrl) && zmsgI(shift) ) {
		//ADJUST the linIncrement
		if( zmsgIs(which,L) ) {
			linIncrement *= 2.f;
		}
		else if( zmsgIs(which,R) ) {
			linIncrement /= 2.f;
		}
	}
	else if( zmsgIs(type,MouseClickOn) && zmsgIs(dir,D) && zmsgIs(which,L) ) {
		selected = (int)( (myH-y) / lineH );
		selected += scroll;
		selected = selected > view.count-1 ? view.count-1 : selected;

		ZHashTable *hash = (ZHashTable *)getAttrp( "hashPtr" );
		if( !hash ) return;
		char *val = hash->getS( view[selected] );

		char *end;
		double valD = strtod( val, &end );
		if( end != val ) {
			// This is a number that can be manipulated

//			if( zmsgI(shift) && !zmsgI(ctrl) ) {
//				linMode = 0;
//				zMsgQueue( "type=GUIAttrEdit_CreateOptionMenu key=%s val=%lf toGUI=%s", selectVarPtr->name, selectVarPtr->getDouble(), getAttrS("name") );
//			}
//			else {
				if( zmsgI(ctrl) && !zmsgI(shift) ) {
					linMode = 1;
				}
				else {
					linMode = 0;
				}
				selectX = x;
				selectY = y;
				mouseX = x;
				mouseY = y;
				startVal = valD;
				requestExclusiveMouse( 1, 1 );
//			}
		}
		else {
			selected = -1;
		}


/*
		ZVarPtr *selectVarPtr = getSelectedVar( selected );
		if( selectVarPtr ) {
			if( zmsgI(shift) && !zmsgI(ctrl) ) {
				linMode = 0;
				zMsgQueue( "type=GUIAttrEdit_CreateOptionMenu key=%s val=%lf toGUI=%s", selectVarPtr->name, selectVarPtr->getDouble(), getAttrS("name") );
			}
			else {
				if( zmsgI(ctrl) && !zmsgI(shift) ) {
					linMode = 1;
				}
				else {
					linMode = 0;
				}
				selectX = x;
				selectY = y;
				mouseX = x;
				mouseY = y;
				switch( selectVarPtr->type ) {
					case zVarTypeINT:    startVal = (double)*(int    *)selectVarPtr->ptr + 0.4; break;
					case zVarTypeSHORT:  startVal = (double)*(short  *)selectVarPtr->ptr + 0.4; break;
					case zVarTypeFLOAT:  startVal = (double)*(float  *)selectVarPtr->ptr; break;
					case zVarTypeDOUBLE: startVal = (double)*(double *)selectVarPtr->ptr; break;
				}
				requestExclusiveMouse( 1, 1 );
			}
		}
*/
		zMsgUsed();
		return;
	}
	else if( zmsgIs(type,MouseReleaseDrag) ) {
		if( selected >= 0 ) {
//			ZVarPtr *selectVarPtr = getSelectedVar( selected );
//			if( selectVarPtr ) {
//				zMsgQueue( "type=GUIAttrEdit_VarDoneChange key=%s val=%lf", selectVarPtr->name, selectVarPtr->getDouble() );
//			}
		}

		requestExclusiveMouse( 1, 0 );
		selected = -1;
		zMsgUsed();
		return;
	}
	else if( zmsgIs(type,MouseDrag) && zmsgI(l) ) {
		int last = -1;
		int count = 0;
		//while( count++ != selected+1 && zVarsEnum( last, selectVarPtr, regExp ) );

		ZHashTable *hash = (ZHashTable *)getAttrp( "hashPtr" );
		double val = hash->getD( view[selected] );
		mouseX = x;
		mouseY = y;
		if( linMode ) {
			val = startVal + (mouseY-selectY) * linIncrement;
		}
		else{
			val = startVal * exp( (mouseY-selectY) / 50.0 );
		}
		hash->putS( view[selected], ZTmpStr("%4.3le",val) );
	}
	else if( zmsgIs(type,MouseClickOn) && zmsgIs(dir,D) && zmsgIs(which,R) ) {
		selectX = x;
		selectY = y;
		startScroll = scroll;
		requestExclusiveMouse( 1, 1 );
		zMsgUsed();
		return;
	}
	else if( zmsgIs(type,MouseDrag) && zmsgI(r) ) {
		scroll = (int)( startScroll + ( y - selectY ) / lineH );
		scroll = max( -10, scroll );
		scroll = min( view.count-5, scroll );
		setAttrI( "scroll", scroll );
	}
	else if( zmsgIs(type,GUIAttrEdit_Clear) ) {
		clearView();
	}
//	else if( zmsgIs(type,GUIAttrEdit_Add) ) {
//		if( zmsgHas(regexp) ) {
//			addVarsByRegExp( zmsgS(regexp) );
//		}
//		else if( zmsgHas(name) ) {
//			addVar( zmsgS(name) );
//		}
//	}
	else if( zmsgIs(type,GUIAttrEdit_Sort) ) {
		if( zmsgIs(which,name) ) {
			sortViewByName();
		}
//		else if( zmsgIs(which,order) ) {
//			sortViewByDeclOrder();
//		}
	}
	else if( zmsgIs(type,GUIAttrEdit_CreateOptionMenu) ) {
		ZHashTable hash;
		hash.putS( "who", getAttrS("name") );
		hash.putS( "key", zmsgS(key) );
		hash.putS( "val", ZTmpStr("%1.2e", zmsgF(val)) );
		createOptionMenu( &hash );
		optMenuUp = 1;
		zMsgQueue( "type=GUILayout toGUI=varEditOptMenu" );
		zMsgQueue( "type=GUIMoveNear who=%s where=T x=4 y=%f toGUI=varEditOptMenu", getAttrS("name"), -(mouseOver-scroll)*lineH );
		zMsgQueue( "type=GUISetModal val=1 toGUI=varEditOptMenu" );
	}
	else if( zmsgIs(type,GUIAttrEdit_CreateOptionMenuDone) ) {
		optMenuUp = 0;
		selected = -1;
	}
	else if( zmsgIs(type,GUIAttrEdit_CreateOptionMenuDirectEntry) ) {
		GUIObject *obj = guiFind( zmsgS(fromGUI) );
		if( obj ) {
			zMsgQueue( "type=SetVar key=%s val=%f", zmsgS(key), atof(obj->getAttrS("text")) );
		}
	}
//	else if( zmsgIs(type,GUIAttrEdit_ResetAll) ) {
//		for( int i=0; i<view.count; i++ ) {
//			ZVarPtr *v = zVarsLookup( varsView.vec[i] );
//			v->resetDefault();
//		}
//	}
	else if( zmsgIs(type,GUIAttrEdit_Clear) ) {
		clearView();
	}
	else if( zmsgIs(type,GUIAttrEdit_Add) ) {
		addVar( zmsgS(key) );
	}
	else if( zmsgIs(type,GUIAttrEdit_ViewAll) ) {
		if( zmsgI(clear) ) {
			clearView();
		}
		addAllVars();
	}
	GUIPanel::handleMsg( msg );
}