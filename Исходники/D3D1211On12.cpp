// Render the scene.
void D3D1211on12::OnRender()
{
	PIXBeginEvent(m_commandQueue.Get(), 0, L"Render 3D");

	// Record all the commands we need to render the scene into the command list.
	PopulateCommandList();

	// Execute the command list.
	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	PIXEndEvent(m_commandQueue.Get());

	PIXBeginEvent(m_commandQueue.Get(), 0, L"Render UI");
	RenderUI();
	PIXEndEvent(m_commandQueue.Get());

	// Present the frame.
	ThrowIfFailed(m_swapChain->Present(1, 0));

	MoveToNextFrame();
}