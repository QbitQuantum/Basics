void debugpageptr(UINT32 addr) {

	FILEH	fh;
	char	buf[256];
	UINT32	pde;
	UINT32	pte;
	UINT	i;
	UINT32	a;

	fh = file_create("page.txt");
	SPRINTF(buf, "CR3=%.8x\r\n", CPU_CR3);
	file_write(fh, buf, strlen(buf));
	for (i=0; i<1024; i++) {
		a = CPU_STAT_PDE_BASE + (i * 4);
		pde = cpu_memoryread_d(a);
		SPRINTF(buf, "%.8x=>%.8x [%.8x]\r\n", (i << 22), pde, a);
		file_write(fh, buf, strlen(buf));
	}
	addr >>= 22;
	pde = cpu_memoryread_d(CPU_STAT_PDE_BASE + (addr * 4));
	for (i=0; i<1024; i++) {
		a = (pde & CPU_PDE_BASEADDR_MASK) + (i * 4);
		pte = cpu_memoryread_d(a);
		SPRINTF(buf, "%.8x=>%.8x [%.8x]\r\n", (addr << 22) + (i << 12), pte, a);
		file_write(fh, buf, strlen(buf));
	}
	file_close(fh);
}