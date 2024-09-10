/**
* @brief
* @param
* @see
* @remarks
* @code
* @endcode
* @return
**/
bool
file_copy_using_memory_map(
_In_ const wchar_t* src_file,
_In_ const wchar_t* dst_file
)
{
	_ASSERTE(NULL != src_file);
	_ASSERTE(NULL != dst_file);
	if (NULL == src_file || NULL == dst_file) return false;

	if (!is_file_existsW(src_file))
	{
		print("err ] no src file = %ws", src_file);
		return false;
	}

	if (is_file_existsW(dst_file))
	{
		DeleteFileW(dst_file);
	}

	// map src, dst file
	pmap_context src_ctx = open_map_context(src_file);
	pmap_context dst_ctx = create_map_context(dst_file, src_ctx->size);
	if (NULL == src_ctx || NULL == dst_ctx)
	{
		print("err ] open_map_context() failed.");
		close_map_context(src_ctx);
		close_map_context(dst_ctx);
		return false;
	}

	// copy src to dst by mmio
	for (uint32_t i = 0; i < src_ctx->size; ++i)
	{
		dst_ctx->view[i] = src_ctx->view[i];
	}

	close_map_context(src_ctx);
	close_map_context(dst_ctx);
	
	return true;
}