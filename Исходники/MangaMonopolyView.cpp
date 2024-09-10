void CMangaMonopolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMangaMonopolyDoc* pDoc = GetDocument();
	if(pDoc->now_state == CPublic::WAIT_DICE) // Ready to go
	{
		if(point.x >= 250 && point.x <= 250 + dice.GetWidth() && point.y >= 250 && point.y <= 250 + dice.GetHeight() )
		{
			int step1 = rand()%6+1;
			int step2 = rand()%6+1;
			int step = step1 + step2;

			CDC* dc = GetDC();
			CFont font;
			font.CreatePointFont(120, L"微软雅黑", dc);
			dc->SelectObject(font);
			
			string_buffer.Format(L"投出了 %d 点！", step);
			dc->TextOutW(248, 403, string_buffer);
			font.DeleteObject();
			dc->DeleteDC();
			
			pDoc->ChangeState(CPublic::WAIT_WALK);
			Sleep(500);
			dc = GetDC();
			int i;
			for(i=1;i<=step;i++)
			{
				Sleep(100);
			    pDoc->MovePlayerOnce();
				OnDraw(dc);
			}
			dc->DeleteDC();
			/////////////////////////////////////////////////// Event Handling

			int now_player= pDoc->now_player;

			CPanel now_panel = pDoc->GetNowPanel();

			//1. If it is a buyable panel
			if( pDoc->Buyable() )
			{
				if(now_panel.occupied == false) //buy
				{
					if( pDoc->CanBuy() ) // can buy
					{
						CAskDialog ask_buy_dialog;
						ask_buy_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::BUY);
						if( ask_buy_dialog.DoModal()  == IDOK)
						{
							pDoc->Buy();
						}
					}
					else //no money to buy
					{
						CNoMoneyDialog no_money_dialog;
						no_money_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::BUY);
						no_money_dialog.DoModal();
					}
				}

				else if(now_panel.occupied == true && now_panel.owner != now_player) // buzz
				{
					CPenaltyDialog penalty_dialog;
					penalty_dialog.SetInfo(now_panel.name, now_panel.price * now_panel.level, now_panel.owner, CPublic::GIVE);
					penalty_dialog.DoModal();
					pDoc->GiveMoney(now_panel.price * now_panel.level, now_panel.owner);
				}
				else if(now_panel.occupied == true && now_panel.owner == now_player) //upgrade
				{
					if( pDoc->CanUpgrade() ) 
					{
						CAskDialog ask_upgrade_dialog;
						ask_upgrade_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::UPGRADE);
						if ( ask_upgrade_dialog.DoModal() == IDOK )
						{
							pDoc->Upgrade();
						}
					}
					else
					{
						CNoMoneyDialog no_money_up_dialog;
						no_money_up_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::UPGRADE);
						no_money_up_dialog.DoModal();
					}
				}
			}

			//2. if it is a penalty panel
			else if( pDoc->isTax() )
			{
	            CPenaltyDialog penalty_dialog;
				penalty_dialog.SetInfo(now_panel.name, now_panel.price, now_panel.owner, CPublic::TAX);
				penalty_dialog.DoModal();
				pDoc->CutMoney(CPublic::TAX_MONEY);
			}

			pDoc->RefreshMoney();
			if(pDoc->KnockOut())
			{
				CString s;
				s.Format(L"玩家%d破产了！", pDoc->now_player);
				MessageBox(s);
				pDoc->DeletePlayer();
				if(pDoc->rest_num == 1)
				{
					int last_player;
					last_player = pDoc->GetLastPlayer();
					CString victory_message;
					victory_message.Format(L"恭喜玩家%d取得了最后的胜利！", last_player);
					MessageBox(victory_message);
					pDoc->ChangeState(CPublic::GAME_OVER);
				}
			}

			/////////////////////////////Refresh Screen

			dc = GetDC();
			OnDraw(dc);

			///////////////////////////Ready for next
			Sleep(500);
			if(pDoc->now_state == CPublic::WAIT_WALK)
			{
				pDoc->ChangeState(CPublic::WAIT_DICE);
				pDoc->NextPlayer();
			}
			
			dc = GetDC();
			OnDraw(dc);

			//////////////////////////////////End
			dc->DeleteDC();
		}

		pDoc->SetModifiedFlag();
	}

	CView::OnLButtonDown(nFlags, point);
}