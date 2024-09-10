void FrameResource::PopulateCommandList(ID3D12GraphicsCommandList* pCommandList, ID3D12PipelineState* pPso,
	UINT frameResourceIndex, UINT numIndices, D3D12_INDEX_BUFFER_VIEW* pIndexBufferViewDesc, D3D12_VERTEX_BUFFER_VIEW* pVertexBufferViewDesc,
	ID3D12DescriptorHeap* pCbvSrvDescriptorHeap, UINT cbvSrvDescriptorSize, ID3D12DescriptorHeap* pSamplerDescriptorHeap, ID3D12RootSignature* pRootSignature)
{
	// If the root signature matches the root signature of the caller, then
	// bindings are inherited, otherwise the bind space is reset.
	pCommandList->SetGraphicsRootSignature(pRootSignature);

	ID3D12DescriptorHeap* ppHeaps[] = { pCbvSrvDescriptorHeap, pSamplerDescriptorHeap };
	pCommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pCommandList->IASetIndexBuffer(pIndexBufferViewDesc);
	pCommandList->IASetVertexBuffers(0, 1, pVertexBufferViewDesc);
	pCommandList->SetGraphicsRootDescriptorTable(0, pCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	pCommandList->SetGraphicsRootDescriptorTable(1, pSamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart());

	// Calculate the descriptor offset due to multiple frame resources.
	// (m_cityMaterialCount + 1) SRVs + how many CBVs we have currently.
	UINT frameResourceDescriptorOffset = (m_cityMaterialCount + 1) + (frameResourceIndex * m_cityRowCount * m_cityColumnCount);
	CD3DX12_GPU_DESCRIPTOR_HANDLE cbvSrvHandle(pCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart(), frameResourceDescriptorOffset, cbvSrvDescriptorSize);

	PIXBeginEvent(pCommandList, 0, L"Draw cities");
	for (UINT i = 0; i < m_cityRowCount; i++)
	{
		for (UINT j = 0; j < m_cityColumnCount; j++)
		{
			pCommandList->SetPipelineState(pPso);

			// Set the city's root constant for dynamically indexing into the material array.
			pCommandList->SetGraphicsRoot32BitConstant(3, (i * m_cityColumnCount) + j, 0);

			// Set this city's CBV table and move to the next descriptor.
			pCommandList->SetGraphicsRootDescriptorTable(2, cbvSrvHandle);
			cbvSrvHandle.Offset(cbvSrvDescriptorSize);

			pCommandList->DrawIndexedInstanced(numIndices, 1, 0, 0, 0);
		}
	}
	PIXEndEvent(pCommandList);
}