void RenderLine2D(Shader *sh, Primitive prim, const float3 &v1, const float3 &v2, float thickness)
{
    auto v = (v2 - v1) / 2;
    auto len = length(v);
    auto vnorm = v / len;
    auto trans = translation(v1 + v) * 
                 rotationZ(vnorm.xy()) *
                 float4x4(float4(len, thickness / 2, 1, 1));
    RenderQuad(sh, prim, true, trans);
}