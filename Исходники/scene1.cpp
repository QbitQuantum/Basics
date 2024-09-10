int MainScene1::Initialize(aurora::Engine* engine) { 
  GameView::Initialize(engine);
  
  //core::delegation::one::pair<graphics::Effect,int,void> p(&main_effect_,0);
  func.Bind<graphics::Effect>(main_effect_,&graphics::Effect::Begin);
  func = core::delegation::none::pair<graphics::Effect,int>(main_effect_,&graphics::Effect::Begin);

  aurora::resource::EffectResource* res = engine_->resource_manager.GetResourceById<aurora::resource::EffectResource>(2);
  main_effect_ = res->effect();
  /*main_effect_.Initialize(&engine_->gfx_context());
  int hr;
  hr = main_effect_.CreateFromMemory(res->data_pointer,res->data_length);
  if (FAILED(hr)) {
    return hr;
  }*/
  int hr;

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
  XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
  XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
  camera_.view() = XMMatrixLookAtLH( Eye, At, Up );
  camera_.Perspective();
  camera_.UpdateConstantBuffer();
  //camera_.Ortho2D();
  //camera_.view() = XMMatrixScaling(0.4f,0.4f,0.4f);// * XMMatrixTranslation(0.5,0,0);

  // Create vertex buffer
  SimpleVertex vertices[] =
  {
      { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.5f, 0.0f ) },
      { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.5f, 0.5f ) },
      { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.2f, 0.5f ) },

      { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
      { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

      { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
      { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
      { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
      { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

      { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
      { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

      { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
      { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

      { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
      { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
      { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
  };

  //D3D11_BUFFER_DESC bd;
  //ZeroMemory( &bd, sizeof(bd) );

  {
  
    g_vb.description.bind_flags = D3D11_BIND_VERTEX_BUFFER;
    g_vb.description.usage = D3D11_USAGE_DEFAULT;
    g_vb.description.byte_width = sizeof( SimpleVertex ) * 24;
    g_vb.description.cpu_access_flags = 0;
    engine_->gfx_context().CreateBuffer(g_vb,NULL);
    //uint32_t index,uint32_t type,
    //graphics::BufferSubresource subresource;
    engine_->gfx_context().device_context()->UpdateSubresource((ID3D11Resource*)g_vb.internal_pointer,0,NULL,vertices,sizeof(vertices),0);
  }

  WORD indices[] =
  {
      3,1,0,
      2,1,3,

      6,4,5,
      7,4,6,

      11,9,8,
      10,9,11,

      14,12,13,
      15,12,14,

      19,17,16,
      18,17,19,

      22,20,21,
      23,20,22
  };

  {

    g_ib.description.bind_flags = D3D11_BIND_INDEX_BUFFER;
    g_ib.description.usage = D3D11_USAGE_DEFAULT;
    g_ib.description.byte_width = sizeof( uint16_t ) * 36;
    g_ib.description.cpu_access_flags = 0;
    engine_->gfx_context().CreateBuffer(g_ib,NULL);
    //uint32_t index,uint32_t type,
    //graphics::BufferSubresource subresource;
    engine_->gfx_context().device_context()->UpdateSubresource((ID3D11Resource*)g_ib.internal_pointer,0,NULL,indices,sizeof(indices),0);
  }



    
  //bd.ByteWidth = sizeof(CBChangeOnResize);
  //hr = gfx_context_.device()->CreateBuffer( &bd, NULL, &g_pCBChangeOnResize );
  //if( FAILED( hr ) )
  //    return hr;
    
  g_pCBChangesEveryFrame.description.bind_flags = D3D11_BIND_CONSTANT_BUFFER;
  g_pCBChangesEveryFrame.description.usage = D3D11_USAGE_DEFAULT;
  g_pCBChangesEveryFrame.description.byte_width = sizeof(ConstantBuffer2Type);
  g_pCBChangesEveryFrame.description.cpu_access_flags = 0;
  hr = engine_->gfx_context().CreateBuffer(g_pCBChangesEveryFrame,NULL);
  if( FAILED( hr ) )
      return hr;

  // Load the Texture
  hr = D3DX11CreateShaderResourceViewFromFile( engine_->gfx_context().device(), "Content\\arial31_0.png", NULL, NULL, &g_pTextureRV, NULL );
  if( FAILED( hr ) )
      return hr;

    
  D3D11_BLEND_DESC BlendStateDescription;
  ZeroMemory(&BlendStateDescription,sizeof(BlendStateDescription));
  BlendStateDescription.AlphaToCoverageEnable = false;
  BlendStateDescription.RenderTarget[0].BlendEnable = true;

  BlendStateDescription.RenderTarget[0].SrcBlend                  = D3D11_BLEND_SRC_ALPHA;        //D3D11_BLEND_SRC_COLOR;
  BlendStateDescription.RenderTarget[0].DestBlend                 = D3D11_BLEND_INV_SRC_ALPHA;//D3D11_BLEND_DEST_COLOR;
  BlendStateDescription.RenderTarget[0].SrcBlendAlpha             = D3D11_BLEND_ONE;//D3D11_BLEND_SRC_ALPHA;
  BlendStateDescription.RenderTarget[0].DestBlendAlpha    = D3D11_BLEND_ONE;//D3D11_BLEND_DEST_ALPHA;
  BlendStateDescription.RenderTarget[0].BlendOp                   = D3D11_BLEND_OP_ADD;
  BlendStateDescription.RenderTarget[0].BlendOpAlpha              = D3D11_BLEND_OP_ADD;
  BlendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    
  engine_->gfx_context().device()->CreateBlendState(&BlendStateDescription,&blend_state);
  float blendFactor[] = {1,1, 1, 1};
      UINT sampleMask   = 0xffffffff;
  engine_->gfx_context().device_context()->OMSetBlendState(blend_state,blendFactor,sampleMask);
    

  // Initialize the world matrices
  g_World = XMMatrixIdentity();


  motion1.set_context(&engine_->animation());
  motion1.set_from(0);
  motion1.set_to(2);
  motion1.set_max_time(1000000);
  motion1.set_value_ptr(&move_z);
  engine_->animation().tween_list.push_back(&motion1);
  move_z=0;
  motion1.Play();
  return S_OK; 
}