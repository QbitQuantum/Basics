void cmd_boot(const char *arg, void *data, unsigned sz)
{
	unsigned kernel_actual;
	unsigned ramdisk_actual;
	static struct boot_img_hdr hdr;
	char *ptr = ((char*) data);
   unsigned page_size = 0;
   unsigned page_mask = 0;
   int strlen = 0;

	if (sz < sizeof(hdr)) {
		fastboot_fail("invalid bootimage header");
		return;
	}

	memcpy(&hdr, data, sizeof(hdr));

  printf("\n============================================================\n");
	hdr.magic[7] = '\0';
  printf("[%s] Android Boot IMG Hdr - Magic 	        : %s\n",MODULE_NAME,hdr.magic);
  printf("[%s] Android Boot IMG Hdr - Kernel Size 	: 0x%x\n",MODULE_NAME,hdr.kernel_size);
  printf("[%s] Android Boot IMG Hdr - Rootfs Size 	: 0x%x\n",MODULE_NAME,hdr.ramdisk_size);
  printf("[%s] Android Boot IMG Hdr - Page Size    	: 0x%x\n",MODULE_NAME,hdr.page_size);
  printf("============================================================\n");

	/* ensure commandline is terminated */
	hdr.cmdline[BOOT_ARGS_SIZE-1] = 0;

	if(hdr.page_size) {
		page_size = hdr.page_size;
		page_mask = page_size - 1;
		//page_mask = 2*1024 ; /*FIXME*/
	}
   else
   {
     printf("[FASTBOOT] Please specify the storage page-size in the boot header!\n");
     fastboot_fail("Please specify the storage page-size in the boot header!\n");
     return;
   }

	kernel_actual = ROUND_TO_PAGE(hdr.kernel_size, page_mask);
	ramdisk_actual = ROUND_TO_PAGE(hdr.ramdisk_size, page_mask);

	/* sz should have atleast raw boot image */
	if (page_size + kernel_actual + ramdisk_actual > sz) {
		fastboot_fail("incomplete bootimage");
		return;
	}

	memmove((void*) hdr.kernel_addr, (ptr + MKIMG_HEADER_SZ + BIMG_HEADER_SZ), hdr.kernel_size);
	memmove((void*) hdr.ramdisk_addr, (ptr + MKIMG_HEADER_SZ + BIMG_HEADER_SZ + kernel_actual), hdr.ramdisk_size);

  strlen += sprintf((const char*) hdr.cmdline, "%s lcm=%1d-%s", hdr.cmdline, DISP_IsLcmFound(), mt_disp_get_lcm_id());
  strlen += sprintf((const char*) hdr.cmdline, "%s fps=%1d", hdr.cmdline, mt_disp_get_lcd_time());

	fastboot_okay("");
	udc_stop();
   mtk_wdt_init(); //re-open wdt

  g_boot_mode = NORMAL_BOOT;

	boot_linux((void*) hdr.kernel_addr, (void*) hdr.tags_addr,
		   (const char*) hdr.cmdline, board_machtype(),
		   (void*) hdr.ramdisk_addr, hdr.ramdisk_size);
#if 0
  unsigned kernel_actual;
  unsigned ramdisk_actual;
  struct boot_img_hdr boot_hdr;
  unsigned int k_pg_cnt = 0;
  unsigned int r_pg_cnt = 0;
  unsigned int b_pg_cnt = 0;
  unsigned int size_b = 0;
  unsigned int pg_sz = 2*1024 ;
  int strlen = 0;

  /*copy hdr data from download_base*/
  memcpy(&boot_hdr, data, sizeof(boot_hdr));

  /* ensure commandline is terminated */
  boot_hdr.cmdline[BOOT_ARGS_SIZE-1] = 0;

  printf("\n============================================================\n");
	boot_hdr.magic[7] = '\0';
  printf("[%s] Android Boot IMG Hdr - Magic 	        : %s\n",MODULE_NAME,boot_hdr.magic);
  printf("[%s] Android Boot IMG Hdr - Kernel Size 	: 0x%x\n",MODULE_NAME,boot_hdr.kernel_size);
  printf("[%s] Android Boot IMG Hdr - Rootfs Size 	: 0x%x\n",MODULE_NAME,boot_hdr.ramdisk_size);
  printf("[%s] Android Boot IMG Hdr - Page Size    	: 0x%x\n",MODULE_NAME,boot_hdr.page_size);
  printf("============================================================\n");

  //***************
  //* check partition magic
  //*
  if (strncmp(boot_hdr.magic,BOOT_MAGIC, sizeof(BOOT_MAGIC))!=0) {
    printf("[%s] boot image header magic error\n", MODULE_NAME);
    return -1;
  }

  g_kmem_off =  (unsigned int)target_get_scratch_address();
  g_kmem_off = g_kmem_off + MKIMG_HEADER_SZ + BIMG_HEADER_SZ;


  if(boot_hdr.kernel_size % pg_sz == 0)
  {
    k_pg_cnt = boot_hdr.kernel_size / pg_sz;
  }
  else
  {
    k_pg_cnt = (boot_hdr.kernel_size / pg_sz) + 1;
  }

  if(boot_hdr.ramdisk_size % pg_sz == 0)
  {
    r_pg_cnt = boot_hdr.ramdisk_size / pg_sz;
  }
  else
  {
    r_pg_cnt = (boot_hdr.ramdisk_size / pg_sz) + 1;
  }

  printf(" > page count of kernel image = %d\n",k_pg_cnt);
  g_rmem_off = g_kmem_off + k_pg_cnt * pg_sz;

  printf(" > kernel mem offset = 0x%x\n",g_kmem_off);
  printf(" > rootfs mem offset = 0x%x\n",g_rmem_off);

  //***************
  //* specify boot image size
  //*
  g_bimg_sz = (k_pg_cnt + r_pg_cnt + 2)* pg_sz;
  printf(" > boot image size = 0x%x\n",g_bimg_sz);

  memmove((void*)CFG_BOOTIMG_LOAD_ADDR , g_kmem_off, boot_hdr.kernel_size);
  memmove((void*)CFG_RAMDISK_LOAD_ADDR , g_rmem_off, boot_hdr.ramdisk_size);

  //custom_port_in_kernel(g_boot_mode, commanline);
  //strlen += sprintf(commanline, "%s lcm=%1d-%s", commanline, DISP_IsLcmFound(), mt_disp_get_lcm_id());
  //strlen += sprintf(commanline, "%s fps=%1d", commanline, mt_disp_get_lcd_time());

  fastboot_okay("");

  udc_stop();

  mtk_wdt_init();
  boot_linux((void *)CFG_BOOTIMG_LOAD_ADDR, (unsigned *)CFG_BOOTARGS_ADDR,
		   (const char*) boot_hdr.cmdline, board_machtype(),
		   (void *)CFG_RAMDISK_LOAD_ADDR, boot_hdr.ramdisk_size);
#endif
}