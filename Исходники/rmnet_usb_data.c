static ssize_t dbg_mask_show(struct device *d,
		struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", data_msg_dbg_mask);
}