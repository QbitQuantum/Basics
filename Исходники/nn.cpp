int main(){

	int a,b;
	char c;
	int i;
	int j;
	double dif;
	int col = 0;
	double sum_sq_error = 0 ;
	int epoch=0;
	double pre_avg_sq_error = 0;
	double accuracy = 0;
	double max = 0;
	int num_correct= 0, tmp, k;
	//�ʱ�ȭ
	for(i = 0; i<NLayer; i++){
		for(j = 0; j<MLayerSize; j++){
			s[i][j] = 0;
			f[i][j] = 0;
			delta[i][j] = 0;
		}
	}



	initialization();		// ����ġ ������ �ʱ�ȭ


	FILE *fp, *fp1;
	fp = fopen("traindata.txt", "r");fp1 = fopen("testdata.txt", "r");//�Է½�ȣ ��������
	while(!feof(fp)){
		fscanf(fp, "%d", &a);
		for(i = 0; i<m2; i++){
			if(a == i)	
				d[col][i] = 1;
			else	
				d[col][i] = 0;		
		}	
		fscanf(fp, " %c ", &c);		c = '0';	// $������
		for(i = 0; i<N; i++){
			fscanf(fp, "%d", &b);
			TrainData[col][i] = b;
		}
		col ++;
	}
	col = 0;a = 0;b = 0;
	while(!feof(fp1)) {
		fscanf(fp1, "%d", &a);
		for(i=0; i<m2; i++) {
			if(a==i) 
				Td[col][i]=1;
			else 
				Td[col][i]=0;		
		}
		fscanf(fp1, " %c ", &c);	c = '0';	// $������
		for(i=0; i<N; i++) {
			fscanf(fp1, " %d",  &b);
			TestData[col][i]=b;		
		}
		col++;
	}
	//file input


	do{
		pre_avg_sq_error = avg_sq_error;
	//	printf("pre = %lf\n", pre_avg_sq_error);
		avg_sq_error=0, sum_sq_error=0;
		for(int t=0; t<=N_tr_examples-1; t++){		// �� ������ �Ʒð���
			forward_compute(t);
			backward_compute(t);
			weight_update(t);
		}
		epoch++;
		for(int t = 0; t<=N_tr_examples-1; t++){	// �� ���� �� ��� ���� ���
			// t���� �Ʒÿ����� �̿��Ͽ� �ý����� ����� ���� error�� ����
			forward_compute(t);													//  t ��° �Ʒÿ��� �����Ͽ� ����� ����

			for(i = 0; i<=M[NLayer-1]-1 ; i++){									       // �������� ����� �̿��Ͽ� ������ ����.
				sum_sq_error+=pow((d[t][i]-f[NLayer-1][i]),2);					
			}
		}
		avg_sq_error = sum_sq_error/(N_tr_examples*M[NLayer-1]);						//��� �Ʒ� ���� ���Ͽ� ��� square ������ �����
		printf("%d epoch error rate = %lf\n",epoch,avg_sq_error);

		/*        Fail �κ�, �Ӱ�ġ ���Ϸ� �������� �ʹ� ���� ����� ������ ������ �Ͼ���ϴ�.
		dif = pre_avg_sq_error - avg_sq_error;
		if(dif < 0)
			dif = -dif;
		printf("dif = %lf\n", dif);
		*/

	}while(threshold < avg_sq_error) ;
		//&& (threshold < dif));				//avg_sq_error �� �Ӱ�ġ �����̸� ����, 
	//�Ǵ� ���� epoch ������ avg_sq_error �� �̹� epoch �� avg_sq_error  �� ���̰�       �Ӱ�ġ �����̸� ����


	for(int t = 0; t<=N_te_examples-1; t++){
		// TestData[t], d_te[t] �� input,d�� �ִ´�.
		t_forward_compute(t);
		max=0.;
		for(j=0; j<NLayer; j++) {	
			if(max < f[NLayer-1][j]) {
				max = f[NLayer-1][j];
				tmp = j;
			}
		}
		for(k=0; k<NLayer; k++) {
			if(Td[t][k] == 1 && tmp == k)
				num_correct++;
		}
	}
	accuracy =  (double)num_correct/(double)N_te_examples;
	printf("Accuracy = %lf", accuracy);

	fclose(fp);
	fclose(fp1);
}