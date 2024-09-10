/* -------------- */
int load_font_in(char *font_path, int font_nr)
{
register int f_handle;
register long len;
register fontform *fnt_mem, *search;

f_handle = Fopen(font_path, 0);	
if (f_handle > 0)
	{
	len = Fseek(0L, f_handle, 2);
	Fseek(0L, f_handle, 0);

	pic_sub += len + 4;
	if (pic_sub & 1)
		{
		pic_sub--;
		*(long *)(mtext_mem + mtext_mlen - pic_sub) = len + 1;
		}
	else
		*(long *)(mtext_mem + mtext_mlen - pic_sub) = len;

	fnt_mem = (fontform *)(mtext_mem + mtext_mlen - pic_sub + 4);

	Fread(f_handle, len, fnt_mem);
	Fclose(f_handle);

	if ((long)fnt_point[akt_id] > 0)
		vst_unload_fonts(vdi_handle, 1);

	if ((long)fnt_point[akt_id] > 0)
		fnt_mem[0].next = fnt_point[akt_id];
	else
		fnt_mem[0].next = 0;

	fnt_point[akt_id] = fnt_mem;

	fnt_mem[0].id = 99;
	fnt_mem[0].ch_ofst = (int *)((long)fnt_mem[0].ch_ofst + (long)fnt_mem);
	fnt_mem[0].fnt_dta  = (int *)((long)fnt_mem[0].fnt_dta + (long)fnt_mem);

	remove_font(font_nr);

	fnt_mem = fnt_point[akt_id];
	fnt_mem[0].id = font_nr;

	inst_font();

	return(1);
	}

return(0);
}