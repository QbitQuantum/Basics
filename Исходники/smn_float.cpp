static cell_t GetURandomFloat(IPluginContext *ctx, const cell_t *params)
{
	MTRand *randobj = s_RandHelpers.RandObjForPlugin(ctx);
	return sp_ftoc((float)randobj->rand());
}