	Mtorz() {
		setBackground(osapal[8]);
		setBounds(200, 64, 14 * 8 + 12, 4 * 16 + 28);
		setTitle("M t . o r z 0");
		label1 = new Label(
			"　　　orz\n"
			"　　orz orz\n"
			"　orz orz orz\n"
			"orz orz orz orz");
		label1->setBounds(20, 8, 12 * 8, 3 * 16);
		label1->setBackground(osapal[8]);
		add(label1);
		setTimer(500);
	}