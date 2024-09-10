/*
 * General handler for setting values in config files.
 *
 * @param context	The main context pointer
 * @param token  	The parse token value
 * @param value  	The value to set
 * @return 0 for success
 */
int context_set_value(build_image_context *context,
		parse_token token,
		u_int32_t value)
{
	assert(context != NULL);

	switch (token) {
	case token_attribute:
		context->newbl_attr = value;
		break;

	case token_block_size:
		context->block_size = value;
		context->block_size_log2 = log2(value);

		if (context->memory != NULL) {
			printf("Error: Too late to change block size.\n");
			return 1;
		}

		if (value != (u_int32_t)(1 << context->block_size_log2)) {
			printf("Error: Block size must be a power of 2.\n");
			return 1;
		}
		context->pages_per_blk= 1 << (context->block_size_log2-
				context->page_size_log2);
		g_soc_config->set_value(token_block_size_log2,
			context->block_size_log2, context->bct);
		break;

	case token_partition_size:
		if (context->memory != NULL) {
			printf("Error: Too late to change block size.\n");
			return 1;
		}

		context->partition_size= value;
		g_soc_config->set_value(token_partition_size,
			value, context->bct);
		break;

	case token_page_size:
		context->page_size = value;
		context->page_size_log2 = log2(value);
		context->pages_per_blk= 1 << (context->block_size_log2-
			context->page_size_log2);

		g_soc_config->set_value(token_page_size_log2,
			context->page_size_log2, context->bct);
		break;
	case token_redundancy:
		context->redundancy = value;
		break;

	case token_version:
		context->version = value;
		break;

	case token_bct_copy:
		context->bct_copy = value;
		break;

	case token_odm_data:
		context->odm_data = value;
		break;

	case token_pre_bct_pad_blocks:
		if (context->bct_init) {
			printf("Error: Too late to pre-BCT pad.\n");
			return 1;
		}
		context->pre_bct_pad_blocks = value;
		break;

	DEFAULT();
	}

	return 0;
}