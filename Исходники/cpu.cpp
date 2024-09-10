//프로세서에 프로세스를 삽입
void Cpu::insertToProcessor(){
	Process frontprocess;
	bool checkQ = m_q_process.pop(frontprocess);
	if (checkQ){
		printf("CPU No : [ %d ] process [ %d ] ,Start Time = %3d , Burst Time = %3d, 현재 클락 Time = %d\n", m_cpuNum, frontprocess.getPid(), frontprocess.getStartTime(), frontprocess.getBurstTime(), m_clockTime);
		usingProcess(frontprocess);	//CPU가 프로세스를 사용한다
	}
}