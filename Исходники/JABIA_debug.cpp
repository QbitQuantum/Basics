void fillDialog(HWND hwnd, JABIA_Character * ptr) {
	char buf[100];
	JABIA_Character character;
	if(ptr != NULL) {
		memcpy(&character, (void *)ptr, sizeof(JABIA_Character));		

		// address of character
		_itoa_s((uint32_t)ptr, buf, 100, 16);
		SetDlgItemText(hwnd, IDC_ADDRESS, buf);	

		_itoa_s(character.level, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_LEV, buf);

		_itoa_s(character.experience, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_EX, buf);

		_itoa_s(character.training_points, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_TP, buf);

		_itoa_s(character.inventory.weapon_in_hand, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_WPN_EQ, buf);

		_itoa_s(character.inventory.weapon_in_hand_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_WPN_EQ_DUR, buf);

		_itoa_s(character.inventory.helmet_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_HELM_EQ, buf);

		_itoa_s(character.inventory.helmet_equiped_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_HELM_EQ_DUR, buf);

		_itoa_s(character.inventory.eyewear_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_EYE_EQ, buf);

		_itoa_s(character.inventory.eyewear_equiped_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_EYE_EQ_DUR, buf);

		_itoa_s(character.inventory.special_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_SPC_EQ, buf);

		_itoa_s(character.inventory.special_equiped_charges, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_SPC_EQ_LEFT, buf);

		_itoa_s(character.inventory.shirt_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_SHRT_EQ, buf);

		_itoa_s(character.inventory.shirt_equiped_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_SHRT_EQ_DUR, buf);

		_itoa_s(character.inventory.vest_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_VEST_EQ, buf);

		_itoa_s(character.inventory.vest_equiped_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_VEST_DUR, buf);

		_itoa_s(character.inventory.shoes_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_SHOES_EQ, buf);

		_itoa_s(character.inventory.shoes_equiped_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_SHOES_DUR, buf);

		_itoa_s(character.inventory.pants_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_PANTS_EQ, buf);

		_itoa_s(character.inventory.pants_equiped_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_PANTS_DUR, buf);

		_itoa_s(character.inventory.ammo_equiped, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_AMMO_EQ, buf);

		_itoa_s(character.inventory.ammo_equiped_count, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_AMMO_EQ_CNT, buf);

		_itoa_s(character.inventory.ammo_equiped_count, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_AMMO_EQ_CNT, buf);

		_itoa_s(character.inventory.weapon_attachment_removable, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_WPN_MOD, buf);

		// health and stamina 	
		sprintf_s(buf, "%.1f", character.health, 4);
		//OutputDebugString(buf);
		SetDlgItemText(hwnd, IDC_HLTH, buf);

		sprintf_s(buf, "%.1f", character.stamina, 4);
		SetDlgItemText(hwnd, IDC_STAMINA, buf);

		// name
		memset(buf, 0x00, 16);
		memcpy(buf, character.merc_name, character.name_length);
		SetDlgItemText(hwnd, IDC_MERC_NAME, buf);

		_itoa_s(character.faction, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_MERC_FAC, buf);

		_itoa_s(character.medical_condition, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_MED_COND, buf);

		// inventory
		_itoa_s(character.inventory.weapons[last_weaponslot_selected_index].weapon, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_WPN_INV, buf);

		_itoa_s(character.inventory.weapons[last_weaponslot_selected_index].weapon_durability, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_WPN_INV_DUR, buf);

		_itoa_s(character.inventory.weapons[last_weaponslot_selected_index].ammo_count, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_AMMO_INV_CNT, buf);

		_itoa_s(character.inventory.inventory_items[last_inventory_selected_index].item_id, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_INV_ITEM_ID, buf);

		// attributes
		_itoa_s(character.agility, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_AG, buf);

		_itoa_s(character.dexterity, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_DEX, buf);

		_itoa_s(character.strength, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_STR, buf);

		_itoa_s(character.intelligence, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_INT, buf);

		_itoa_s(character.perception, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_PER, buf);

		// skills

		_itoa_s(character.medical, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_MED, buf);

		_itoa_s(character.explosives, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_EXPL, buf);

		_itoa_s(character.marksmanship, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_MARK, buf);

		_itoa_s(character.stealth, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_STEALTH, buf);

		_itoa_s(character.mechanical, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_MECH, buf);

		_itoa_s(character.bleed_rate, buf, 100, 10);
		SetDlgItemText(hwnd, IDC_BLEED_RATE, buf);
	}	
}