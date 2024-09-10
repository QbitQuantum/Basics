void* NyLPC_cMiMicIpTcpSocket_parseRx(
	NyLPC_TcMiMicIpTcpSocket_t* i_inst,
    const NyLPC_TcIPv4Payload_t* i_ipp)
{
    int i,s;
    NyLPC_TUInt16 tmp16;
    NyLPC_TUInt16 data_size;
    NyLPC_TUInt8 in_tcpflag=i_ipp->payload.tcp->flags;
    const void* tcp_data_offset;
    NyLPC_TBool is_new_packet;
    int num_of_noack;
    void* dlist[NyLPC_TcTcpSocket_NUMBER_OF_TXQ];
    void* ret;

    //パラメータの計算

    tmp16=NyLPC_TTcpHeader_getHeaderLength(i_ipp->payload.tcp);
    //TCPペイロードの長さは、IPパケットの長さ-(IPヘッダ+TCPヘッダ)
    data_size=NyLPC_TIPv4Header_getPacketLength(i_ipp->header)-NyLPC_TIPv4Header_getHeaderLength(i_ipp->header)-tmp16;
    //TCPデータオフセット
    tcp_data_offset=i_ipp->payload.rawbuf+tmp16;

    //インスタンスをロックする。
    lockResource(i_inst);

    //RSTのチェック。RST受信時は、状態にかかわらず、CLOSEDステータスに移行する。
    if (in_tcpflag & TCP_RST)
    {
        i_inst->tcpstateflags =UIP_CLOSED;
        goto DROP;
    }


    is_new_packet=NyLPC_ntohl(i_ipp->payload.tcp->seqno32)==i_inst->uip_connr.rcv_nxt32;


    //OPTIONの反映

    //MSSの取得
    if(NyLPC_TTcpHeader_getTcpMmsOpt(i_ipp->payload.tcp,&tmp16)){
        //取得で着たら更新
        i_inst->uip_connr.peer_mss=tmp16;
    }
    //受信パケットを元に、未ACKパケットの数を計算
    num_of_noack=getNumOfSending(i_inst,i_ipp->payload.tcp->ackno32);//i_inst->txbuf.num_of_txq;

    //ステータス毎のACK応答
    switch(i_inst->tcpstateflags)
    {
    case UIP_SYN_RCVD:
        //ACKを受信したら、ESTABLISHEDへ。
        //すべてのパケットをACKしたかで判定。()
        if(num_of_noack==0){
            i_inst->tcpstateflags=UIP_ESTABLISHED;
        }else{
            //それ以外のパケットはドロップする。
            break;//goto DROP;
        }
        //新しいパケットがなければ、無応答
        if(!is_new_packet){
            break;//goto DROP;
        }
        //引き続き、ESTABLISHEDの処理へ。
    case UIP_ESTABLISHED:
        if(data_size>0){
            if(is_new_packet){
                if(addRecvData(i_inst,tcp_data_offset,data_size)){
                    //通常のACK返却
                    i_inst->uip_connr.rcv_nxt32+=data_size;
                }else{
                    //失敗したときは必要に応じて単純ACK
                }
            }
        }
        //どちらにしろ、ACK送信
        if(is_new_packet && (in_tcpflag & TCP_FIN)){
            //FINがあるときは、ステータスをCLOSE_WAITへセットして、ACKを返す。
            i_inst->tcpstateflags = UIP_CLOSE_WAIT;
            i_inst->uip_connr.rcv_nxt32++;
        }
        break;
    case UIP_CLOSE_WAIT:
        //必要に応じたACK応答
        break;
    case UIP_LAST_ACK:
        //ACK(by FIN)が得られたなら、CLOSEDへ。
        if(num_of_noack==0){
            i_inst->tcpstateflags=UIP_CLOSED;
        }
        //必要に応じたACK応答
        break;
    case UIP_FIN_WAIT_1:
        //FIN受信->CLOSINGへ
        if(is_new_packet){
            i_inst->uip_connr.rcv_nxt32+=data_size;
            if(in_tcpflag & TCP_FIN){
                i_inst->uip_connr.rcv_nxt32++;
                if(num_of_noack==0){
                    //FINとACKを受信
                    i_inst->tcpstateflags=UIP_TIME_WAIT;
                }else{
                    //FINのみ
                    i_inst->tcpstateflags=UIP_CLOSING;
                }
            }
        }else if(num_of_noack==0){
            //ACKのみ
            i_inst->tcpstateflags=UIP_FIN_WAIT_2;
        }
        //必要に応じたACK応答
        break;
    case UIP_FIN_WAIT_2:
        //FIN受信->TIME_WAITへ(pureACK)
        if(is_new_packet && (in_tcpflag & TCP_FIN)){
            i_inst->uip_connr.rcv_nxt32++;
            i_inst->tcpstateflags=UIP_TIME_WAIT;
        }
        break;
    case UIP_CLOSING:
        //ACK受信したら、TIME_WAITへ
        if(num_of_noack==0){
            i_inst->tcpstateflags=UIP_TIME_WAIT;
        }
        break;
    case UIP_CLOSED:
        //何もできない。何もしない。
        break;
    case UIP_TIME_WAIT:
        //最終ACKを送り続ける。
        break;
    case UIP_SYN_SENT:
        //connect関数実行中しか起動しないステータス
        if(num_of_noack==0){
            i_inst->tcpstateflags=UIP_ESTABLISHED;
            i_inst->uip_connr.rcv_nxt32=NyLPC_ntohl(i_ipp->payload.tcp->seqno32)+1;
        }else{
            //それ以外のパケットはドロップする。
            break;//goto DROP;
        }
        //ACKを送る。
        break;
    default:
        goto DROP;
    }
    //ウインドウサイズを更新
    i_inst->uip_connr.peer_win=NyLPC_ntohs(i_ipp->payload.tcp->wnd16);

    //送信キューから、Peerが受信したデータを削除する。
    if(in_tcpflag & TCP_ACK){
        //再送パケットキューから送信済みのデータを回収(後で開放)
        NyLPC_Trace();
        s=updateTxQByIndex(i_inst,i_ipp->payload.tcp->ackno32,dlist);
        NyLPC_Trace();
    }else{
        s=0;
    }
    //新しいパケットがきた場合は、再送キューのACKを更新する。
    if(is_new_packet){
        //再送キューのACKを更新
        updateTxAck(i_inst,NyLPC_htonl(i_inst->uip_connr.rcv_nxt32));
    }

    //送信キューのない
    if(((in_tcpflag&(TCP_FIN|TCP_SYN))!=0x00) ||
        ((!is_new_packet) && (data_size>0)))
    {
        //ソケットからPureACKを生成 as setPacket(i_inst,i_ipp,TCP_ACK,NULL,0);
        ret=NyLPC_cMiMicIpNetIf_allocSysTxBuf();
        setTxPacket(i_inst,ret,TCP_ACK,NULL,0);
    }else{
        ret=NULL;
    }
    unlockResource(i_inst);
    //取り外したTXメモリの開放
    for(i=0;i<s;i++){
        //取り外したTXメモリを開放
        NyLPC_cMiMicIpNetIf_releaseTxBuf(dlist[i]);
    }
NyLPC_Trace();
    return ret;
DROP:
    //ACKしたパケットを送信キューから削除
    unlockResource(i_inst);
NyLPC_Trace();
    return NULL;
}