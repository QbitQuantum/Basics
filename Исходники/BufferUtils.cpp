void uploadVertexData(const VertexBufferFormat &vbf, const RSXVertexData *vertexData, size_t baseOffset, void* bufferMap)
{
	for (int vertex = 0; vertex < vbf.elementCount; vertex++)
	{
		for (size_t attributeId : vbf.attributeId)
		{
			if (!vertexData[attributeId].addr)
			{
				memcpy(bufferMap, vertexData[attributeId].data.data(), vertexData[attributeId].data.size());
				continue;
			}
			size_t offset = (size_t)vertexData[attributeId].addr + baseOffset - vbf.range.first;
			size_t tsize = vertexData[attributeId].GetTypeSize();
			size_t size = vertexData[attributeId].size;
			auto src = vm::get_ptr<const u8>(vertexData[attributeId].addr + (u32)baseOffset + (u32)vbf.stride * vertex);
			char* dst = (char*)bufferMap + offset + vbf.stride * vertex;

			switch (tsize)
			{
			case 1:
			{
				memcpy(dst, src, size);
				break;
			}

			case 2:
			{
				const u16* c_src = (const u16*)src;
				u16* c_dst = (u16*)dst;
				for (u32 j = 0; j < size; ++j) *c_dst++ = _byteswap_ushort(*c_src++);
				break;
			}

			case 4:
			{
				const u32* c_src = (const u32*)src;
				u32* c_dst = (u32*)dst;
				for (u32 j = 0; j < size; ++j) *c_dst++ = _byteswap_ulong(*c_src++);
				break;
			}
			}
		}
	}
}