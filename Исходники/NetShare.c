NET_API_STATUS netapitest_share(struct libnetapi_ctx *ctx,
				const char *hostname)
{
	NET_API_STATUS status = 0;
	const char *sharename, *comment;
	uint8_t *buffer = NULL;
	struct SHARE_INFO_2 i2;
	struct SHARE_INFO_502 i502;
	struct SHARE_INFO_1004 i1004;
	struct SHARE_INFO_501 *i501 = NULL;
	uint32_t parm_err = 0;
	uint32_t levels[] = { 0, 1, 2, 501, 1005 };
	uint32_t enum_levels[] = { 0, 1, 2 };
	int i;

	printf("NetShare tests\n");

	sharename = "torture_test_share";

	/* cleanup */
	NetShareDel(hostname, sharename, 0);

	/* add a share */

	printf("testing NetShareAdd\n");

	ZERO_STRUCT(i502);

	i502.shi502_netname = sharename;
	i502.shi502_path = "c:\\";

	status = NetShareAdd(hostname, 502, (uint8_t *)&i502, &parm_err);
	if (status) {
		NETAPI_STATUS(ctx, status, "NetShareAdd");
		goto out;
	};

	status = NetShareDel(hostname, sharename, 0);
	if (status) {
		NETAPI_STATUS(ctx, status, "NetShareDel");
		goto out;
	};

	ZERO_STRUCT(i2);

	i2.shi2_netname = sharename;
	i2.shi2_path = "c:\\";

	status = NetShareAdd(hostname, 2, (uint8_t *)&i2, &parm_err);
	if (status) {
		NETAPI_STATUS(ctx, status, "NetShareAdd");
		goto out;
	};

	/* test enum */

	for (i=0; i<ARRAY_SIZE(enum_levels); i++) {

		status = test_netshareenum(hostname, enum_levels[i], sharename);
		if (status) {
			NETAPI_STATUS(ctx, status, "NetShareEnum");
			goto out;
		}
	}

	/* basic queries */

	for (i=0; i<ARRAY_SIZE(levels); i++) {

		printf("testing NetShareGetInfo level %d\n", levels[i]);

		status = NetShareGetInfo(hostname, sharename, levels[i], &buffer);
		if (status && status != 124) {
			NETAPI_STATUS(ctx, status, "NetShareGetInfo");
			goto out;
		}
	}


	comment = "NetApi generated comment";

	i1004.shi1004_remark = comment;

	printf("testing NetShareSetInfo level 1004\n");

	status = NetShareSetInfo(hostname, sharename, 1004, (uint8_t *)&i1004, &parm_err);
	if (status) {
		NETAPI_STATUS(ctx, status, "NetShareSetInfo");
		goto out;
	}

	status = NetShareGetInfo(hostname, sharename, 501, (uint8_t **)&i501);
	if (status) {
		NETAPI_STATUS(ctx, status, "NetShareGetInfo");
		goto out;
	}

	if (strcasecmp(i501->shi501_remark, comment) != 0) {
		NETAPI_STATUS(ctx, status, "NetShareGetInfo");
		goto out;
	}

	/* delete */

	printf("testing NetShareDel\n");

	status = NetShareDel(hostname, sharename, 0);
	if (status) {
		NETAPI_STATUS(ctx, status, "NetShareDel");
		goto out;
	};

	/* should not exist anymore */

	status = NetShareGetInfo(hostname, sharename, 0, &buffer);
	if (status == 0) {
		NETAPI_STATUS(ctx, status, "NetShareGetInfo");
		goto out;
	};

	status = 0;

	printf("NetShare tests succeeded\n");
 out:
	if (status != 0) {
		printf("NetShare testsuite failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
	}

	return status;
}