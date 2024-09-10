	void Draw(UIContext &dc) {
		if (g_Config.iCurrentStateSlot == slot_) {
			dc.FillRect(UI::Drawable(0x40FFFFFF), GetBounds());
		}
		UI::LinearLayout::Draw(dc);
	}