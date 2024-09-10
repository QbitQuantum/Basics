void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	protoent *protocolo;
	iphdr *datagrama;
	ether_header *trama;
	tcphdr *cabecera_tcp;

	struct mi_cabecera_tcp *ptr_paquetes_aux;
	int i;

	trama=(ether_header *)(pkt_data);

	if(ntohs(trama->ether_type) == ETHERTYPE_IP)  //IP¿?
	{		
		datagrama=(iphdr *)(pkt_data+sizeof(ether_header));

		protocolo = getprotobynumber(datagrama->protocol);

		if(protocolo!=0 && !strcmp(protocolo->p_name, "tcp")) //tcp¿?
		{
			cabecera_tcp = (tcphdr *) (pkt_data+sizeof(ether_header)+sizeof(iphdr));

			//Reservo memoria en bloques de 10 paquetes
			if (num_paquetes%10==0)
			{
				ptr_paquetes_aux = ptr_paquetes;

				ptr_paquetes = (mi_cabecera_tcp *)malloc(sizeof(mi_cabecera_tcp)*(num_paquetes+10));

				for (i=0;i<num_paquetes;i++)
					ptr_paquetes[i] = ptr_paquetes_aux[i];

				if (num_paquetes>0) free(ptr_paquetes_aux);
			}

			//Añado al vector los paquetes TCP
			ptr_paquetes[num_paquetes].ip1 = (dir_ip) ntohl(datagrama->saddr);
			ptr_paquetes[num_paquetes].ip2 = (dir_ip) ntohl(datagrama->daddr);
			ptr_paquetes[num_paquetes].puerto1 = (puerto) ntohs(cabecera_tcp->source);
			ptr_paquetes[num_paquetes].puerto2 = (puerto) ntohs(cabecera_tcp->dest);
			ptr_paquetes[num_paquetes].seq = (num_seq_ack) ntohl(cabecera_tcp->seq);
			ptr_paquetes[num_paquetes].ack = (num_seq_ack) ntohl(cabecera_tcp->ack_seq);

			#ifdef DEBUG
			mostrar_paquete_tcp(&ptr_paquetes[num_paquetes]);
			#endif

			num_paquetes++;
		}
	}
}