void socksend(notification_data* data)
{
	Socket sock =Socket_get_instance();
	if(sock->isAccessible(sock)){
		bool b= sock->Send(sock,"hello");
		sprintf(data->result_text,"%s",b?"send ok":"send fail");
	}
	else{
		sprintf(data->result_text,"this device does't support socket");
	}

}