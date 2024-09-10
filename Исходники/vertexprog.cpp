void VertexProcessor::parameter(vp::Parameter param, const Eigen::Vector4f& v)
{
    parameter(param, v.x(), v.y(), v.z(), v.w());
}