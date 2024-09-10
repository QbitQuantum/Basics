void ColorMenuItem::Draw /*Content*/() {
float w, h;
BPoint p;
	BMenu *m = Menu();
	if (m == NULL) return;
	
	p = ContentLocation();
	GetContentSize(&w, &h);	

	rgb_color c = color;
	if (!IsEnabled()) {
		c.green = c.blue = c.red = 
			(uint8) (0.4 * c.red + 0.2 * c.blue + 0.4 * c.green);
	}

	m->SetHighColor(c);
	m->FillRect(BRect(p.x+2, p.y+2, p.x+w-2, p.y+h-2));
	
	if (IsMarked()) {
	rgb_color blue={0, 0, 255, 255};
		m->SetHighColor(blue);
		m->StrokeRect(BRect(p.x, p.y, p.x+w, p.y+h));
	}

	if (IsSelected()) {
	rgb_color red={0, 0, 255, 255};
		m->SetHighColor(red);
		m->StrokeRect(BRect(p.x, p.y, p.x+w, p.y+h));
	}
}