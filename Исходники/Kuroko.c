BOOL SetBufAndTimeOut(HANDLE Hcom)
{
	/*���ô���*/
	//����I/O������(����ͨ�����ʵ���)
	if (SetupComm(Hcom,//�豸����
		1024,//���뻺������С(�ֽ�)
		1024 //������������С(�ֽ�)
		) == FALSE)
	{
		Err = Err_SetBuffer;
		return FALSE;
	}
	//�������ó�ʱ�Ľṹ��  ע:��ʱ���������������õĳ�ʱʱ����δ���ɶ�/д����,��/д�����Ի�����
	COMMTIMEOUTS TimeOuts;
	/*
	1.��/д�ܳ�ʱ=ϵ��*�ַ���+����
	2.ϵ���볣����Ϊ0����ʾ��ʹ�øó�ʱ
	3.����������ʱΪMAXDWORD�Ҷ�ϵ���ͳ�����Ϊ0,��ô�������ͻ���������,�����Ƿ�����Ҫ�����ַ�
	4.�첽ͨ��ʱ,��/д���ܻ������ɲ���ǰ����,��ʱ��ʱ�涨���ǲ���������ʱ��
	5.ʱ�䵥λ��Ϊms
	*/
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = MAXDWORD;//��������ʱ
	TimeOuts.ReadTotalTimeoutMultiplier = 0;//��ʱ��ϵ��
	TimeOuts.ReadTotalTimeoutConstant = 1;//��ʱ�䳣��
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 50;//дʱ��ϵ��
	TimeOuts.WriteTotalTimeoutConstant = 1000;//дʱ�䳣��
	//д�볬ʱ����,��ȡ��ǰ��ʱ����ʹ��GetCommTimeouts()
	if (SetCommTimeouts(Hcom, &TimeOuts) == FALSE)
	{
		Err = Err_SetTimeOuts;
		return FALSE;
	}
	return TRUE;
}