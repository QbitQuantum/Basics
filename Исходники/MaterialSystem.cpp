#include "MaterialTextureOps.h"
#include "MaterialExperimental.h"
#include "MaterialPostprocess.h"

#include "MaterialSystem.h"

static const unsigned int scMaterialSystemMemorySize = 512 * 1024;
static const unsigned int scPhongMaterialsSegmentSize = 512;
static const unsigned int scPlainColorMaterialsSegmentSize = 3;
static const unsigned int scTextured2DMaterialsSegmentSize = 2;
static const unsigned int scMipGeneratorMaterialsSegmentSize = 1;
static const unsigned int scLinearTo2DMaterialsSegmentSize = 3;
static const unsigned int scExperimentalMaterialsSegmentSize = 100;
static const unsigned int scPostprocessMaterialsSegmentSize = 1;

static XMVECTOR sPink = XMVectorSet(1.0f, 0.0f, 1.0f, 1.0f);
static XMVECTOR sBlack = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);


//----------------------------------------------------------------------------------
void CMaterial::SetSRV(ID3D11DeviceContext* pDeviceContext, const CShaderResourceInfo& ResourceInfo, ID3D11ShaderResourceView* pSRV) const
{
	ID3D11ShaderResourceView* ppSRV[1] = { pSRV };
	if (ResourceInfo.m_ResourceInfo[eVertexShader].m_NumViews > 0)
	{
		pDeviceContext->VSSetShaderResources(ResourceInfo.m_ResourceInfo[eVertexShader].m_StartSlot, ResourceInfo.m_ResourceInfo[eVertexShader].m_NumViews, ppSRV);
	}

	if (ResourceInfo.m_ResourceInfo[ePixelShader].m_NumViews > 0)
	{
		pDeviceContext->PSSetShaderResources(ResourceInfo.m_ResourceInfo[ePixelShader].m_StartSlot, ResourceInfo.m_ResourceInfo[ePixelShader].m_NumViews, ppSRV);