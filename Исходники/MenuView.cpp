void
MenuView::DrawMenu(int mx, int my, Menu* m)
{
	if (m) {
		MenuItem*   locked_item = 0;
		Menu*       submenu     = 0;
		int         subx        = 0;
		int         suby        = 0;
		Font*       font        = FontMgr::Find("HUD");

		Rect menu_rect(mx, my, 100, m->NumItems() * 10 + 6);

		int max_width     = 0;
		int max_height    = 0;
		int extra_width   = 16;

		ListIter<MenuItem> item = m->GetItems();
		while (++item) {
			menu_rect.w = width/2;

			if (item->GetText().length()) {
				window->SetFont(font);
				window->DrawText(item->GetText(), 0, menu_rect, DT_LEFT|DT_SINGLELINE|DT_CALCRECT);
				if (menu_rect.w > max_width)
				max_width = menu_rect.w;
				max_height += 11;

				if (item->GetSubmenu())
				extra_width = 28;

				if (item->GetSelected() > 1)
				locked_item = item.value();
			}
			else {
				max_height += 4;
			}
		}

		menu_rect.h = max_height + 6;
		menu_rect.w = max_width  + extra_width;

		if (menu_rect.x + menu_rect.w >= width)
		menu_rect.x = width - menu_rect.w - 2;

		if (menu_rect.y + menu_rect.h >= height)
		menu_rect.y = height - menu_rect.h - 2;

		window->FillRect(menu_rect, back_color * 0.2);
		window->DrawRect(menu_rect, back_color);

		Rect item_rect = menu_rect;

		item_rect.x += 4;
		item_rect.y += 3;
		item_rect.w -= 8;
		item_rect.h = 12;

		item.reset();
		while (++item) {
			int line_height = 0;

			if (item->GetText().length()) {
				Rect fill_rect = item_rect;
				fill_rect.Inflate(2,-1);
				fill_rect.y -= 1;

				int mx = Mouse::X() - offset.x;
				int my = Mouse::Y() - offset.y;

				// is this item picked?
				if (menu_rect.Contains(mx, my)) {
					if (my >= fill_rect.y && my <= fill_rect.y+fill_rect.h) {
						if (Mouse::LButton()) {
							menu_item = item.value();
							item->SetSelected(2);
							if (locked_item && locked_item->GetMenu() == m)
							locked_item->SetSelected(0);
							locked_item = menu_item;
						}
						else if (!locked_item || locked_item->GetMenu() != m) {
							item->SetSelected(true);
							menu_item = item.value();
						}

						if (menu_item && menu_item != selected) {
							selected = menu_item;
							Button::PlaySound(Button::SND_MENU_HILITE);
						}
					}
					else if (item.value() != locked_item) {
						item->SetSelected(false);
					}
				}

				if (item->GetSelected()) {
					window->FillRect(fill_rect, back_color * 0.35);
					window->DrawRect(fill_rect, back_color * 0.75);

					if (item->GetSubmenu()) {
						submenu  = item->GetSubmenu();
						subx     = menu_rect.x + max_width + extra_width;
						suby     = fill_rect.y - 3;
					}
				}

				if (item->GetEnabled())
				font->SetColor(text_color);
				else
				font->SetColor(text_color * 0.33);

				window->SetFont(font);
				window->DrawText(item->GetText(), 0, item_rect, DT_LEFT|DT_SINGLELINE);
				line_height = 11;
			}
			else {
				window->DrawLine(item_rect.x,
				item_rect.y + 2,
				item_rect.x + max_width + extra_width - 8,
				item_rect.y + 2,
				back_color);
				line_height = 4;
			}

			if (item->GetSubmenu()) {
				int left = item_rect.x + max_width + 10;
				int top  = item_rect.y + 1;

				// draw the arrow:
				POINT arrow[3];

				arrow[0].x = left;
				arrow[0].y = top;
				arrow[1].x = left + 8;
				arrow[1].y = top  + 4;
				arrow[2].x = left;
				arrow[2].y = top  + 8;

				window->FillPoly(3, arrow, back_color);
			}

			item_rect.y += line_height;
		}

		if (submenu) {
			if (subx + 60 > width)
			subx = menu_rect.x - 60;

			DrawMenu(subx, suby, submenu);
		}
	}
}