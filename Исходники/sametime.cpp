static int sametime_proto_uninit(PROTO_INTERFACE* ppro)
{
	CSametimeProto* proto = (CSametimeProto*)ppro;
	g_Instances.remove(proto);
	delete proto;
	return 0;
}