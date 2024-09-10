	void UIColorPicker::Update() {
		if (!this->HasFocus() || (!this->pm_bIsBragging && !this->pm_bIsBraggingAlpha)) return;

		Vector2 mp = this->UIMan->LastMousePosition - this->GetAbsoluteLocation();

		float mdist = mp.Distance(this->pm_vCenter);
		if (mdist >= this->W / 2 - BorderSize && mdist <= this->W / 2) {
			this->pm_fHue = (float)((int)(-atan2(mp.X - (float)this->W / 2, (float)this->H / 2 - mp.Y) * (float)(180.0 / M_PI) + 180) % 360);
		} else {
			if (mp.X >= this->BorderSize * 3 + +this->Padding && mp.Y >= this->BorderSize * 3 + this->Padding && mp.X <= this->W - this->BorderSize * 3 - this->Padding  && mp.Y <= this->H - this->BorderSize * 3 - this->Padding) {
				Vector2 tmp = mp;
				tmp -= (float)this->BorderSize * 3 + this->Padding;

				this->pm_vsat.X = Utilities::Clamp(tmp.X / (float)(this->W - this->BorderSize * 6 - this->Padding * 2), 0.0f, 1.0f);
				this->pm_vsat.Y = Utilities::Clamp(1 - (tmp.Y / (float)(this->H - this->BorderSize * 6 - this->Padding * 2)), 0.0f, 1.0f);
			}
		}

		Color oldval = this->Value;
		this->Value = HSVtoRGB(this->pm_fHue, this->pm_vsat.X, this->pm_vsat.Y);

		if (this->Value != oldval) {
			if (this->OnValueChanged != nullptr) this->OnValueChanged();
			this->MarkForFullRedraw();
		}
	}