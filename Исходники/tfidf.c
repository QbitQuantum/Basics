int main(int argc,char *argv[])
{
	int i;
	struct tuple t[NOFFILES][NOFWORDS];
	int sumoffreq[NOFFILES]; /* 빈도의 합계 */
    
	/* 명령행 인수 검사 */
	if (argc < 3) { /* 인수가 부족함 */
		fprintf(stderr, "사용법 tfidf "
                "(파일1) (파일2) ... \n");
		exit(1);
	}
	else if (argc > NOFFILES) { /* 파일이 너무 많음 */
		fprintf(stderr, "파일이 너무 많습니다(%d).\n "
				, argc);
		exit(1);
	}
    
    
	/* 파일에서 데이터 읽어오기 */
	for (i = 0; i < (argc - 1); ++i) {
		readfile(argv[i+1], t[i]);
	}
    
	/* 빈도 합계 계산 */
	for (i = 0; i < (argc - 1); ++i) {
		sumoffreq[i] = sumfreq(t[i]);
	}
    
	/* tf 값 계산 */
	for (i = 0; i < (argc - 1); ++i) {
		settf(t[i], sumoffreq[i]);
	}
    
	/* idf 값 계산 */
	for (i = 0; i < (argc - 1); ++i) {
		setidf(t, i, argc);
	}
    
	/* 파일에 데이터 기록하기 */
	for (i = 0; i < (argc - 1); ++i) {
		writefile(i, t[i]);
	}
    
	return 0;
}