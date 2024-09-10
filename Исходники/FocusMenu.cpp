/*---------------------------------------------------------------------*//**
	メニューの位置調整
**//*---------------------------------------------------------------------*/
void FocusMenu::adjustMenuPos(MenuKind mkind)
{
	// フォローなしの場合は必要なし
	if(_unitFllowRef[mkind] == 0)			{	return;	}

	do
	{
		MenuTreeNode* mtnode = _menu[mkind]->getCurrentMenuNode();
		if(mtnode == 0L)						{	break;	}
		MenuWindow* mwnd = (MenuWindow*)mtnode->getPanel();
		if(mwnd == 0L)							{	break;	}
		const RectF32* rectMwnd = mwnd->getRectangle();

		// 対象がいなくなった
		if(!_unitFllowRef[mkind]->isEnable())
		{
			break;	// メニューを閉じる
		}

		// スクリーン座標に変換
		Vector2F vScr;
		CalcUtils::calc3dPosToScreenPos(&vScr, _unitFllowRef[mkind]->getCenterPos());
		f32 x = vScr.x();
		f32 y = vScr.y();

		// ユニット自体が画面外に出たときはメニューを閉じる
		if((x < 0) || (x > Game::getGame()->getLogicalWidth()) || (y < 0) || (y > Game::getGame()->getLogicalHeight()))
		{
			break;	// メニューを閉じる
		}

		// 画面内に収めるように位置修正
		if((x + rectMwnd->w()) > Game::getGame()->getLogicalWidth())	{	x = Game::getGame()->getLogicalWidth() - rectMwnd->w();	}
		else if(x < 0)					{	x = 0;						}
		if((y + rectMwnd->h()) > Game::getGame()->getLogicalHeight())	{	y = Game::getGame()->getLogicalHeight() - rectMwnd->h();	}
		else if(y < 0)					{	y = 0;						}

		// 修正を反映
		if((x != rectMwnd->x()) || (y != rectMwnd->y()))
		{
			PointF32 pt(x, y);
			mwnd->move(&pt);
		}

		return;	// 正常終了
	}
	while(false);

	// なんらかエラーが発生したのでメニューを閉じる
	_menu[mkind]->closeMenu();
}