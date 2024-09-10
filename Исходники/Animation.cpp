void Animation::getFrameData(float frame, uint32_t boneIndex, Vec3& pos, Quaternion& rot, Vec3& scale, uint32_t& hint)
{
    FrameSet& set   = m_framesByBoneIndex[boneIndex];
    uint32_t index  = 0;
    
    for (uint32_t i = hint; i < set.count; i++)
    {
        Frame& fr = set.frames[i];
        
        if (fr.milliseconds >= frame)
        {
            index = i;
            break;
        }
        
        hint++;
    }
    
    if (set.count <= hint)
        return;
    
    Frame& a = set.frames[index];
    Frame& b = set.frames[index - 1];
    
    float f1 = frame - a.milliseconds;
    float f2 = b.milliseconds - frame + f1;
    
    // Position
    pos = ((b.pos - a.pos) / f2) * f1 + a.pos;
    
    // Scale
    scale = ((b.scale - a.scale) / f2) * f1 + a.scale;
    
    // Rotation
    rot.slerp(a.rot, b.rot, f1 / f2);
}