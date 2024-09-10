void getsyspara(void)
{
	unsigned char buffer[32];
	int i;
	char macaddr[]="00:11:22:33:44:55";
	char macaddr2[]="00:11:22:33:44:56";
	char macaddr3[]="001122334457";
	char macaddr4[]="001122334458";
	char ea[ETHER_ADDR_LEN];
	char country_code[3];
	char pin[9];
	char productid[13];
	char fwver[8], fwver_sub[16];
	char blver[20];
	unsigned char txbf_para[33];
	
	/* /dev/mtd/2, RF parameters, starts from 0x40000 */
	memset(buffer, 0, sizeof(buffer));
	memset(country_code, 0, sizeof(country_code));
	memset(pin, 0, sizeof(pin));
	memset(productid, 0, sizeof(productid));
	memset(fwver, 0, sizeof(fwver));
	memset(fwver_sub, 0, sizeof(fwver_sub));
	memset(txbf_para, 0, sizeof(txbf_para));

	if (FRead(buffer, OFFSET_MAC_ADDR, 6)<0)
	{
		dbg("READ MAC address: Out of scope\n");
	}
	else
	{
		if (buffer[0]!=0xff)
		{
			ether_etoa(buffer, macaddr);
			ether_etoa2(buffer, macaddr3);
		}
	}
	
	if (FRead(buffer, OFFSET_MAC_ADDR_2G, 6)<0)
	{
		dbg("READ MAC address 2G: Out of scope\n");
	}
	else
	{
		if (buffer[0]!=0xff)
		{
			ether_etoa(buffer, macaddr2);
			ether_etoa2(buffer, macaddr4);
		}
	}

	nvram_set("il0macaddr", macaddr);
	nvram_set("il1macaddr", macaddr2);
	nvram_set("et0macaddr", macaddr);
	nvram_set("br0hexaddr", macaddr3);
	nvram_set("wanhexaddr", macaddr4);
	
	if (FRead(buffer, OFFSET_MAC_GMAC0, 6)<0)
	{
		dbg("READ MAC address GMAC0: Out of scope\n");
	}
	else
	{
		if (buffer[0]==0xff)
		{
			if (ether_atoe(macaddr, ea))
				FWrite(ea, OFFSET_MAC_GMAC0, 6);
		}
	}
	
	if (FRead(buffer, OFFSET_MAC_GMAC2, 6)<0)
	{
		dbg("READ MAC address GMAC2: Out of scope\n");
	}
	else
	{
		if (buffer[0]==0xff)
		{
			if (ether_atoe(macaddr2, ea))
				FWrite(ea, OFFSET_MAC_GMAC2, 6);
		}
	}
	
	/* reserved for Ralink. used as ASUS country code. */
	if (FRead(country_code, OFFSET_COUNTRY_CODE, 2)<0)
	{
		dbg("READ ASUS country code: Out of scope\n");
		strcpy(country_code, "GB");
	}
	else
	{
		country_code[2] = 0;
		if ((unsigned char)country_code[0]==0xff)
			strcpy(country_code, "GB");
	}
	
	if (strlen(nvram_safe_get("rt_country_code")) == 0)
	{
		nvram_set("rt_country_code", country_code);
	}
	
	if (strlen(nvram_safe_get("wl_country_code")) == 0)
	{
		nvram_set("wl_country_code", country_code);
	}
	
	if (!strcasecmp(nvram_safe_get("wl_country_code"), "BR"))
		nvram_set("wl_country_code", "UZ");
	
	/* reserved for Ralink. used as ASUS pin code. */
	if (FRead(pin, OFFSET_PIN_CODE, 8)<0)
	{
		dbg("READ ASUS pin code: Out of scope\n");
		nvram_set("wl_pin_code", "");
	}
	else
	{
		if ((unsigned char)pin[0]!=0xff)
			nvram_set("secret_code", pin);
		else
			nvram_set("secret_code", "12345670");
	}

#if defined(USE_RT3352_MII)
 #define EEPROM_INIC_SIZE (512)
 #define EEPROM_INIT_ADDR 0x48000
	{
		char eeprom[EEPROM_INIC_SIZE];
		if(FRead(eeprom, EEPROM_INIT_ADDR, sizeof(eeprom)) < 0)
		{
			dbg("READ iNIC EEPROM: Out of scope!\n");
		}
		else
		{
			FILE *fp;
			if((fp = fopen("/etc/Wireless/iNIC/iNIC_e2p.bin", "w")))
			{
				fwrite(eeprom, sizeof(eeprom), 1, fp);
				fclose(fp);
			}
		}
	}
#endif

	/* /dev/mtd/3, firmware, starts from 0x50000 */
	if (FRead(buffer, 0x50020, sizeof(buffer))<0)
	{
		dbg("READ firmware header: Out of scope\n");
		nvram_set("productid", "unknown");
		nvram_set("firmver", "unknown");
	}
	else
	{
		strncpy(productid, buffer + 4, 12);
		productid[12] = 0;
		
		if(valid_subver(buffer[27]))
			sprintf(fwver_sub, "%d.%d.%d.%d%c", buffer[0], buffer[1], buffer[2], buffer[3], buffer[27]);
		else
			sprintf(fwver_sub, "%d.%d.%d.%d", buffer[0], buffer[1], buffer[2], buffer[3]);
		
#if defined(FWBLDSTR)
		sprintf(fwver_sub, "%s-%s", fwver_sub, FWBLDSTR);
#endif
		sprintf(fwver, "%d.%d.%d.%d", buffer[0], buffer[1], buffer[2], buffer[3]);
		nvram_set("productid", trim_r(productid));
		nvram_set("firmver", trim_r(fwver));
		nvram_set("firmver_sub", trim_r(fwver_sub));
	}

	memset(buffer, 0, sizeof(buffer));
	FRead(buffer, OFFSET_BOOT_VER, 4);
	sprintf(blver, "%s-0%c-0%c-0%c-0%c", trim_r(productid), buffer[0], buffer[1], buffer[2], buffer[3]);
	nvram_set("blver", trim_r(blver));

	int count_0xff = 0;
	if (FRead(txbf_para, OFFSET_TXBF_PARA, 33) < 0)
	{
		dbg("READ TXBF PARA address: Out of scope\n");
	}
	else
	{
		for (i = 0; i < 33; i++)
		{
			if (txbf_para[i] == 0xff)
				count_0xff++;
		}
	}

	if (count_0xff == 33)
		nvram_set("wl_txbf_en", "0");
	else
		nvram_set("wl_txbf_en", "1");
}