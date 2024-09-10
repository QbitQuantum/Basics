int uuuid_is_nil(struct uuuid_t* uuuid, int* status)
{
	RPC_STATUS st;
	int ret;

	ret = UuidIsNil(&uuuid->uuid, &st);

	if (st != RPC_S_OK) {
		*status = UUUID_ERR;
		return -1;
	}

	*status = UUUID_OK;

	return ret;
}