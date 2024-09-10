/////////////////////////////////////////////////////////////////////////////////
// Puts an inflected multi-word form 'f' corresponding to the DELAC entry 'dlc_entry' into the DELACF format ('entry').
// The resulting enntry may takes up to 'max' characters.
// 'entry' almready has its space allocated.
// Returns 1 on error, 0 otherwise.
int DLC_format_form(struct l_morpho_t* pL_MORPHO,unichar* entry, int max, MU_f_T f, DLC_entry_T* dlc_entry,
		d_class_equiv_T* D_CLASS_EQUIV) {
	int l; //length of the entry

	//Inflected form
	l = u_strlen(f.form);
	if (l >= max)
		return 1;
	u_strcpy(entry, f.form);

	//Comma
	l++;
	if (l >= max)
		return 1;
	u_strcat(entry, ",");

	//Lemma
	int u; //index of the current unit in the lemma of the MW form
	for (u = 0; u < dlc_entry->lemma->no_units; u++)
		l = l + u_strlen(dlc_entry->lemma->units[u]->form);
	if (l >= max)
		return 1;
	for (u = 0; u < dlc_entry->lemma->no_units; u++)
		u_strcat(entry, dlc_entry->lemma->units[u]->form);

	//Full stop
	l++;
	if (l >= max)
		return 1;
	u_strcat(entry, ".");

	//Inflection paradigm
	//l = l + strlen(dlc_entry->lemma->paradigm);
	//if (l >= max) return 1;
	//u_strcat(entry,dlc_entry->lemma->paradigm);

	//Inflection class
	l = l + u_strlen(d_get_str_class(dlc_entry->lemma->cl, D_CLASS_EQUIV));
	if (l >= max)
		return 1;
	u_strcat(entry, d_get_str_class(dlc_entry->lemma->cl, D_CLASS_EQUIV));

	//Semantic codes
	int c; //index of the current semantic code
	for (c = 0; dlc_entry->codes[c]; c++)
		l = l + u_strlen(dlc_entry->codes[c]) + 1;
	if (l >= max)
		return 1;
	for (c = 0; dlc_entry->codes[c]; c++) {
		u_strcat(entry, "+");
		u_strcat(entry, dlc_entry->codes[c]);
	}

	//Inflection features
	unichar* feat; //sequence of single-letter inflection features, e.g. 'sIf'
	if (f.features && f.features->no_cats > 0) {
		feat = d_get_str_feat(pL_MORPHO,f.features);
		l = l + u_strlen(feat) + 1; //Place for a ':' and all features
		if (l >= max)
			return 1;
		u_strcat(entry, ":");
		u_strcat(entry, feat);
		free(feat);
	}

	//Comment
	if (dlc_entry->comment && u_strlen(dlc_entry->comment)) {
		l = l + u_strlen(dlc_entry->comment);//Place for a '/' and the comment
		if (l >= max)
			return 1;
		u_strcat(entry, "/");
		u_strcat(entry, dlc_entry->comment);
	}
	return 0;
}