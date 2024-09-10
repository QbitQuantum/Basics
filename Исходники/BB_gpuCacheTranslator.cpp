                virtual void ExportProcedural( AtNode *node )
                {
                        // do basic node export
                        ExportMatrix( node, 0 );

                        // AiNodeSetPtr( node, "shader", arnoldShader(node) );


                        AiNodeSetInt( node, "visibility", ComputeVisibility() );

                        MPlug plug = FindMayaObjectPlug( "receiveShadows" );
                        if( !plug.isNull() )
                        {
                                AiNodeSetBool( node, "receive_shadows", plug.asBool() );
                        }

                        plug = FindMayaObjectPlug( "aiSelfShadows" );
                        if( !plug.isNull() )
                        {
                                AiNodeSetBool( node, "self_shadows", plug.asBool() );
                        }

                        plug = FindMayaObjectPlug( "aiOpaque" );
                        if( !plug.isNull() )
                        {
                                AiNodeSetBool( node, "opaque", plug.asBool() );
                        }

                        // now set the procedural-specific parameters

                        AiNodeSetBool( node, "load_at_init", true ); // just for now so that it can load the shaders at the right time

                        MFnDagNode fnDagNode( m_dagPath );
                        MBoundingBox bound = fnDagNode.boundingBox();

                        AiNodeSetPnt( node, "min", bound.min().x-m_dispPadding, bound.min().y-m_dispPadding, bound.min().z-m_dispPadding );
                        AiNodeSetPnt( node, "max", bound.max().x+m_dispPadding, bound.max().y, bound.max().z+m_dispPadding );

                        const char *dsoPath = getenv( "ALEMBIC_ARNOLD_PROCEDURAL_PATH" );
                        AiNodeSetStr( node, "dso",  dsoPath ? dsoPath : "bb_AlembicArnoldProcedural.so" );

                        // Set the parameters for the procedural

                        //abcFile path
                        MString abcFile = fnDagNode.findPlug("cacheFileName").asString().expandEnvironmentVariablesAndTilde();

                        //object path
                        MString objectPath = fnDagNode.findPlug("cacheGeomPath").asString();

                        //object pattern
                        MString objectPattern = "*";

                        plug = FindMayaObjectPlug( "objectPattern" );
                        if (!plug.isNull() )
                        {
                              if (plug.asString() != "")
                              {
                                objectPattern = plug.asString();
                              }
                        }

                        //object pattern
                        MString excludePattern = "";

                        plug = FindMayaObjectPlug( "excludePattern" );
                        if (!plug.isNull() )
                        {
                              if (plug.asString() != "")
                              {
                                excludePattern = plug.asString();
                              }
                        }

                        float shutterOpen = 0.0;
                        plug = FindMayaObjectPlug( "shutterOpen" );
                        if (!plug.isNull() )
                        {
                                shutterOpen = plug.asFloat();
                        }

                        float shutterClose = 0.0;
                        plug = FindMayaObjectPlug( "shutterClose" );
                        if (!plug.isNull() )
                        {
                                shutterClose = plug.asFloat();
                        }

                        float timeOffset = 0.0;
                        plug = FindMayaObjectPlug( "timeOffset" );
                        if (!plug.isNull() )
                        {
                                timeOffset = plug.asFloat();
                        }

                        int subDIterations = 0;
                        plug = FindMayaObjectPlug( "ai_subDIterations" );
                        if (!plug.isNull() )
                        {
                                subDIterations = plug.asInt();
                        }

                        MString nameprefix = "";
                        plug = FindMayaObjectPlug( "namePrefix" );
                        if (!plug.isNull() )
                        {
                                nameprefix = plug.asString();
                        }

                        // bool exportFaceIds = fnDagNode.findPlug("exportFaceIds").asBool();

                        bool makeInstance = true; // always on for now
                        plug = FindMayaObjectPlug( "makeInstance" );
                        if (!plug.isNull() )
                        {
                                makeInstance = plug.asBool();
                        }
                        
                        bool flipv = false; 
                        plug = FindMayaObjectPlug( "flipv" );
                        if (!plug.isNull() )
                        {
                                flipv = plug.asBool();
                        }

                        bool invertNormals = false; 
                        plug = FindMayaObjectPlug( "invertNormals" );
                        if (!plug.isNull() )
                        {
                                invertNormals = plug.asBool();
                        }
                        
                        short i_subDUVSmoothing = 1;
                        plug = FindMayaObjectPlug( "ai_subDUVSmoothing" );
                        if (!plug.isNull() )
                        {
                                i_subDUVSmoothing = plug.asShort();
                        }

                        MString  subDUVSmoothing;

                        switch (i_subDUVSmoothing)
                        {
                          case 0:
                            subDUVSmoothing = "pin_corners";
                            break;
                          case 1:
                            subDUVSmoothing = "pin_borders";
                            break;
                          case 2:
                            subDUVSmoothing = "linear";
                            break;
                          case 3:
                            subDUVSmoothing = "smooth";
                            break;
                          default :
                            subDUVSmoothing = "pin_corners";
                            break;
                        }

                        MTime curTime = MAnimControl::currentTime();
                        // fnDagNode.findPlug("time").getValue( frame );

                        // MTime frameOffset;
                        // fnDagNode.findPlug("timeOffset").getValue( frameOffset );

                        float time = curTime.as(MTime::kFilm)+timeOffset;

                        MString argsString;
                        if (objectPath != "|"){
                                argsString += "-objectpath ";
                                // convert "|" to "/"

                                argsString += MString(replace_all(objectPath,"|","/").c_str());
                        }
                        if (objectPattern != "*"){
                                argsString += "-pattern ";
                                argsString += objectPattern;
                        }
                        if (excludePattern != ""){
                                argsString += "-excludepattern ";
                                argsString += excludePattern;
                        }
                        if (shutterOpen != 0.0){
                                argsString += " -shutteropen ";
                                argsString += shutterOpen;
                        }
                        if (shutterClose != 0.0){
                                argsString += " -shutterclose ";
                                argsString += shutterClose;
                        }
                        if (subDIterations != 0){
                                argsString += " -subditerations ";
                                argsString += subDIterations;
                                argsString += " -subduvsmoothing ";
                                argsString += subDUVSmoothing;
                        }
                        if (makeInstance){
                                argsString += " -makeinstance ";
                        }
                        if (nameprefix != ""){
                                argsString += " -nameprefix ";
                                argsString += nameprefix;
                        }
                        if (flipv){
                                argsString += " -flipv ";
                        }
                        if (invertNormals){
                                argsString += " -invertNormals ";
                        }
                        argsString += " -filename ";
                        argsString += abcFile;
                        argsString += " -frame ";
                        argsString += time;

                        if (m_displaced){

                            argsString += " -disp_map ";
                            argsString += AiNodeGetName(m_dispNode);

                        }

                        AiNodeSetStr(node, "data", argsString.asChar());

                        ExportUserAttrs(node);

                        // Export light linking per instance
                        ExportLightLinking(node);

                }