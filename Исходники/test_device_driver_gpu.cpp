TEST(DeviceDriverTest, GPU_CONST_BERN) {
	float numbers[10000];
	GPUDriver driver;
	DeviceMemoryPointer_Local_GPURAM p(0, NULL, sizeof(float)*10000);
	driver.malloc(&p);

	float one = 10000.0;
	DeviceMemoryPointer_Local_RAM p_one(&one, sizeof(float));
	driver.sapply<_f_set>(&p, &p_one);

	driver.sbernoulli_initialize(&p, 0.2);

  	cudaMemcpy(numbers, p.ptr, p.size_in_byte, cudaMemcpyDeviceToHost);

	float sum = 0.0;
	for(int i=0;i<10000;i++){
		sum += numbers[i];
	}
	ASSERT_NEAR(sum/10000, 0.2, 0.1);
}