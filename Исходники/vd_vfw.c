// uninit driver
static void uninit(sh_video_t *sh){
    HRESULT ret;
    vd_vfw_ctx *priv = sh->context;

#ifdef BUILD_VFWEX
    ret = ICDecompressEndEx(priv->handle);
#else
    ret = ICDecompressEnd(priv->handle);
#endif
    if (ret)
    {
	mp_msg(MSGT_WIN32, MSGL_WARN, "ICDecompressEnd failed: %ld\n", ret);
	return;
    }

    ret = ICClose(priv->handle);
    if (ret)
    {
	mp_msg(MSGT_WIN32, MSGL_WARN, "ICClose failed: %ld\n", ret);
	return;
    }

    free(priv->o_bih);
    free(priv);
}