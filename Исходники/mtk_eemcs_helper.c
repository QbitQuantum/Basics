void get_ext_md_post_fix(int md_id, char buf[], char buf_ex[])
{
	// name format: modem_X_YYY_Z_Ex.img
	int		X, Ex;
	char		YYY[8];
#if defined(DFO_FEATURE_EN)
	unsigned int	feature_val = 0;
#endif

  if (md_id < MD_SYS5) {
    printk("[EEMCS]wrong MD ID to get postfix %d\n", md_id);
    return;
  }

	// X
	X = md_id + 1;

#if defined(DFO_FEATURE_EN)
	// DFO start -------------------
	// YYY
	YYY[0] = '\0';
	switch(md_id) {
  	case MD_SYS5:
  		feature_val = ext_md_support[MD_SYS5-MD_EXT1];
  		break;
  	default:
      printk("[EEMCS]request MD ID %d not supported\n", md_id);
  		break;
	}
	switch(feature_val) {
  	case modem_lwg:
  		snprintf(YYY, 8, "_lwg_n");
  		break;
  	case modem_ltg:
  		snprintf(YYY, 8, "_ltg_n");
  		break;
  	default:
  		printk("[EEMCS]request MD type %d not supported\n", feature_val);
  		break;
	}
	// DFO end ---------------------
#else
	// Static start -------------------
	// YYY
	snprintf(YYY, 8, "_lwg_n");
	// Static end ---------------------
#endif

	// [_Ex] Get chip version
#if 0
	if(get_chip_version() == CHIP_SW_VER_01)
		Ex = 1;
	else if(get_chip_version() == CHIP_SW_VER_02)
		Ex = 2;
#else
	Ex = 1;
#endif

	// Gen post fix
	if(buf) {
		snprintf(buf, 12, "%d%s", X, YYY);
    printk("[EEMCS]MD%d image postfix=%s\n", md_id, buf);
	}

	if(buf_ex) {
		snprintf(buf_ex, 12, "%d%s_E%d", X, YYY, Ex);
    printk("[EEMCS]MD%d image postfix=%s\n", md_id, buf_ex);
	}
}