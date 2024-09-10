void show_string(Array a, FILE* out) {
	fputwc(L'"', out);
	int i;
	for(i = 0; i < a.len; i++)
		show_stringed_char(a.items[i].chara, out);
	fputwc(L'"', out);
}