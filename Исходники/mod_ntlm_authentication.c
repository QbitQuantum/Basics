/* setting up/initalizing the connection details */
static int set_connection_details(sspi_auth_ctx* ctx)
{
	SECURITY_STATUS ss;

	if (ctx->scr->username == NULL) {
		ctx->scr->username = get_username_from_context(ctx->r->connection->pool, sspiModuleInfo.functable, 
			&ctx->scr->server_context);
	}

	if (ctx->scr->username == NULL)
		return HTTP_INTERNAL_SERVER_ERROR;
	else
		construct_username(ctx);

	if (ctx->r->user == NULL) {
		ctx->r->user = ctx->scr->username;
		ctx->r->ap_auth_type = ctx->scr->package;
	}

	if (ctx->scr->usertoken == NULL) {
		if ((ss = sspiModuleInfo.functable->ImpersonateSecurityContext(&ctx->scr->server_context)) != SEC_E_OK) {
			return HTTP_INTERNAL_SERVER_ERROR;
		}

		if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY_SOURCE | TOKEN_READ, TRUE, &ctx->scr->usertoken)) {
			sspiModuleInfo.functable->RevertSecurityContext(&ctx->scr->server_context);
			return HTTP_INTERNAL_SERVER_ERROR;
		}

		if ((ss = sspiModuleInfo.functable->RevertSecurityContext(&ctx->scr->server_context)) != SEC_E_OK) {
			return HTTP_INTERNAL_SERVER_ERROR;
		}
	}

	return OK;
}