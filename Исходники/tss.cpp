void TSS::Init(GDT * gdt)
{
	m_back_link = 0;
	//m_esp0 = KERNEL_STACK_TOP;
	m_ss0 = SEL_KERNEL_CODE;
	m_cr3 = __readcr3();//登记CR3(PDBR)
	m_eip = 0;//(uint32)UserProcess;
	m_eflags = 0x00000202;

	m_ldt = 0;//没有LDT。处理器允许没有LDT的任务
	m_trap = 0;
	m_iobase = 103;//没有I/O位图。0特权级事实上不需要。
				   //创建程序管理器的TSS描述符，并安装到GDT中 
	printf("TSS Init() OK\n");
	Register(gdt);
}