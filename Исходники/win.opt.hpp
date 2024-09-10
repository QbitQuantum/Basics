	void reflowStatic() {
		tabMain.append("OPN");
			tabMain.setLayout(0, ltOPN);
			frTogglesOPN.setLayout(lTogglesOPN);
			ltOPN.append(frTogglesOPN, {~0,~0}, 5);
			ltOPN.append(lOPN2, {~0,~0});
		tabMain.append("OPM");
			tabMain.setLayout(1, ltOPM);
			frTogglesOPM.setLayout(lTogglesOPM);
			ltOPM.append(frTogglesOPM, {~0,~0}, 5);
			ltOPM.append(lOPM2, {~0,~0});
	}