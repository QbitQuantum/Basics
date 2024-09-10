	SIC_Font(EscValue& v) {
		v.Escape("Height(h)", this, THISBACK(Height));
		v.Escape("Bold(...)", this, THISBACK(Bold));
		v.Escape("Italic(...)", this, THISBACK(Italic));
		v.Escape("Underline(...)", this, THISBACK(Underline));
	}