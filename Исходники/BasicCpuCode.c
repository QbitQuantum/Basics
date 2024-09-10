int main(int argc, char * argv[])
{
	parse_args(argc, argv);
	const int size = n * n;
	int data_size_bytes = size * sizeof(float);

	float *mat_a = malloc(data_size_bytes);
	float *mat_b = malloc(data_size_bytes);
	float *vector;
	float *output = malloc(data_size_bytes);

	float *expected = malloc(data_size_bytes);

	generate_matrix(n, mat_a, range);
	generate_matrix(n, mat_b, range);

	timing_t timer;
	timer_start(&timer);

	float *mat_b_trans = malloc(data_size_bytes);
	transpose(n, mat_b, mat_b_trans);

	for (int i=0; i<n; ++i) {
		vector = &mat_b_trans[n*i];
		MatMatMultiply(n, mat_a, vector, &output[n*i]);
	}
	float *output_trans = malloc(data_size_bytes);
	transpose(n, output, output_trans);

	timer_stop(&timer);
	float sum = sum_mat(size, output_trans);
	printf("%d %f %ld %ld\n", n, sum, timer.realtime, timer.cputime);

	int status = 0;

	if (trace == 1) {

		printf("\nMatrix A\n");
		for (int i=0; i<n; i++){
			for (int j=0; j<n; j++){
				printf("%f " , mat_a[i*n+j]);
			}
			printf("\n");
		}

		printf("\nMatrix B \n");
		for (int i=0; i<n; i++){
			for (int j=0; j<n; j++){
				printf("%f " , mat_b[i*n+j]);
			}
			printf("\n");
		}

		printf("\n\nResult\n");
		for (int i=0; i<n; i++){
			for (int j=0; j<n; j++){
				printf("%f " , output[i*n+j]);
			}
			printf("\n");
		}
	}

	else if (trace == 2) {
		multiply_CPU_matrix(n, mat_a, mat_b, expected);

		int status = check(size, output_trans, expected);
		if (status) {
			printf("Test failed.\n");
			status = 1;
		}
		else
			printf("Test passed OK!\n");

	}


	free(mat_a);
	free(mat_b);
	free(mat_b_trans);
	free(output);
	free(expected);
	free(output_trans);

	return status;
}