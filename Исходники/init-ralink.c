void init_syspara(void)
{
	unsigned char buffer[16];
	unsigned char *dst;
	unsigned int bytes;
	int i;
	char macaddr[]="00:11:22:33:44:55";
	char macaddr2[]="00:11:22:33:44:58";
	char country_code[3];
	char pin[9];
	char productid[13];
	char fwver[8];
	char blver[20];
	unsigned char txbf_para[33];
	char ea[ETHER_ADDR_LEN];

	nvram_set("buildno", rt_serialno);
	nvram_set("extendno", rt_extendno);
	nvram_set("buildinfo", rt_buildinfo);
	nvram_set("swpjverno", rt_swpjverno);

	/* /dev/mtd/2, RF parameters, starts from 0x40000 */
	dst = buffer;
	bytes = 6;
	memset(buffer, 0, sizeof(buffer));
	memset(country_code, 0, sizeof(country_code));
	memset(pin, 0, sizeof(pin));
	memset(productid, 0, sizeof(productid));
	memset(fwver, 0, sizeof(fwver));
	memset(txbf_para, 0, sizeof(txbf_para));

	if (FRead(dst, OFFSET_MAC_ADDR, bytes)<0)
	{
		_dprintf("READ MAC address: Out of scope\n");
	}
	else
	{
		if (buffer[0]!=0xff)
			ether_etoa(buffer, macaddr);
	}

#if !defined(RTN14U) // single band
	if (FRead(dst, OFFSET_MAC_ADDR_2G, bytes)<0)
	{
		_dprintf("READ MAC address 2G: Out of scope\n");
	}
	else
	{
		if (buffer[0]!=0xff)
			ether_etoa(buffer, macaddr2);
	}
#endif

#if defined(RTN14U) // single band
	if (!mssid_mac_validate(macaddr))
#else
	if (!mssid_mac_validate(macaddr) || !mssid_mac_validate(macaddr2))
#endif
		nvram_set("wl_mssid", "0");
	else
		nvram_set("wl_mssid", "1");

#if defined(RTN14U) // single band
	nvram_set("et0macaddr", macaddr);
	nvram_set("et1macaddr", macaddr);
#else
	//TODO: separate for different chipset solution
	nvram_set("et0macaddr", macaddr);
	nvram_set("et1macaddr", macaddr2);
#endif

	if (FRead(dst, OFFSET_MAC_GMAC0, bytes)<0)
		dbg("READ MAC address GMAC0: Out of scope\n");
	else
	{
		if (buffer[0]==0xff)
		{
			if (ether_atoe(macaddr, ea))
				FWrite(ea, OFFSET_MAC_GMAC0, 6);
		}
	}

	if (FRead(dst, OFFSET_MAC_GMAC2, bytes)<0)
		dbg("READ MAC address GMAC2: Out of scope\n");
	else
	{
		if (buffer[0]==0xff)
		{
			if (ether_atoe(macaddr2, ea))
				FWrite(ea, OFFSET_MAC_GMAC2, 6);
		}
	}

	/* reserved for Ralink. used as ASUS country code. */
#if ! defined(RTCONFIG_NEW_REGULATION_DOMAIN)
	dst = (unsigned char*) country_code;
	bytes = 2;
	if (FRead(dst, OFFSET_COUNTRY_CODE, bytes)<0)
	{
		_dprintf("READ ASUS country code: Out of scope\n");
		nvram_set("wl_country_code", "");
	}
	else
	{
		chk_valid_country_code(country_code);
		nvram_set("wl_country_code", country_code);
		nvram_set("wl0_country_code", country_code);
		nvram_set("wl1_country_code", country_code);
	}
#else	/* ! RTCONFIG_NEW_REGULATION_DOMAIN */
	dst = buffer;

	bytes = MAX_REGSPEC_LEN;
	memset(dst, 0, MAX_REGSPEC_LEN+1);
	if(FRead(dst, REGSPEC_ADDR, bytes) < 0)
		nvram_set("reg_spec", "FCC"); // DEFAULT
	else
	{
		for (i=(MAX_REGSPEC_LEN-1);i>=0;i--) {
			if ((dst[i]==0xff) || (dst[i]=='\0'))
				dst[i]='\0';
		}
		if (dst[0]!=0x00)
			nvram_set("reg_spec", dst);
		else
			nvram_set("reg_spec", "FCC"); // DEFAULT
	}

	if (FRead(dst, REG2G_EEPROM_ADDR, MAX_REGDOMAIN_LEN)<0 || memcmp(dst,"2G_CH", 5) != 0)
	{
		_dprintf("READ ASUS country code: Out of scope\n");
		nvram_set("wl_country_code", "");
		nvram_set("wl0_country_code", "DB");
		nvram_set("wl_reg_2g", "2G_CH14");
	}
	else
	{
		for(i = 0; i < MAX_REGDOMAIN_LEN; i++)
			if(dst[i] == 0xff || dst[i] == 0)
				break;

		dst[i] = 0;
		nvram_set("wl_reg_2g", dst);
		if      (strcmp(dst, "2G_CH11") == 0)
			nvram_set("wl0_country_code", "US");
		else if (strcmp(dst, "2G_CH13") == 0)
			nvram_set("wl0_country_code", "GB");
		else if (strcmp(dst, "2G_CH14") == 0)
			nvram_set("wl0_country_code", "DB");
		else
			nvram_set("wl0_country_code", "DB");
	}

	if (FRead(dst, REG5G_EEPROM_ADDR, MAX_REGDOMAIN_LEN)<0 || memcmp(dst,"5G_", 3) != 0)
	{
		_dprintf("READ ASUS country code: Out of scope\n");
		nvram_set("wl_country_code", "");
		nvram_set("wl1_country_code", "DB");
		nvram_set("wl_reg_5g", "5G_ALL");
	}
	else
	{
		for(i = 0; i < MAX_REGDOMAIN_LEN; i++)
			if(dst[i] == 0xff || dst[i] == 0)
				break;

		dst[i] = 0;
		nvram_set("wl_reg_5g", dst);
		if      (strcmp(dst, "5G_BAND1") == 0)
			nvram_set("wl1_country_code", "GB");
		else if (strcmp(dst, "5G_BAND123") == 0)
			nvram_set("wl1_country_code", "GB");
		else if (strcmp(dst, "5G_BAND14") == 0)
			nvram_set("wl1_country_code", "US");
		else if (strcmp(dst, "5G_BAND24") == 0)
			nvram_set("wl1_country_code", "TW");
		else if (strcmp(dst, "5G_BAND4") == 0)
			nvram_set("wl1_country_code", "CN");
		else
			nvram_set("wl1_country_code", "DB");
	}
#endif	/* ! RTCONFIG_NEW_REGULATION_DOMAIN */
#if defined(RTN56U) || defined(RTCONFIG_DSL)
		if (nvram_match("wl_country_code", "BR"))
		{
			nvram_set("wl_country_code", "UZ");
			nvram_set("wl0_country_code", "UZ");
			nvram_set("wl1_country_code", "UZ");
		}
#endif
		if (nvram_match("wl_country_code", "HK") && nvram_match("preferred_lang", ""))
			nvram_set("preferred_lang", "TW");

	/* reserved for Ralink. used as ASUS pin code. */
	dst = (char*)pin;
	bytes = 8;
	if (FRead(dst, OFFSET_PIN_CODE, bytes)<0)
	{
		_dprintf("READ ASUS pin code: Out of scope\n");
		nvram_set("wl_pin_code", "");
	}
	else
	{
		if ((unsigned char)pin[0]!=0xff)
			nvram_set("secret_code", pin);
		else
			nvram_set("secret_code", "12345670");
	}

	dst = buffer;
	bytes = 16;
	if (linuxRead(dst, 0x20, bytes)<0)	/* The "linux" MTD partition, offset 0x20. */
	{
		fprintf(stderr, "READ firmware header: Out of scope\n");
		nvram_set("productid", "unknown");
		nvram_set("firmver", "unknown");
	}
	else
	{
		strncpy(productid, buffer + 4, 12);
		productid[12] = 0;
		sprintf(fwver, "%d.%d.%d.%d", buffer[0], buffer[1], buffer[2], buffer[3]);
		nvram_set("productid", trim_r(productid));
		nvram_set("firmver", trim_r(fwver));
	}

	memset(buffer, 0, sizeof(buffer));
	FRead(buffer, OFFSET_BOOT_VER, 4);
//	sprintf(blver, "%c.%c.%c.%c", buffer[0], buffer[1], buffer[2], buffer[3]);
	sprintf(blver, "%s-0%c-0%c-0%c-0%c", trim_r(productid), buffer[0], buffer[1], buffer[2], buffer[3]);
	nvram_set("blver", trim_r(blver));

	_dprintf("bootloader version: %s\n", nvram_safe_get("blver"));
	_dprintf("firmware version: %s\n", nvram_safe_get("firmver"));

	dst = txbf_para;
	int count_0xff = 0;
	if (FRead(dst, OFFSET_TXBF_PARA, 33) < 0)
	{
		fprintf(stderr, "READ TXBF PARA address: Out of scope\n");
	}
	else
	{
		for (i = 0; i < 33; i++)
		{
			if (txbf_para[i] == 0xff)
				count_0xff++;
/*
			if ((i % 16) == 0) fprintf(stderr, "\n");
			fprintf(stderr, "%02x ", (unsigned char) txbf_para[i]);
*/
		}
/*
		fprintf(stderr, "\n");

		fprintf(stderr, "TxBF parameter 0xFF count: %d\n", count_0xff);
*/
	}

	if (count_0xff == 33)
		nvram_set("wl1_txbf_en", "0");
	else
		nvram_set("wl1_txbf_en", "1");

#if defined (RTCONFIG_WLMODULE_RT3352_INIC_MII)
#define EEPROM_INIC_SIZE (512)
#define EEPROM_INIT_ADDR 0x48000
#define EEPROM_INIT_FILE "/etc/Wireless/iNIC/iNIC_e2p.bin"
	{
		char eeprom[EEPROM_INIC_SIZE];
		if(FRead(eeprom, EEPROM_INIT_ADDR, sizeof(eeprom)) < 0)
		{
			fprintf(stderr, "FRead(eeprom, 0x%08x, 0x%x) failed\n", EEPROM_INIT_ADDR, sizeof(eeprom));
		}
		else
		{
			FILE *fp;
			char *filepath = EEPROM_INIT_FILE;

			system("mkdir -p /etc/Wireless/iNIC/");
			if((fp = fopen(filepath, "w")) == NULL)
			{
				fprintf(stderr, "fopen(%s) failed!!\n", filepath);
			}
			else
			{
				if(fwrite(eeprom, sizeof(eeprom), 1, fp) < 1)
				{
					perror("fwrite(eeprom)");
				}
				fclose(fp);
			}
		}
	}
#endif

#ifdef RA_SINGLE_SKU
#if defined(RTAC52U)
	{
		char *reg_spec;

		reg_spec = nvram_safe_get("reg_spec");
		create_SingleSKU("/etc/Wireless/RT2860", "", reg_spec);
		create_SingleSKU("/etc/Wireless/iNIC", "_5G", reg_spec);
	}
#endif	/* RTAC52U */
#endif	/* RA_SINGLE_SKU */

	{
#ifdef RTCONFIG_ODMPID
		char modelname[16];
		FRead(modelname, OFFSET_ODMPID, sizeof(modelname));
		modelname[sizeof(modelname)-1] = '\0';
		if(modelname[0] != 0 && (unsigned char)(modelname[0]) != 0xff && is_valid_hostname(modelname) && strcmp(modelname, "ASUS"))
		{
			nvram_set("odmpid", modelname);
		}
		else
#endif
			nvram_unset("odmpid");
	}

	nvram_set("firmver", rt_version);
	nvram_set("productid", rt_buildname);
}