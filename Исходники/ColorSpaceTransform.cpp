    void BuildColorSpaceOps(OpRcPtrVec & ops,
    const Config& config,
    const ConstContextRcPtr & context,
    const ColorSpaceTransform & colorSpaceTransform,
    TransformDirection dir)
    {
        TransformDirection combinedDir = CombineTransformDirections(dir,
        colorSpaceTransform.getDirection());

        ConstColorSpaceRcPtr src, dst;

        if(combinedDir == TRANSFORM_DIR_FORWARD)
        {
            src = config.getColorSpace( colorSpaceTransform.getSrc() );
            dst = config.getColorSpace( colorSpaceTransform.getDst() );
        }
        else if(combinedDir == TRANSFORM_DIR_INVERSE)
        {
            dst = config.getColorSpace( colorSpaceTransform.getSrc() );
            src = config.getColorSpace( colorSpaceTransform.getDst() );
        }

        BuildColorSpaceOps(ops, config, context, src, dst);
    }