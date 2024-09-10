bool OnPlayerShopSubBuyNum(const CEGUI::EventArgs& e)
{
	CEGUI::Window* wnd = WEArgs(e).window;
	if(!wnd) return false;

	CEGUI::Window* goodsWnd = wnd->getParent();
	if (goodsWnd)
	{	
		CGoods* goods = static_cast<CGoods*>(goodsWnd->getUserData());
		if (!goods) return false;

		PlayerShop::tagGoodsItem* pGoodsItem = GetPlayerShop().FindtagGoods(goods);
		if (pGoodsItem!=NULL)
		{
			char str[32];
			// 取得输入框控件名
			CEGUI::String name = wnd->getName();
			name.assign(name, 0, name.find_last_of("/"));
			name += "/BuyNum";

			CEGUI::Window* buyNumWnd = GetWndMgr().getWindow(name);
			int num = atoi(buyNumWnd->getText().c_str());

			if (num<=0)
			{
				sprintf(str,"%d",0);
				wnd->disable();
			}
			else
				sprintf(str,"%d",num--);
			buyNumWnd->setText(ToCEGUIString(str));
			pGoodsItem->readyTradeNum = num;	
		}
	}

	return true;
}