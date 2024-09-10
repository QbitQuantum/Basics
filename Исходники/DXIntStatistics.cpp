BOOL TrianglesPerFrame_ProcessCall(DXMethodCallPtr call)
{
  D3DPRIMITIVETYPE primitiveType;
  UINT primitiveCount;
  
  switch (call->GetToken())
  {
  case DXMethodCallHelper::TOK_IDirect3DDevice9_DrawIndexedPrimitive:
    call->GetParam(0, (char*) &primitiveType);
    call->GetParam(5, (char*) &primitiveCount);
    g_TRIANGLESPERFRAME += TrianglesPerFrame_CalculateNumTriangles(primitiveType, primitiveCount);
    break;
  
  case DXMethodCallHelper::TOK_IDirect3DDevice9_DrawPrimitive:  
    call->GetParam(0, (char*) &primitiveType);
    call->GetParam(2, (char*) &primitiveCount);
    g_TRIANGLESPERFRAME += TrianglesPerFrame_CalculateNumTriangles(primitiveType, primitiveCount);
    break;
  
  case DXMethodCallHelper::TOK_IDirect3DDevice9_DrawIndexedPrimitiveUP:
    call->GetParam(0, (char*) &primitiveType);
    call->GetParam(3, (char*) &primitiveCount);
    g_TRIANGLESPERFRAME += TrianglesPerFrame_CalculateNumTriangles(primitiveType, primitiveCount);
    break;

  case DXMethodCallHelper::TOK_IDirect3DDevice9_DrawPrimitiveUP:
    call->GetParam(0, (char*) &primitiveType);
    call->GetParam(1, (char*) &primitiveCount);
    g_TRIANGLESPERFRAME += TrianglesPerFrame_CalculateNumTriangles(primitiveType, primitiveCount);
    break;
  }
  
  return TRUE;
}