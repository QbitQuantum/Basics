//-------------------------------------------------------------------------------------------------
U2Variable* U2FrameXmlParser::ParseVariable(U2Variable::Type dataType, TiXmlElement* elem)
{
	U2ASSERT(elem);
	const char* szVar = elem->Attribute("name");
	U2ASSERT(szVar);
	U2Variable::Handle varHandle = U2VariableMgr::Instance()->GetVariableHandleByName(szVar);
	U2Variable* pNewVar = U2_NEW U2Variable(dataType, varHandle);
	switch(dataType)
	{
	case U2Variable::Int:
		pNewVar->SetInt(GetIntAttr(elem, "value", 0));
		break;
	case U2Variable::Float:
		pNewVar->SetFloat(GetFloatAttr(elem, "value", 0.0f));
		break;
	case U2Variable::Vector4:
		{
			D3DXVECTOR4 v(VECTOR4_ZERO);
			pNewVar->SetVector4(GetVector4Attr(elem, "value", v));
		}
		break;
	case U2Variable::Object:
		{
#ifdef UNICODE 
			const wchar_t* szFilename = ToUnicode(elem->Attribute("value"));
#else 
			const char* szFilename = elem->Attribute("value");
#endif 
			U2ASSERT(szFilename);

			U2Dx9BaseTexture* pTexIter = U2Dx9BaseTexture::GetHead();

			U2Dx9BaseTexture* pNexTex = 0;

			while(pTexIter)
			{
				// Create시 SetName을 함..
				if(pTexIter->GetName() == szFilename)
				{
					pNexTex = pTexIter;
					break;
				}

				pTexIter = pTexIter->GetNext();
			}

			if(!pNexTex)
			{
				U2FilePath fPath;				
				TCHAR fullPath[256];
				fPath.ConvertToAbs(fullPath, 256 * sizeof(TCHAR) , szFilename, TEXTURE_PATH);	

				pNexTex = U2Dx9Texture::Create(fullPath, U2Dx9Renderer::GetRenderer());			
			}

			pNewVar->SetObj(pNexTex);			
		}
		break;
	default:
		U2ASSERT(false);
		FDebug("nRpXmlParser::ParseGlobalVariable(): invalid datatype for variable '%s'!",
			szVar);
		
		break;
	}
	return pNewVar;
}