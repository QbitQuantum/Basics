		void Label_SetTextColor(Gwen::Controls::Label& label, const argb_color& value)
		{
			label.SetTextColor(Gwen::Color(value.red, value.green, value.blue, value.alpha));
			label.SetTextColorOverride(Gwen::Color(value.red, value.green, value.blue, value.alpha));
		}