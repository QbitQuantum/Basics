/**
 * Sockwatch Module Handler
 * If you use Sockwatch Module, this should run in the main loop
 * @ingroup sockwatch_module
 */
void sockwatch_run(void)
{
#define WCF_HANDLE(item_v, ret_v) \
do { \
	BITCLR(watch_sock[i], item_v); \
	watch_cb[i](i, item_v, ret_v); \
} while(0)

	uint8_t i;
	int32_t ret;

	S2E_Packet *value = get_S2E_Packet_pointer();
	MQTTPacket_connectData mqttConnectData = MQTTPacket_connectData_initializer;

	for(i=0; i<TOTAL_SOCK_NUM; i++) {
		if(watch_sock[i] == 0) continue;
		if(atci.mqtt_run == 1) {
			ret = MQTTYield(&mqttClient, mqttConnectData.keepAliveInterval);
#ifdef __ATC_MODE_MQTT_DEBUG__
			if(ret != SUCCESSS) {
				printf("MQTT yield error - ret : %d\r\n", ret);
			}
#endif
		}
		if(watch_sock[i] & WATCH_SOCK_RECV) {	// checked every time when 'connected' state
			getsockopt(i, SO_RECVBUF, (uint16_t*)&ret);
			if((uint16_t)ret > 0) WCF_HANDLE(WATCH_SOCK_RECV, RET_OK);
		}
		if(watch_sock[i] & WATCH_SOCK_CLS_EVT) {	// checked every time when 'connected' state
			getsockopt(i, SO_STATUS, (uint8_t*)&ret);
			switch((uint8_t)ret) {
			case SOCK_CLOSED:
				WCF_HANDLE(WATCH_SOCK_CLS_EVT, RET_OK);
				break;
			case SOCK_CLOSE_WAIT:
				disconnect(i);
				//close(i);
				break;
			default:
				break;
			}
		}
		if(watch_sock[i] & WATCH_SOCK_CONN_EVT) {	// checked every time when 'listen' state
			getsockopt(i, SO_STATUS, (uint8_t*)&ret);
			switch((uint8_t)ret) {
			case SOCK_ESTABLISHED:
				WCF_HANDLE(WATCH_SOCK_CONN_EVT, RET_OK);
				break;
			default:
				break;
			}
		}
		if((watch_sock[i] & WATCH_SOCK_MASK_LOW) == 0) continue;	// things which occurs occasionally will be checked all together
		if(watch_sock[i] & WATCH_SOCK_CLS_TRY) {
			getsockopt(i, SO_STATUS, (uint8_t*)&ret);
			switch((uint8_t)ret) {
			case SOCK_LISTEN:
				close(i);
			case SOCK_CLOSED:
				WCF_HANDLE(WATCH_SOCK_CLS_TRY, RET_OK);
				break;
			case SOCK_FIN_WAIT:
				close(i);	
				break;
			default:
				ctlsocket(i, CS_GET_INTERRUPT, (uint8_t*)&ret);
				if((uint8_t)ret & Sn_IR_TIMEOUT){
					//ctlsocket(i, CS_CLR_INTERRUPT, (uint8_t*)&ret);
					close(i);
					WCF_HANDLE(WATCH_SOCK_CLS_TRY, SOCKERR_TIMEOUT);
				}
				disconnect(i);
				//close(i);
				break;
			}
		}
		if(watch_sock[i] & WATCH_SOCK_CONN_TRY) {
			getsockopt(i, SO_STATUS, (uint8_t*)&ret);
			switch((uint8_t)ret) {
			case SOCK_ESTABLISHED:
				WCF_HANDLE(WATCH_SOCK_CONN_TRY, RET_OK);
				if(atci.mqtt_con == 1) {
					if(getSn_IR(i) & Sn_IR_CON) {
						setSn_IR(i,Sn_IR_CON);

						mqttConnectData.MQTTVersion			= 4;
						mqttConnectData.clientID.cstring 	= value->module_name;
						mqttConnectData.username.cstring 	= value->options.mqtt_user;
						mqttConnectData.password.cstring 	= value->options.mqtt_pw;
						mqttConnectData.willFlag 			= 0;
						mqttConnectData.keepAliveInterval   = 60;
						mqttConnectData.cleansession        = 1;

						ret = MQTTConnect(&mqttClient, &mqttConnectData);
#ifdef __ATC_MODE_MQTT_DEBUG__
						if(ret != SUCCESSS) {
							printf("MQTT connect error - ret : %d\r\n", ret);
						}
#endif
						atci.mqtt_con = 0;
						atci.mqtt_run = 1;
					}
				}
				break;
			default:
				ctlsocket(i, CS_GET_INTERRUPT, (uint8_t*)&ret);
				if((uint8_t)ret & Sn_IR_TIMEOUT){
					//ctlsocket(i, CS_CLR_INTERRUPT, (uint8_t*)&ret);
					close(i);
					WCF_HANDLE(WATCH_SOCK_CONN_TRY, SOCKERR_TIMEOUT);
				}
				break;
			}
		}
		if(watch_sock[i] & WATCH_SOCK_TCP_SEND) {
			// 블로킹 모드로만 동작함 그러므로 Watch할 필요가 없음
		}
		if(watch_sock[i] & WATCH_SOCK_UDP_SEND) {
			if(checkAtcUdpSendStatus < 0) {
				WCF_HANDLE(WATCH_SOCK_UDP_SEND, RET_NOK);
			}
			else {
				WCF_HANDLE(WATCH_SOCK_UDP_SEND, RET_OK);
			}
		}
	}

	// ToDo: not socket part
	
}