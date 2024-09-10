static NET_API_STATUS test_netusermodals(struct torture_context *tctx,
					 struct libnetapi_ctx *ctx,
					 const char *hostname)
{
	NET_API_STATUS status;
	struct USER_MODALS_INFO_0 *u0 = NULL;
	struct USER_MODALS_INFO_0 *_u0 = NULL;
	uint8_t *buffer = NULL;
	uint32_t parm_err = 0;
	uint32_t levels[] = { 0, 1, 2, 3 };
	int i = 0;

	for (i=0; i<ARRAY_SIZE(levels); i++) {

		torture_comment(tctx, "Testing NetUserModalsGet level %d\n", levels[i]);

		status = NetUserModalsGet(hostname, levels[i], &buffer);
		if (status) {
			NETAPI_STATUS(tctx, ctx, status, "NetUserModalsGet");
			return status;
		}
	}

	status = NetUserModalsGet(hostname, 0, (uint8_t **)&u0);
	if (status) {
		NETAPI_STATUS(tctx, ctx, status, "NetUserModalsGet");
		return status;
	}

	torture_comment(tctx, "Testing NetUserModalsSet\n");

	status = NetUserModalsSet(hostname, 0, (uint8_t *)u0, &parm_err);
	if (status) {
		NETAPI_STATUS(tctx, ctx, status, "NetUserModalsSet");
		return status;
	}

	status = NetUserModalsGet(hostname, 0, (uint8_t **)&_u0);
	if (status) {
		NETAPI_STATUS(tctx, ctx, status, "NetUserModalsGet");
		return status;
	}

	if (memcmp(u0, _u0, sizeof(*u0)) != 0) {
		torture_comment(tctx, "USER_MODALS_INFO_0 struct has changed!!!!\n");
		return -1;
	}

	return 0;
}