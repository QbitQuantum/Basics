    void Update(float dt)
    {
      // Remove all models no longer being referenced.
      for (auto it = models.begin(); it != models.end();)
      {
        if (it->second.unique())
        {
          it = models.erase(it);
        }
        else
        {
          ++it;
        }
      }

      if (!d3d.Context || !d3d.RenderTarget) return;

      // Clear the render target.
      float clearColor [] = { 0.0f, 0.125f, 0.6f, 1.0f };
      d3d.Context->ClearRenderTargetView(d3d.RenderTarget, clearColor);

      // Clear the depth buffer to max depth (1.0).
      d3d.Context->ClearDepthStencilView(d3d.DSView, D3D11_CLEAR_DEPTH, 1, 0);

      // Set the vertex layout for the input assembler stage.
      d3d.Context->IASetInputLayout(inputLayout);
      // Set the render target to the depth-stencil view.
      d3d.Context->OMSetRenderTargets(1, d3d.RenderTarget, d3d.DSView);

      // Some hard-coded light directions and colors.
      XMFLOAT4 lightDirections [] =
      {
        { -.577f, .577f, -.577f, 1 },
        { 0, 0, -1, 1 }
      };
      XMFLOAT4 lightColors [] =
      {
        { 1, 1, 1, 1 },
        { 1, 1, 0, 1 }
      };

      SceneConstants sceneConstants;

      // Update elapsed time.
      static float t = 0.0f;
      static DWORD dwTimeStart = 0;
      DWORD dwTimeCur = GetTickCount();
      if (dwTimeStart == 0)
        dwTimeStart = dwTimeCur;
      t = (dwTimeCur - dwTimeStart) / 1000.0f;

      // Rotate the second light's direction.
      auto rotate = XMMatrixRotationY(-2 * t);
      XMStoreFloat4(&lightDirections[1], XMVector3Transform(XMLoadFloat4(&lightDirections[1]), rotate));

      // Store the view projection and light info in the constant buffer.
      XMStoreFloat4x4(
        &sceneConstants.viewProjection,
        XMMatrixTranspose(
        XMLoadFloat4x4(&Camera.ViewProjectionMatrix())));
      sceneConstants.lightDirections = { lightDirections[0], lightDirections[1] };
      sceneConstants.lightColors = { lightColors[0], lightColors[1] };

      d3d.Context->UpdateSubresource(cbScene, 0, nullptr, &sceneConstants, 0, 0);
      d3d.Context->VSSetConstantBuffers(0, 1, cbScene);
      d3d.Context->PSSetConstantBuffers(0, 1, cbScene);

      // Draw all models.
      for (auto& modelPair : models)
      {
        modelPair.second->Draw();
      }

      // Debug drawing.
      DebugDrawer::Instance().Update();

      // Present the back buffer to the display.
      d3d.SwapChain->Present(0, 0);
    }