void makeTestQuery(QUERY_TYPE qt, char *query)
{
	switch(qt)
	{
	case Q_POINT_SELECTION:
		{
			int a=RAND(TEST_MAX);
			//cout<<"point: "<<a<<endl;
			sprintf(query, "PRO;R;$;R.a00,;$;:SEL;R;$;R.a00,;=,R.a00,$,$,%d,$,$,;:$:$:$:", a);
		}break;
	case Q_RANGE_SELECTION:
		{
			int a=RAND(TEST_MAX);
			int b=RAND(TEST_MAX);
			int minmin=min(a,b);
			int maxmax=minmin+20000000;//max(a,b);
			//result: 155943, 10000000
			//result: 311916, 20000000
			//cout<<"range: ["<<minmin<<", "<<maxmax<<"]"<<endl;
			sprintf(query, "PRO;R;$;R.a00,;$;:SEL;R;$;R.a00,;AND,>,R.a00,$,$,%d,$,$,<,R.a00,$,$,%d,$,$,;:$:$:$:", minmin, maxmax);
		}break;
	case Q_AGG:
		{
			sprintf(query, "AGG;R;MAX;R.a00,;$;:$:$:");
		}break;
	case Q_ORDERBY:
		{
			sprintf(query, "AGG;R;MAX;R.a00,;$;:ORD;R;$;R.a00,;$;:$:$:$:");
			//sprintf(query, "PRO;$;$;R.b00,;$;:ORD;R;$;R.a00,;$;:$:$:$:");
			//sprintf(query, "PRO;R;$;R.b00,;$;:ORD;R;$;R.a00,;$;:SEL;R;$;R.b00,;<,R.b00,$,$,8,$,$,;:$:$:$:$:");
		}break;
	case Q_AGG_GROUPBY:
		{
			sprintf(query, "AGG;R;MAX;R.a00,;$;:GRP;R;$;R.b00,;$;:$:$:$:");
		}break;
	case Q_NINLJ:
		{
			//sprintf(query, "JOIN;R;S;R.a00,S.a00,;<,R.a00,$,$,S.a00,$,$,;:$:$:");
			/*int a1=RAND(TEST_MAX);
			int a2=RAND(TEST_MAX);
			int minmin1=a1;
			int maxmax1=minmin1+20000000;//max(a,b);
			int minmin2=a2;
			int maxmax2=minmin2+20000000;//max(a,b);
			sprintf(query, "PRO;R;$;R.a00,;$;:JOIN;R;S;R.a00,S.a00,;<,R.a00,$,$,S.a00,$,$,;:SEL;R;$;R.a00,;AND,>,R.a00,$,$,%d,$,$,<,R.a00,$,$,%d,$,$,;:$:$:SEL;S;$;S.a00,;AND,>,S.a00,$,$,%d,$,$,<,S.a00,$,$,%d,$,$,;:$:$:$:",minmin1,maxmax1,minmin2,maxmax2);*/
			//cout<<"I have changed the NLJ for testing"<<endl;
			int a1=RAND(TEST_MAX);
			int a2=RAND(TEST_MAX);
			int delta=(int)(20*1000000.0);
			int minmin1=a1;
			int maxmax1=minmin1+delta;//max(a,b);
			int minmin2=a2;
			int maxmax2=minmin2+delta;//max(a,b);
			sprintf(query, "PRO;R;$;R.a00,;$;:JOIN;R;S;R.a00,S.a00,;<,R.a00,$,$,S.a00,$,$,;:SEL;R;$;R.a00,;AND,>,R.a00,$,$,%d,$,$,<,R.a00,$,$,%d,$,$,;:$:$:SEL;S;$;S.a00,;AND,>,S.a00,$,$,%d,$,$,<,S.a00,$,$,%d,$,$,;:$:$:$:",minmin1,maxmax1,minmin2,maxmax2);
		}break;
	case Q_INLJ:
		{

			sprintf(query,"PRO;R;$;R.a00,;$;:JOIN;R;S;R.a00,S.a00,;=,R.a00,$,$,S.a00,$,$,;:$:$:$:");//my own invension. =  -> INLJ
		}break;
	case Q_SMJ:
		{
			sprintf(query,"PRO;R;$;R.a00,;$;:JOIN;R;S;R.a00,S.a00,;+,R.a00,$,$,S.a00,$,$,;:$:$:$:");//my own invension. +  -> SMJ
		}break;
	case Q_HJ:
		{
			sprintf(query,"PRO;R;$;R.a00,;$;:JOIN;R;S;R.a00,S.a00,;-,R.a00,$,$,S.a00,$,$,;:$:$:$:");//my own invension. - -> HJ
		}break;
	case Q_DBMBENCH1:
		{
			int a=RAND(20000);
			int b=(a-2000);
			if(b<0) b=a+2000;
			int minmin=min(a,b);
			int maxmax=max(a,b);
			sprintf(query,"PRO;$;$;T1.a3,;$;:SEL;$;T1;T1.a2,;AND,<,%d,$,$,T1.a2,$,$,<,T1.a2,$,$,%d,$,$,;:$:$:$:",minmin,maxmax);
		}break;
	case Q_DBMBENCH2:
		{
			int a=RAND(20000);
			int b=(a-4000);
			if(b<0) b=a+4000;
			int minmin=min(a,b);
			int maxmax=max(a,b);
			sprintf(query,"AGG;T1;AVG;T1.a3,;$;:JOIN;T1;T2;T1.a1,T2.a1,;=,T1.a1,$,$,T2.a1,$,$,;:SEL;$;T1;T1.a2,;AND,<,%d,$,$,T1.a2,$,$,<,T1.a2,$,$,%d,$,$,;:$:$:$:$:",minmin,maxmax);
			//sprintf(query,"PRO;T1;$;T1.a3,;$;:JOIN;T1;T2;T1.a1,T2.a1,;=,T1.a1,$,$,T2.a1,$,$,;:$:$:$:");
		}break;
	case Q_DBMBENCH3:
		{
			int a=RAND(20000);
			int b=(a-100);
			if(b<0) b=a+100;
			int minmin=min(a,b);
			int maxmax=max(a,b);
			sprintf(query,"AGG;T1;AVG;T1.a3,;$;:SEL;$;T1;T1.a2,;AND,<,%d,$,$,T1.a2,$,$,<,T1.a2,$,$,%d,$,$,;:$:$:$:",minmin,maxmax);
		}break;
	}
	__DEBUG__(query);
}