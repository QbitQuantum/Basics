void CMobs::DrawStats()
{
	if (Visible)
	{
		char buf[100];
		char ultoabuf[10];
		strcpy(buf, MobName.c_str());
		strcat(buf, "\n");
		strcat(buf, "HP: ");
		strcat(buf, _ultoa(HP, ultoabuf, 10));
		strcat(buf, " / ");
		strcat(buf, _ultoa(MaxHP, ultoabuf, 10));
		strcat(buf, "\n");
		strcat(buf, "MP: ");
		strcat(buf, _ultoa(MP, ultoabuf, 10));
		strcat(buf, " / ");
		strcat(buf, _ultoa(MaxMP, ultoabuf, 10));
		strcat(buf, "\n");
		strcat(buf, "EXP: ");
		strcat(buf, _ultoa(EXPGiven, ultoabuf, 10));
		D3D.TextWorld(D3D.FrostFont, X - 10, Y - (20*4), D3DCOLOR_XRGB( 0xFF, 0xFF, 0xFF ), buf);
	}
}