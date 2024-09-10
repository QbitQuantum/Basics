static ssize_t reg_write(struct file *file, const char __user *ubuf,
						size_t count, loff_t *ppos)
{
	struct seq_file *s = file->private_data;
	struct mcde_display_device *ddev = s->private;
	struct device *dev;
	struct mcde_chnl_state *chnl;
	char *buf;
	const char *p;
	enum dbg_cmd_type cmd;
	u8 data[MCDE_MAX_DSI_DIRECT_CMD_WRITE + 1]; /* Make room for cmd  */
	int i = 0;
	int ret;
	char tmp[TMP_BUF_SZ];

	if (!ddev || !&ddev->dev) {
		pr_err("%s: no device\n", __func__);
		ret = -ENODEV;
		goto exit;
	}
	chnl = ddev->chnl_state;
	dev = &ddev->dev;

	dev_dbg(dev, "%s\n", __func__);

	reset_res_buf();

	buf = kzalloc(sizeof(char) * count, GFP_KERNEL);
	if (!buf) {
		dev_err(dev, "%s: Failed to allocate buffer\n", __func__);
		ret = -ENOMEM;
		goto exit;
	}

	dev_dbg(dev, "%s: buf = %p, ubuf = %p, count = %d, "
				"sizeof(char) * count = %d, line = %d\n",
		__func__, buf, ubuf, count, sizeof(char) * count, __LINE__);

	if (copy_from_user(buf, ubuf, count)) {
		ret = -EFAULT;
		goto fail_free_mem;
	}

	p = buf;

	if (!strncmp(buf, "dcs", 3)) {
		dev_dbg(dev, "%s: dcs\n", __func__);
		cmd = DCS;
	} else if (!strncmp(buf, "gen", 3)) {
		dev_dbg(dev, "%s: gen\n", __func__);
		cmd = GEN;
	} else {
		update_res_buf("Write - unknown type\n");
		ret = -EFAULT;
		goto fail_free_mem;
	}

	p = p+4;

	/* Get first param, Register */
	if (sscanf(p, "%4hhx", &data[0]) != 1) {
		update_res_buf("Write - parameter error\n");
		ret = -EINVAL;
		goto fail_free_mem;
	}
	i++;

	while (isxdigit(*p) || (*p == 'x'))
		p++;

	/* Get data */
	while (true) {
		if (isspace(*p)) {
			p++;
		} else {
			if (sscanf(p, "%4hhx", &data[i]) == 1) {
				while (isxdigit(*p) || (*p == 'x'))
					p++;
			}
			i++;
		}
		if (iscntrl(*p))
			break;

		if (i > MCDE_MAX_DSI_DIRECT_CMD_WRITE) {
			update_res_buf("Write - Too many parameters\n");
			ret = -EINVAL;
			goto fail_free_mem;
		}
	}

	if (cmd == DCS) {
		if (i == 1)
			ret = mcde_dsi_dcs_write(chnl, data[0], NULL, 0);
		else
			ret = mcde_dsi_dcs_write(chnl, data[0], &data[1],
									i - 1);
	} else {
		ret = mcde_dsi_generic_write(chnl, data, i);
	}

	if (!ret) {
		print_params(cmd, data[0], i - 1, &data[1]);
	} else {
		snprintf(tmp, sizeof(tmp), "Write failed, ret = %d!\n", ret);
		update_res_buf(tmp);
	}

fail_free_mem:
	kfree(buf);
exit:
	return count;
}