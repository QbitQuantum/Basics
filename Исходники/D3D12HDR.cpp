// Fill the command list with all the render commands and dependent state and
// submit it to the command queue.
void D3D12HDR::RenderScene()
{
    // Command list allocators can only be reset when the associated
    // command lists have finished execution on the GPU; apps should use
    // fences to determine GPU execution progress.
    ThrowIfFailed(m_commandAllocators[m_frameIndex]->Reset());

    // However, when ExecuteCommandList() is called on a particular command
    // list, that command list can then be reset at any time and must be before
    // re-recording.
    ThrowIfFailed(m_commandList->Reset(m_commandAllocators[m_frameIndex].Get(), m_pipelineStates[GradientPSO].Get()));

    if (m_updateVertexBuffer)
    {
        UpdateVertexBuffer();
        m_updateVertexBuffer = false;
    }

    // Set necessary state.
    m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());

    ID3D12DescriptorHeap* ppHeaps[] = { m_srvHeap.Get() };
    m_commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

    m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    m_commandList->RSSetViewports(1, &m_viewport);
    m_commandList->RSSetScissorRects(1, &m_scissorRect);

    // Bind the root constants and the SRV table to the pipeline.
    m_rootConstantsF[ReferenceWhiteNits] = m_referenceWhiteNits;

    m_commandList->SetGraphicsRoot32BitConstants(0, RootConstantsCount, m_rootConstants, 0);
    m_commandList->SetGraphicsRootDescriptorTable(1, m_srvHeap->GetGPUDescriptorHandleForHeapStart());

    // Draw the scene into the intermediate render target.
    {
        PIXBeginEvent(m_commandList.Get(), 0, L"Draw scene content");

        CD3DX12_CPU_DESCRIPTOR_HANDLE intermediateRtv(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), FrameCount, m_rtvDescriptorSize);
        m_commandList->OMSetRenderTargets(1, &intermediateRtv, FALSE, nullptr);

        const float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        m_commandList->ClearRenderTargetView(intermediateRtv, clearColor, 0, nullptr);

        m_commandList->IASetVertexBuffers(0, 1, &m_gradientVertexBufferView);
        PIXBeginEvent(m_commandList.Get(), 0, L"Standard Gradient");
        m_commandList->DrawInstanced(4, 1, 0, 0);
        PIXEndEvent(m_commandList.Get());

        PIXBeginEvent(m_commandList.Get(), 0, L"Bright Gradient");
        m_commandList->DrawInstanced(4, 1, 4, 0);
        PIXEndEvent(m_commandList.Get());

        m_commandList->SetPipelineState(m_pipelineStates[PalettePSO].Get());
        m_commandList->IASetVertexBuffers(0, 1, &m_trianglesVertexBufferView);
        m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        PIXBeginEvent(m_commandList.Get(), 0, L"Rec709 Triangles");
        m_commandList->DrawInstanced(3, 1, 0, 0);
        m_commandList->DrawInstanced(3, 1, 3, 0);
        m_commandList->DrawInstanced(3, 1, 6, 0);
        PIXEndEvent(m_commandList.Get());

        m_commandList->SetPipelineState(m_pipelineStates[PalettePSO].Get());
        PIXBeginEvent(m_commandList.Get(), 0, L"Rec2020 Triangles");
        m_commandList->DrawInstanced(3, 1, 9, 0);
        m_commandList->DrawInstanced(3, 1, 12, 0);
        m_commandList->DrawInstanced(3, 1, 15, 0);
        PIXEndEvent(m_commandList.Get());

        PIXEndEvent(m_commandList.Get());

        if (!m_enableUI)
        {
            intermediateRtv.Offset(1, m_rtvDescriptorSize);
            m_commandList->OMSetRenderTargets(1, &intermediateRtv, FALSE, nullptr);
            m_commandList->ClearRenderTargetView(intermediateRtv, clearColor, 0, nullptr);
        }
    }

    // Indicate that the intermediates will be used as SRVs in the pixel shader
    // and the back buffer will be used as a render target.
    D3D12_RESOURCE_BARRIER barriers[] = {
        CD3DX12_RESOURCE_BARRIER::Transition(m_intermediateRenderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
        CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET),
        CD3DX12_RESOURCE_BARRIER::Transition(m_UIRenderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
    };

    // Process the intermediate and draw into the swap chain render target.
    {
        PIXBeginEvent(m_commandList.Get(), 0, L"Apply HDR");

        // If the UI is enabled, the 11on12 layer will do the state transition for us.
        UINT barrierCount = m_enableUI ? 2 : _countof(barriers);
        m_commandList->ResourceBarrier(barrierCount, barriers);
        m_commandList->SetPipelineState(m_pipelineStates[Present8bitPSO + m_currentSwapChainBitDepth].Get());

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
        m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

        m_commandList->ClearRenderTargetView(rtvHandle, ClearColor, 0, nullptr);

        m_commandList->IASetVertexBuffers(0, 1, &m_presentVertexBufferView);
        m_commandList->DrawInstanced(3, 1, 0, 0);

        PIXEndEvent(m_commandList.Get());
    }

    // Indicate that the intermediates will be used as render targets and the swap chain
    // back buffer will be used for presentation.
    barriers[0].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    barriers[0].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barriers[1].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barriers[1].Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barriers[2].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    barriers[2].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

    m_commandList->ResourceBarrier(_countof(barriers), barriers);

    ThrowIfFailed(m_commandList->Close());

    // Execute the command list.
    ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
    m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}