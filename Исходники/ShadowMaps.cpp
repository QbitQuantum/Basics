//---------------------------------------------------------------------------
void ShadowMaps::UpdateLightCamera( ID3D11DeviceContext* dc, const DirLight* light, const AABB& renderedArea )
{
    float3 worldUp(0,1,0);
    float3 lightDir = normalize(light->dir);

    // compute ligtcam params.
    float dt = dot(-lightDir, worldUp);
    float3 center = renderedArea.GetCenter();
    float dim = length(renderedArea.Max() - renderedArea.Min());
    float radi = dim * 0.5f;

    float3 camPos = center - (radi * lightDir);
    float3 up;
    float3 right;

    if ((dt + Epsilon) >= 1)
    {
        up = float3(0, 0, -1);
        right = float3(1, 0, 0);

    }
    else
    {
        right = normalize(cross(lightDir, worldUp));
        up = normalize(cross(right, lightDir));
        right = cross(lightDir, worldUp);
        up = cross(right, lightDir);
    }


    // create view matrix from right, up and look, and position.
     float rp = -dot(right, camPos);
     float upp = -dot(up, camPos);
     float zp = dot(lightDir, camPos);
     Matrix view(
                right.x, up.x, -lightDir.x, 0.0f,
                right.y, up.y, -lightDir.y, 0.0f,
                right.z, up.z, -lightDir.z, 0.0f,
                rp, upp, zp, 1.0f);

    // compute the width, height, near, far by transforming the AABB into view space.
    AABB lbounds = renderedArea;
    lbounds.Transform(view);
    float3 vmin = lbounds.Min();
    float3 vmax = lbounds.Max();
    float width = vmax.x - vmin.x;
    float height = vmax.y - vmin.y;
    float nearz = 0.0f;
    float farz = dim;

    Matrix proj = Matrix::CreateOrthographic(width,height, nearz, farz);
    //Matrix proj = Matrix::CreateOrthographicOffCenter(vmin.x, vmax.x, vmin.y, vmax.y, nearz, farz);
    m_lightCamera.SetViewProj(view, proj);

    // update cb        
    m_cbShadow.Data.texelSize  = ( 1.0f / MapSize() );        

    // udpate constant buffer using lightcamera.
    // transform coords from NDC space to texture space.
    float4x4 ndcToTexSpace(  0.5f,  0.0f, 0.0f, 0.0f,
                             0.0f, -0.5f, 0.0f, 0.0f,
                             0.0f,  0.0f, 1.0f, 0.0f,
                             0.5f,  0.5f, 0.0f, 1.0f);
                                 
    float4x4 shadowViewProjection = (m_lightCamera.View() * m_lightCamera.Proj()) * ndcToTexSpace;
    Matrix::Transpose(shadowViewProjection, m_cbShadow.Data.xform);    
    m_cbShadow.Update(dc);
}