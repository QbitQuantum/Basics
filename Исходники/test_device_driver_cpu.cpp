TEST(DeviceDriverTest, CPU_CONST_BERN) {
	float numbers[10000];
	CPUDriver driver;
	DeviceMemoryPointer_Local_RAM p(NULL, sizeof(float)*10000);
	driver.malloc(&p);

	float one = 10000.0;
	DeviceMemoryPointer_Local_RAM p_one(&one, sizeof(float));
	driver.sapply<_f_set>(&p, &p_one);

	driver.sbernoulli_initialize(&p, 0.2);

  	memcpy(numbers, p.ptr, p.size_in_byte);

	float sum = 0.0;
	for(int i=0;i<10000;i++){
		sum += numbers[i];
	}
	ASSERT_NEAR(sum/10000, 0.2, 0.1);
}