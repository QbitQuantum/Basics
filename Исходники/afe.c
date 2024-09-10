int afe_disable(u8 path_id)
{
	struct msm_afe_state *afe = &the_afe_state;
	int rc;

	if (path_id < AFE_HW_PATH_CODEC_RX ||
	    path_id > AFE_HW_PATH_MI2S_TX) {
		MM_AUD_ERR("invalid path id %d\n", path_id);
		return -EINVAL;
	}

	mutex_lock(&afe->lock);

	BUG_ON(!afe->in_use);
	MM_AUD_INFO("%s() path_id:%d codec state:%d\n", __func__, path_id,
	afe->codec_config[GETDEVICEID(path_id)]);
	afe_dsp_codec_config(afe, path_id, 0, NULL);
	rc = wait_event_timeout(afe->wait,
		!afe->codec_config[GETDEVICEID(path_id)],
		msecs_to_jiffies(AFE_MAX_TIMEOUT));
	if (!rc) {
		MM_AUD_ERR("AFE failed to respond within %d ms\n",
				AFE_MAX_TIMEOUT);
		rc = -1;
	} else
		rc = 0;
	afe->in_use--;
	MM_AUD_INFO("%s() in_use:%d \n", __func__, afe->in_use);
	if (!afe->in_use) {
		msm_adsp_disable(afe->mod);
		msm_adsp_put(afe->mod);
		afe->aux_conf_flag = 0;
	}
	mutex_unlock(&afe->lock);
	return rc;
}