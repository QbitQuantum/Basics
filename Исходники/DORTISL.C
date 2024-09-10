void _cikarma(char *sayi1, char *sayi2, char *sonuc)
{
	char *s1, *s2;
	int elde = 0, kontrol, i, sayi_uzunlugu;

	sayi_uzunlugu = sayi_esitle(sayi1, sayi2);
	kontrol = strlen(sayi2);
	if ((sayi_kontrol(sayi1, sayi2) > 0)) {
		s1 = sayi1; s2 = sayi2;
	}
	else {
		s1 = sayi2; s2 = sayi1;
	}
	strrev(s1);
	strrev(s2);

	memset(sonuc, 0, kontrol+1);
	for (i = 0; i < kontrol; i++) {
		if (s1[i] < s2[i]) {
			if (s1[i+1] == 0) {
				s1[i+1] = 9;
			}
			else
				s1[i+1]--;
			elde = s1[i] + 10;
			sonuc[i] = (elde - s2[i]) + '0';
		}
		else
			sonuc[i] = (s1[i] - s2[i]) + '0';
	}
	strrev(sonuc);
	strrev(s1);
	strrev(s2);
	sayi_temizle(sonuc, sayi_uzunlugu);
	sayi_temizle(s1, sayi_uzunlugu);
	sayi_temizle(s2, sayi_uzunlugu);
}