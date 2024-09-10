void dosyala(char *dosya_adi, char *alan)
{
	FILE *fp;

	if ((fp = _fsopen(dosya_adi, "rb+", SH_DENYNO)) == NULL) {
		msj_kutu(NULL, "Disk kay�t hatas�", HATA);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	fwrite(alan, 1, 4920, fp);
	fclose(fp);
}