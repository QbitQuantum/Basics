int main(){
	freopen("12207.txt", "r", stdin);
	int P, C, i, n, flag, cs=1;
	char s[6];
	while( scanf("%d%d", &P, &C) ){
		if( !P && !C )break;
		init(P);
		flag = 0;
		printf("Case %d:\n", cs++);
		for(i=1; i<=C; i++){
			scanf("%s", s);
			if(s[0] == 'N'){
				n = l.front();
				printf("%d\n", n);
				l.pop_front();
				flag = 1;
				if(flag && P<=1000)l.push_back(n);
			}else{
				scanf("%d", &n);
				l.remove(n);
				l.push_front(n);
			}
		}
		l.clear();
	}
	return 0;
}