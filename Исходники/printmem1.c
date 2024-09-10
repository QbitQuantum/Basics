void first_task_code (){
	
	print1();

	SHUTDOWN();
	Exit();
	kprintf ("Unexpected return from Exit() at first_task_code\n\r");
}