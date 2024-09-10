main()
{
	unsigned int x, p, n;

	printf("�������ַ���x: ");
    scanf("%u", &x);
    printf("��������ʼλ: ");
    scanf("%d", &p);
    printf("�������滻��λ��: ");
    scanf("%d", &n);
    printf("�滻���xΪ: %u\n", invert(x, p, n));
}