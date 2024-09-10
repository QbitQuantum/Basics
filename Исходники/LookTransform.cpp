 void BuildLookOps(OpRcPtrVec & ops,
                   const Config& config,
                   const ConstContextRcPtr & context,
                   const LookTransform & lookTransform,
                   TransformDirection dir)
 {
     ConstColorSpaceRcPtr src, dst;
     src = config.getColorSpace( lookTransform.getSrc() );
     dst = config.getColorSpace( lookTransform.getDst() );
     
     if(!src)
     {
         std::ostringstream os;
         os << "BuildLookOps error.";
         os << "The specified lookTransform specifies a src colorspace, '";
         os <<  lookTransform.getSrc() << "', which is not defined.";
         throw Exception(os.str().c_str());
     }
     
     if(!dst)
     {
         std::ostringstream os;
         os << "BuildLookOps error.";
         os << "The specified lookTransform specifies a dst colorspace, '";
         os <<  lookTransform.getDst() << "', which is not defined.";
         throw Exception(os.str().c_str());
     }
     
     LookParseResult looks;
     looks.parse(lookTransform.getLooks());
     
     // We must handle the inverse src/dst colorspace transformation explicitly.
     if(dir == TRANSFORM_DIR_INVERSE)
     {
         std::swap(src, dst);
         looks.reverse();
     }
     else if(dir == TRANSFORM_DIR_UNKNOWN)
     {
         std::ostringstream os;
         os << "BuildLookOps error. A valid transform direction must be specified.";
         throw Exception(os.str().c_str());
     }
     
     ConstColorSpaceRcPtr currentColorSpace = src;
     BuildLookOps(ops,
                  currentColorSpace,
                  false,
                  config,
                  context,
                  looks);
     
     BuildColorSpaceOps(ops, config, context,
                        currentColorSpace,
                        dst);
 }