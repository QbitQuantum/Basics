static inline void writeSE3(YAMLWriter& writer, const SE3& value)
{
    writer.startFlowStyleListing();

    const Vector3& p = value.translation();
    writer.putScalar(p.x());
    writer.putScalar(p.y());
    writer.putScalar(p.z());

    const Quat& q = value.rotation();
    writer.putScalar(q.w());
    writer.putScalar(q.x());
    writer.putScalar(q.y());
    writer.putScalar(q.z());

    writer.endListing();
}