 /* init node */
void CanNode::initCanNode(int can_idx, int node_id)
{
	/* get the channels */
    CAN_MSG msg;
    //Digit input channels
	CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,0);
	CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,1);
    sendSDO("40 00 60 00");
    _sleep(100);
    if(CAN_ReadMsg(can_idx, node_id,1,&msg) == CAN_OK)
        m_Channels[0] = (int)msg.a_data[4] * 4;
	/*else
		QMessageBox::warning(0,"digit","read error");*/

	 //Digit output channels
	CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,0);
	CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,1);
    sendSDO("40 00 62 00");
    _sleep(100);
    if(CAN_ReadMsg(can_idx, node_id,1,&msg) == CAN_OK)
        m_Channels[1] = (int)msg.a_data[4] * 4;
	/*else
		QMessageBox::warning(0,"digit","read error");*/

    //IP2302 has 4 digit input channels and 4 digit output channels
    //sendState(00,80);
    //_sleep(1000);
    //if(CAN_ReadMsg(can_idx, node_id,1,&msg) == CAN_OK)
    //{
    //    m_Channels[0] = 4;
    //    m_Channels[1] = 4;
    //}
    //Analog input channels
    CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,0);
    CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,1);
   sendSDO("40 01 64 00");
    _sleep(100);
    if(CAN_ReadMsg(can_idx, node_id,1,&msg) == CAN_OK)
        m_Channels[2] = (int)msg.a_data[4];
  
	//Analog output channels
    CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,0);
    CAN_ConfigQueue(can_idx,node_id,CAN_RX_QUE,1);
    sendSDO("40 11 64 00");
    _sleep(100);
    if(CAN_ReadMsg(can_idx, node_id,1,&msg) == CAN_OK)
        m_Channels[3] = (int)msg.a_data[4];

	//QMessageBox::about(0,"channels",QString("channels:%1,%2,%3,%4").arg(m_Channels[0]).arg(m_Channels[1]).arg(m_Channels[2]).arg(m_Channels[3]));
 
	sendState(01,00);
	setHeartBeat(0);
	setEventDriver(false);
}