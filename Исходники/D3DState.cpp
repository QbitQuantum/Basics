	void StateManager::Apply()
	{
		if (!m_blendStates.empty())
		{
			if (m_currentBlendState != m_blendStates.top().get())
			{
				m_currentBlendState = (ID3D11BlendState*)m_blendStates.top().get();
				D3D::context->OMSetBlendState(m_currentBlendState, nullptr, 0xFFFFFFFF);
			}
		}
		else ERROR_LOG(VIDEO, "Tried to apply without blend state!");

		if (!m_depthStates.empty())
		{
			if (m_currentDepthState != m_depthStates.top().get())
			{
				m_currentDepthState = (ID3D11DepthStencilState*)m_depthStates.top().get();
				D3D::context->OMSetDepthStencilState(m_currentDepthState, 0);
			}
		}
		else ERROR_LOG(VIDEO, "Tried to apply without depth state!");

		if (!m_rasterizerStates.empty())
		{
			if (m_currentRasterizerState != m_rasterizerStates.top().get())
			{
				m_currentRasterizerState = (ID3D11RasterizerState*)m_rasterizerStates.top().get();
				D3D::context->RSSetState(m_currentRasterizerState);
			}
		}
		else ERROR_LOG(VIDEO, "Tried to apply without rasterizer state!");

		if (!m_dirtyFlags)
		{
			return;
		}		

		if (m_dirtyFlags & DirtyFlag_Constants)
		{
			if (use_partial_buffer_update)
			{
				if (m_dirtyFlags & DirtyFlag_PixelConstants)
				{
					if (m_pending.pixelConstantsSize[0] == 0 && m_pending.pixelConstantsSize[1] == 0)
					{
						D3D::context->PSSetConstantBuffers(0,  m_pending.pixelConstants[1] ? 2 : 1, m_pending.pixelConstants);
					}
					else
					{
						D3D::context1->PSSetConstantBuffers1(0, 1, m_pending.pixelConstants, m_pending.pixelConstantsOffset, m_pending.pixelConstantsSize);
					}
					m_current.pixelConstants[0] = m_pending.pixelConstants[0];
					m_current.pixelConstantsOffset[0] = m_pending.pixelConstantsOffset[0];
					m_current.pixelConstantsSize[0] = m_pending.pixelConstantsSize[0];
					m_current.pixelConstants[1] = m_pending.pixelConstants[1];
					m_current.pixelConstantsOffset[1] = m_pending.pixelConstantsOffset[1];
					m_current.pixelConstantsSize[1] = m_pending.pixelConstantsSize[1];
				}
				if (m_dirtyFlags & DirtyFlag_VertexConstants)
				{
					if (m_pending.vertexConstantsSize == 0)
					{
						D3D::context1->VSSetConstantBuffers(0, 1, &m_pending.vertexConstants);
					}
					else
					{
						D3D::context1->VSSetConstantBuffers1(0, 1, &m_pending.vertexConstants, &m_pending.vertexConstantsOffset, &m_pending.vertexConstantsSize);
					}
					m_current.vertexConstants = m_pending.vertexConstants;
					m_current.vertexConstantsOffset = m_pending.vertexConstantsOffset;
					m_current.vertexConstantsSize = m_pending.vertexConstantsSize;
				}
				if (m_dirtyFlags & DirtyFlag_GeometryConstants)
				{
					if (m_pending.geometryConstantsSize == 0)
					{
						D3D::context->GSSetConstantBuffers(0, 1, &m_pending.geometryConstants);
					}
					else
					{
						D3D::context1->GSSetConstantBuffers1(0, 1, &m_pending.geometryConstants, &m_pending.geometryConstantsOffset, &m_pending.geometryConstantsSize);
					}
					m_current.geometryConstants = m_pending.geometryConstants;
					m_current.geometryConstantsOffset = m_pending.geometryConstantsOffset;
					m_current.geometryConstantsSize = m_pending.geometryConstantsSize;
				}
				if (m_dirtyFlags & DirtyFlag_HullDomainConstants)
				{
					if (m_pending.hulldomainConstantsSize == 0)
					{
						D3D::context->HSSetConstantBuffers(0, 1, &m_pending.hulldomainConstants);
						D3D::context->DSSetConstantBuffers(0, 1, &m_pending.hulldomainConstants);
					}
					else
					{
						D3D::context1->HSSetConstantBuffers1(0, 1, &m_pending.hulldomainConstants, &m_pending.hulldomainConstantsOffset, &m_pending.hulldomainConstantsSize);
						D3D::context1->DSSetConstantBuffers1(0, 1, &m_pending.hulldomainConstants, &m_pending.hulldomainConstantsOffset, &m_pending.hulldomainConstantsSize);
					}
					m_current.hulldomainConstants = m_pending.hulldomainConstants;
					m_current.hulldomainConstantsOffset = m_pending.hulldomainConstantsOffset;
					m_current.hulldomainConstantsSize = m_pending.hulldomainConstantsSize;
				}

			}
			else
			{
				if (m_dirtyFlags & DirtyFlag_PixelConstants)
				{
					D3D::context->PSSetConstantBuffers(0,  m_pending.pixelConstants[1] ? 2 : 1, m_pending.pixelConstants);
					m_current.pixelConstants[0] = m_pending.pixelConstants[0];
					m_current.pixelConstants[1] = m_pending.pixelConstants[1];
				}
				if (m_dirtyFlags & DirtyFlag_VertexConstants)
				{
					D3D::context->VSSetConstantBuffers(0, 1, &m_pending.vertexConstants);
					m_current.vertexConstants = m_pending.vertexConstants;
				}
				if (m_dirtyFlags & DirtyFlag_GeometryConstants)
				{
					D3D::context->GSSetConstantBuffers(0, 1, &m_pending.geometryConstants);
					m_current.geometryConstants = m_pending.geometryConstants;
				}
				if (m_dirtyFlags & DirtyFlag_HullDomainConstants)
				{
					if (g_ActiveConfig.backend_info.bSupportsTessellation)
					{
						D3D::context->HSSetConstantBuffers(0, 1, &m_pending.hulldomainConstants);
						D3D::context->DSSetConstantBuffers(0, 1, &m_pending.hulldomainConstants);
					}
					m_current.hulldomainConstants = m_pending.hulldomainConstants;
				}
			}
		}

		if (m_dirtyFlags & (DirtyFlag_Buffers | DirtyFlag_InputAssembler))
		{
			if (m_dirtyFlags & DirtyFlag_VertexBuffer)
			{
				D3D::context->IASetVertexBuffers(0, 1, &m_pending.vertexBuffer, &m_pending.vertexBufferStride, &m_pending.vertexBufferOffset);
				m_current.vertexBuffer = m_pending.vertexBuffer;
				m_current.vertexBufferStride = m_pending.vertexBufferStride;
				m_current.vertexBufferOffset = m_pending.vertexBufferOffset;
			}

			if (m_dirtyFlags & DirtyFlag_IndexBuffer)
			{
				D3D::context->IASetIndexBuffer(m_pending.indexBuffer, DXGI_FORMAT_R16_UINT, 0);
				m_current.indexBuffer = m_pending.indexBuffer;
			}

			if (m_current.topology != m_pending.topology)
			{
				D3D::context->IASetPrimitiveTopology(m_pending.topology);
				m_current.topology = m_pending.topology;
			}

			if (m_current.inputLayout != m_pending.inputLayout)
			{
				D3D::context->IASetInputLayout(m_pending.inputLayout);
				m_current.inputLayout = m_pending.inputLayout;
			}
		}
		u32 dirty_elements = m_dirtyFlags & DirtyFlag_Textures;
		if (dirty_elements)
		{
			while (dirty_elements)
			{
				unsigned long index;
				_BitScanForward(&index, dirty_elements);
				D3D::context->PSSetShaderResources(index, 1, &m_pending.textures[index]);
				D3D::context->DSSetShaderResources(index, 1, &m_pending.textures[index]);
				m_current.textures[index] = m_pending.textures[index];
				dirty_elements &= ~(1 << index);
			}
		}
		dirty_elements = (m_dirtyFlags & DirtyFlag_Samplers) >> 8;
		if (dirty_elements)
		{
			while (dirty_elements)
			{
				unsigned long index;
				_BitScanForward(&index, dirty_elements);
				D3D::context->PSSetSamplers(index, 1, &m_pending.samplers[index]);
				D3D::context->DSSetSamplers(index, 1, &m_pending.samplers[index]);
				m_current.samplers[index] = m_pending.samplers[index];
				dirty_elements &= ~(1 << index);
			}
		}

		if (m_dirtyFlags & DirtyFlag_Shaders)
		{
			if (m_current.pixelShader != m_pending.pixelShader)
			{
				D3D::context->PSSetShader(m_pending.pixelShader, nullptr, 0);
				m_current.pixelShader = m_pending.pixelShader;
			}

			if (m_current.vertexShader != m_pending.vertexShader)
			{
				D3D::context->VSSetShader(m_pending.vertexShader, nullptr, 0);
				m_current.vertexShader = m_pending.vertexShader;
			}

			if (m_current.geometryShader != m_pending.geometryShader)
			{
				D3D::context->GSSetShader(m_pending.geometryShader, nullptr, 0);
				m_current.geometryShader = m_pending.geometryShader;
			}
			if (g_ActiveConfig.backend_info.bSupportsTessellation)
			{
				if (m_current.hullShader != m_pending.hullShader)
				{
					D3D::context->HSSetShader(m_pending.hullShader, nullptr, 0);
					m_current.hullShader = m_pending.hullShader;
				}

				if (m_current.domainShader != m_pending.domainShader)
				{
					D3D::context->DSSetShader(m_pending.domainShader, nullptr, 0);
					m_current.domainShader = m_pending.domainShader;
				}
			}
		}

		m_dirtyFlags = 0;
	}