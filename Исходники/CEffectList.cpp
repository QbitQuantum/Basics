//--------------------------------------------------------------------------------------
//LoadShaderFromResource
//
//loads shader given a resource id
//--------------------------------------------------------------------------------------
HRESULT CEffect::LoadShaderFromResource(uint32 a_ResourceID, IDirect3DDevice9 *a_pDevice)
{
   HRESULT hr;
   ID3DXBuffer *errorBuffer;
   HRSRC       resourceInfo;
   HGLOBAL     resourceData;
   char8       *shaderText;

   m_pDevice = a_pDevice;

   //delete old effect if multiple calls to load shader are made
   SAFE_RELEASE(m_pEffect);

   // Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the 
   // shader debugger. Debugging vertex shaders requires either REF or software vertex 
   // processing, and debugging pixel shaders requires REF.  The 
   // D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the 
   // shader debugger.  It enables source level debugging, prevents instruction 
   // reordering, prevents dead code elimination, and forces the compiler to compile 
   // against the next higher available software target, which ensures that the 
   // unoptimized shaders do not exceed the shader model limitations.  Setting these 
   // flags will cause slower rendering since the shaders will be unoptimized and 
   // forced into software.  See the DirectX documentation for more information about 
   // using the shader debugger.
   DWORD dwShaderFlags = 0;
   #ifdef DEBUG_VS
      dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
   #endif
   #ifdef DEBUG_PS
      dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
   #endif

   //load shadertext from resource
   resourceInfo = FindResource(NULL, MAKEINTRESOURCE(a_ResourceID), L"EFFECTFILE"); 

   if(resourceInfo == NULL)
   {
      _snwprintf_s(m_ErrorMsg, MAX_ERROR_MSG, MAX_ERROR_MSG, L"Resource %d of type ''EFFECTFILE'' not found.", a_ResourceID );   
   }

   resourceData = LoadResource(NULL, resourceInfo ); 

   shaderText = (char8 *)LockResource( resourceData);

   //Create effect from text loaded from resource
   // load and compile .fx file
   // If this fails, there should be debug output as to 
   // why the .fx file failed to compile
   hr = D3DXCreateEffect(
      m_pDevice,           //LPDIRECT3DDEVICE9 pDevice,
      shaderText,          //LPCVOID pSrcData,
      (uint32)SizeofResource(NULL, resourceInfo),  //UINT SrcDataLen,
      NULL,                //const D3DXMACRO *pDefines,
      NULL,                //LPD3DXINCLUDE pInclude,
      0,                   //DWORD Flags,
      NULL,                //LPD3DXEFFECTPOOL pPool,
      &m_pEffect,          //LPD3DXEFFECT *ppEffect,
      &errorBuffer         //LPD3DXBUFFER *ppCompilationErrors
      );
      
   UnlockResource( resourceData );
   FreeResource( resourceData );

   //return failure and record error message if failure
   if(FAILED(hr))
   {  //error is in 8-bit character format, so for swprintf to use the string, %S (capital S) is used.
      if(errorBuffer != NULL)
      {
         _snwprintf_s(m_ErrorMsg, MAX_ERROR_MSG, MAX_ERROR_MSG, L"Shader Compile Error: %S.", errorBuffer->GetBufferPointer() );
      }
      else
      {
         _snwprintf_s(m_ErrorMsg, MAX_ERROR_MSG, MAX_ERROR_MSG, L"Shader Compile Error: no output from D3DXCreateEffectFromResource." );      
      }

      SAFE_RELEASE(errorBuffer);
      return hr;
   }

   _snwprintf_s(m_ErrorMsg, MAX_ERROR_MSG, MAX_ERROR_MSG, L"FX file in Resource %d Compiled Successfully.", a_ResourceID);

   return S_OK;
}