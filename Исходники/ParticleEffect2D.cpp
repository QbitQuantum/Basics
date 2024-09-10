bool ParticleEffect2D::BeginLoad(Deserializer& source)
{
    if (GetName().Empty())
        SetName(source.GetName());

    loadSpriteName_.Clear();

    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
        return false;

    XMLElement rootElem = xmlFile.GetRoot("particleEmitterConfig");
    if (!rootElem)
        return false;

    String texture = rootElem.GetChild("texture").GetAttribute("name");
    loadSpriteName_ = GetParentPath(GetName()) + texture;
    // If async loading, request the sprite beforehand
    if (GetAsyncLoadState() == ASYNC_LOADING)
        GetSubsystem<ResourceCache>()->BackgroundLoadResource<Sprite2D>(loadSpriteName_, true, this);

    sourcePositionVariance_ = ReadVector2(rootElem, "sourcePositionVariance");

    speed_ = ReadFloat(rootElem, "speed");
    speedVariance_ = ReadFloat(rootElem, "speedVariance");

    particleLifeSpan_ = Max(0.01f, ReadFloat(rootElem, "particleLifeSpan"));
    particleLifespanVariance_ = ReadFloat(rootElem, "particleLifespanVariance");

    angle_ = ReadFloat(rootElem, "angle");
    angleVariance_ = ReadFloat(rootElem, "angleVariance");

    gravity_ = ReadVector2(rootElem, "gravity");

    radialAcceleration_ = ReadFloat(rootElem, "radialAcceleration");
    tangentialAcceleration_ = ReadFloat(rootElem, "tangentialAcceleration");

    radialAccelVariance_ = ReadFloat(rootElem, "radialAccelVariance");
    tangentialAccelVariance_ = ReadFloat(rootElem, "tangentialAccelVariance");

    startColor_ = ReadColor(rootElem, "startColor");
    startColorVariance_ = ReadColor(rootElem, "startColorVariance");

    finishColor_ = ReadColor(rootElem, "finishColor");
    finishColorVariance_ = ReadColor(rootElem, "finishColorVariance");

    maxParticles_ = ReadInt(rootElem, "maxParticles");

    startParticleSize_ = ReadFloat(rootElem, "startParticleSize");
    startParticleSizeVariance_ = ReadFloat(rootElem, "startParticleSizeVariance");

    finishParticleSize_ = ReadFloat(rootElem, "finishParticleSize");
    // Typo in pex file
    finishParticleSizeVariance_ = ReadFloat(rootElem, "FinishParticleSizeVariance");

    duration_ = M_INFINITY;
    if (rootElem.HasChild("duration"))
    {
        float duration = ReadFloat(rootElem, "duration");
        if (duration > 0.0f)
            duration_ = duration;
    }


    emitterType_ = (EmitterType2D)ReadInt(rootElem, "emitterType");

    maxRadius_ = ReadFloat(rootElem, "maxRadius");
    maxRadiusVariance_ = ReadFloat(rootElem, "maxRadiusVariance");
    minRadius_ = ReadFloat(rootElem, "minRadius");
    minRadiusVariance_ = ReadFloat(rootElem, "minRadiusVariance");

    rotatePerSecond_ = ReadFloat(rootElem, "rotatePerSecond");
    rotatePerSecondVariance_ = ReadFloat(rootElem, "rotatePerSecondVariance");

    int blendFuncSource = ReadInt(rootElem, "blendFuncSource");
    int blendFuncDestination = ReadInt(rootElem, "blendFuncDestination");
    blendMode_ = BLEND_ALPHA;
    for (int i = 0; i < MAX_BLENDMODES; ++i)
    {
        if (blendFuncSource == srcBlendFuncs[i] && blendFuncDestination == destBlendFuncs[i])
        {
            blendMode_ = (BlendMode)i;
            break;
        }
    }

    rotationStart_ = ReadFloat(rootElem, "rotationStart");
    rotationStartVariance_ = ReadFloat(rootElem, "rotationStartVariance");

    rotationEnd_ = ReadFloat(rootElem, "rotationEnd");
    rotationEndVariance_ = ReadFloat(rootElem, "rotationEndVariance");

    // Note: not accurate
    SetMemoryUse(source.GetSize());
    return true;
}