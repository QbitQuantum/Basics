// Render the scene.
void D3D12DynamicIndexing::OnRender()
{
	PIXBeginEvent(m_commandQueue.Get(), 0, L"Render");

	// Record all the commands we need to render the scene into the command list.
	PopulateCommandList(m_pCurrentFrameResource);

	// Execute the command list.
	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	PIXEndEvent(m_commandQueue.Get());

	// Present and update the frame index for the next frame.
	ThrowIfFailed(m_swapChain->Present(1, 0));
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	// Signal and increment the fence value.
	m_pCurrentFrameResource->m_fenceValue = m_fenceValue;
	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), m_fenceValue));
	m_fenceValue++;
}