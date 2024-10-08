void CScriptedShapeTranslator::RunScripts(AtNode *atNode, unsigned int step, bool update)
{
   std::map<std::string, CScriptedTranslator>::iterator translatorIt;
   MFnDependencyNode fnNode(GetMayaObject());
   
   translatorIt = gTranslators.find(fnNode.typeName().asChar());
   if (translatorIt == gTranslators.end())
   {
      AiMsgError("[mtoa.scriptedTranslators] No command to export node \"%s\" of type %s.", fnNode.name().asChar(), fnNode.typeName().asChar());
      return;
   }
   
   MString exportCmd = translatorIt->second.exportCmd;
   MString cleanupCmd = translatorIt->second.cleanupCmd;
   
   MFnDagNode node(m_dagPath.node());
   
   bool isMasterDag = false;
   bool transformBlur = IsMotionBlurEnabled(MTOA_MBLUR_OBJECT) && IsLocalMotionBlurEnabled();
   bool deformBlur = IsMotionBlurEnabled(MTOA_MBLUR_DEFORM) && IsLocalMotionBlurEnabled();
   
   char buffer[64];
   
   MString command = exportCmd;
   command += "(";
   
   sprintf(buffer, "%f", GetExportFrame());
   command += buffer;
   command += ", ";
   
   sprintf(buffer, "%d", step);
   command += buffer;
   command += ", ";
   
   // current sample frame
   sprintf(buffer, "%f", GetSampleFrame(m_session, step));
   command += buffer;
   command += ", ";
   
   // List of arnold attributes the custom shape export command has overriden
   MStringArray attrs;
   
   if (!m_masterNode)
   {
      command += "(\"" + m_dagPath.partialPathName() + "\", \"";
      command += AiNodeGetName(atNode);
      command += "\"), None)";
      isMasterDag = true;
   }
   else
   {
      command += "(\"" + m_dagPath.partialPathName() + "\", \"";
      command += AiNodeGetName(atNode);
      command += "\"), (\"" + GetMasterInstance().partialPathName() + "\", \"";
      command += AiNodeGetName(m_masterNode);
      command += "\"))";
   }
   
   MStatus status = MGlobal::executePythonCommand(command, attrs);
   if (!status)
   {
      AiMsgError("[mtoa.scriptedTranslators] Failed to export node \"%s\".", node.name().asChar());
      return;
   }
   
   // Build set of attributes already processed
   std::set<std::string> attrsSet;
   for (unsigned int i=0; i<attrs.length(); ++i)
   {
      attrsSet.insert(attrs[i].asChar());
   }
   std::set<std::string>::iterator attrsEnd = attrsSet.end();
   
   // Should be getting displacement shader from master instance only
   //   as arnold do not support displacement shader overrides for ginstance
   MFnDependencyNode masterShadingEngine;
   MFnDependencyNode shadingEngine;
   float dispPadding = -AI_BIG;
   float dispHeight = 1.0f;
   float dispZeroValue = 0.0f;
   bool dispAutobump = false;
   bool outputDispPadding = false;
   bool outputDispHeight = false;
   bool outputDispZeroValue = false;
   bool outputDispAutobump = false;
   
   const AtNodeEntry *anodeEntry = AiNodeGetNodeEntry(atNode);
   
   GetShapeInstanceShader(m_dagPath, shadingEngine);
   if (!IsMasterInstance())
   {
      GetShapeInstanceShader(GetMasterInstance(), masterShadingEngine);
   }
   else
   {
      masterShadingEngine.setObject(shadingEngine.object());
   }
   
   AtMatrix matrix;
   MMatrix mmatrix = m_dagPath.inclusiveMatrix();
   ConvertMatrix(matrix, mmatrix);
   
   // Set transformation matrix
   if (attrsSet.find("matrix") == attrsEnd)
   {
      if (HasParameter(anodeEntry, "matrix"))
      {
         if (transformBlur)
         {
            if (step == 0)
            {
               AtArray* matrices = AiArrayAllocate(1, GetNumMotionSteps(), AI_TYPE_MATRIX);
               AiArraySetMtx(matrices, step, matrix);
               AiNodeSetArray(atNode, "matrix", matrices);
            }
            else
            {
               AtArray* matrices = AiNodeGetArray(atNode, "matrix");
               AiArraySetMtx(matrices, step, matrix);
            }
         }
         else
         {
            AiNodeSetMatrix(atNode, "matrix", matrix);
         }
      }
   }
   
   // Set bounding box
   if (attrsSet.find("min") == attrsEnd && attrsSet.find("max") == attrsEnd)
   {
      // Now check if min and max parameters are valid parameter names on arnold node
      if (HasParameter(anodeEntry, "min") != 0 && HasParameter(anodeEntry, "max") != 0)
      {
         if (step == 0)
         {
            MBoundingBox bbox = node.boundingBox();
            
            MPoint bmin = bbox.min();
            MPoint bmax = bbox.max();
            
            AiNodeSetPnt(atNode, "min", static_cast<float>(bmin.x), static_cast<float>(bmin.y), static_cast<float>(bmin.z));
            AiNodeSetPnt(atNode, "max", static_cast<float>(bmax.x), static_cast<float>(bmax.y), static_cast<float>(bmax.z));
         }
         else
         {
            if (transformBlur || deformBlur)
            {
               AtPoint cmin = AiNodeGetPnt(atNode, "min");
               AtPoint cmax = AiNodeGetPnt(atNode, "max");
               
               MBoundingBox bbox = node.boundingBox();
               
               MPoint bmin = bbox.min();
               MPoint bmax = bbox.max();
               
               if (bmin.x < cmin.x)
                  cmin.x = static_cast<float>(bmin.x);
               if (bmin.y < cmin.y)
                  cmin.y = static_cast<float>(bmin.y);
               if (bmin.z < cmin.z)
                  cmin.z = static_cast<float>(bmin.z);
               if (bmax.x > cmax.x)
                  cmax.x = static_cast<float>(bmax.x);
               if (bmax.y > cmax.y)
                  cmax.y = static_cast<float>(bmax.y);
               if (bmax.z > cmax.z)
                  cmax.z = static_cast<float>(bmax.z);
               
               AiNodeSetPnt(atNode, "min", cmin.x, cmin.y, cmin.z);
               AiNodeSetPnt(atNode, "max", cmax.x, cmax.y, cmax.z);
            }
         }
      }
   }
   
   if (step == 0)
   {
      // Set common attributes
      MPlug plug;
      
      if (AiNodeIs(atNode, "procedural"))
      {
         // Note: it is up to the procedural to properly forward (or not) those parameters to the node
         //       it creates
         
         if (attrsSet.find("subdiv_type") == attrsEnd)
         {
            plug = FindMayaPlug("subdiv_type");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSubdivType");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_type", atNode, "constant INT"))
            {
               AiNodeSetInt(atNode, "subdiv_type", plug.asInt());
            }
         }
         
         if (attrsSet.find("subdiv_iterations") == attrsEnd)
         {
            plug = FindMayaPlug("subdiv_iterations");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSubdivIterations");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_iterations", atNode, "constant BYTE"))
            {
               AiNodeSetByte(atNode, "subdiv_iterations", plug.asInt());
            }
         }
         
         if (attrsSet.find("subdiv_adaptive_metric") == attrsEnd)
         {
            plug = FindMayaPlug("subdiv_adaptive_metric");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSubdivAdaptiveMetric");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_adaptive_metric", atNode, "constant INT"))
            {
               AiNodeSetInt(atNode, "subdiv_adaptive_metric", plug.asInt());
            }
         }
         
         if (attrsSet.find("subdiv_pixel_error") == attrsEnd)
         {
            plug = FindMayaPlug("subdiv_pixel_error");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSubdivPixelError");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_pixel_error", atNode, "constant FLOAT"))
            {
               AiNodeSetFlt(atNode, "subdiv_pixel_error", plug.asFloat());
            }
         }
         
         if (attrsSet.find("subdiv_dicing_camera") == attrsEnd)
         {
            plug = FindMayaPlug("subdiv_dicing_camera");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSubdivDicingCamera");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_dicing_camera", atNode, "constant NODE"))
            {
               AtNode *cameraNode = NULL;
               
               MPlugArray plugs;
               plug.connectedTo(plugs, true, false);
               
               if (plugs.length() == 1)
               {
                  MFnDagNode camDag(plugs[0].node());
                  MDagPath camPath;
                  
                  if (camDag.getPath(camPath) == MS::kSuccess)
                  {
                     cameraNode = ExportDagPath(camPath);
                  }
               }
               
               AiNodeSetPtr(atNode, "subdiv_dicing_camera", cameraNode);
            }
         }
         
         if (attrsSet.find("subdiv_uv_smoothing") == attrsEnd)
         {
            plug = FindMayaPlug("subdiv_uv_smoothing");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSubdivUvSmoothing");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_uv_smoothing", atNode, "constant INT"))
            {
               AiNodeSetInt(atNode, "subdiv_uv_smoothing", plug.asInt());
            }
         }
         
         if (attrsSet.find("subdiv_smooth_derivs") == attrsEnd)
         {
            plug = FindMayaPlug("aiSubdivSmoothDerivs");
            if (!plug.isNull() && HasParameter(anodeEntry, "subdiv_smooth_derivs", atNode, "constant BOOL"))
            {
               AiNodeSetBool(atNode, "subdiv_smooth_derivs", plug.asBool());
            }
         }
         
         if (attrsSet.find("smoothing") == attrsEnd)
         {
            // Use maya shape built-in attribute
            plug = FindMayaPlug("smoothShading");
            if (!plug.isNull() && HasParameter(anodeEntry, "smoothing", atNode, "constant BOOL"))
            {
               AiNodeSetBool(atNode, "smoothing", plug.asBool());
            }
         }
         
         if (attrsSet.find("disp_height") == attrsEnd)
         {
            plug = FindMayaPlug("aiDispHeight");
            if (!plug.isNull())
            {
               outputDispHeight = true;
               dispHeight = plug.asFloat();
            }
         }
         
         if (attrsSet.find("disp_zero_value") == attrsEnd)
         {
            plug = FindMayaPlug("aiDispZeroValue");
            if (!plug.isNull())
            {
               outputDispZeroValue = true;
               dispZeroValue = plug.asFloat();
            }
         }
         
         if (attrsSet.find("disp_autobump") == attrsEnd)
         {
            plug = FindMayaPlug("aiDispAutobump");
            if (!plug.isNull())
            {
               outputDispAutobump = true;
               dispAutobump = plug.asBool();
            }
         }
         
         if (attrsSet.find("disp_padding") == attrsEnd)
         {
            plug = FindMayaPlug("aiDispPadding");
            if (!plug.isNull())
            {
               outputDispPadding = true;
               dispPadding = MAX(dispPadding, plug.asFloat());
            }
         }
         
         // Set diplacement shader
         if (attrsSet.find("disp_map") == attrsEnd)
         {
            if (masterShadingEngine.object() != MObject::kNullObj)
            {
               MPlugArray shaderConns;
               
               MPlug shaderPlug = masterShadingEngine.findPlug("displacementShader");
               
               shaderPlug.connectedTo(shaderConns, true, false);
               
               if (shaderConns.length() > 0)
               {
                  MFnDependencyNode dispNode(shaderConns[0].node());
                  
                  plug = dispNode.findPlug("aiDisplacementPadding");
                  if (!plug.isNull())
                  {
                     outputDispPadding = true;
                     dispPadding = MAX(dispPadding, plug.asFloat());
                  }
                  
                  plug = dispNode.findPlug("aiDisplacementAutoBump");
                  if (!plug.isNull())
                  {
                     outputDispAutobump = true;
                     dispAutobump = dispAutobump || plug.asBool();
                  }
                  
                  if (HasParameter(anodeEntry, "disp_map", atNode, "constant ARRAY NODE"))
                  {
                     AtNode *dispImage = ExportNode(shaderConns[0]);
                     AiNodeSetArray(atNode, "disp_map", AiArrayConvert(1, 1, AI_TYPE_NODE, &dispImage));
                  }
               }
            }
         }
         
         if (outputDispHeight && HasParameter(anodeEntry, "disp_height", atNode, "constant FLOAT"))
         {
            AiNodeSetFlt(atNode, "disp_height", dispHeight);
         }
         if (outputDispZeroValue && HasParameter(anodeEntry, "disp_zero_value", atNode, "constant FLOAT"))
         {
            AiNodeSetFlt(atNode, "disp_zero_value", dispZeroValue);
         }
         if (outputDispPadding && HasParameter(anodeEntry, "disp_padding", atNode, "constant FLOAT"))
         {
            AiNodeSetFlt(atNode, "disp_padding", dispPadding);
         }
         if (outputDispAutobump && HasParameter(anodeEntry, "disp_autobump", atNode, "constant BOOL"))
         {
            AiNodeSetBool(atNode, "disp_autobump", dispAutobump);
         }
         
         // Old point based SSS parameter
         if (attrsSet.find("sss_sample_distribution") == attrsEnd)
         {
            plug = FindMayaPlug("sss_sample_distribution");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSssSampleDistribution");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "sss_sample_distribution", atNode, "constant INT"))
            {
               AiNodeSetInt(atNode, "sss_sample_distribution", plug.asInt());
            }
         }
         
         // Old point based SSS parameter
         if (attrsSet.find("sss_sample_spacing") == attrsEnd)
         {
            plug = FindMayaPlug("sss_sample_spacing");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiSssSampleSpacing");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "sss_sample_spacing", atNode, "constant FLOAT"))
            {
               AiNodeSetFlt(atNode, "sss_sample_spacing", plug.asFloat());
            }
         }
         
         if (attrsSet.find("min_pixel_width") == attrsEnd)
         {
            plug = FindMayaPlug("aiMinPixelWidth");
            if (!plug.isNull() && HasParameter(anodeEntry, "min_pixel_width", atNode, "constant FLOAT"))
            {
               AiNodeSetFlt(atNode, "min_pixel_width", plug.asFloat());
            }
         }
         
         if (attrsSet.find("mode") == attrsEnd)
         {
            plug = FindMayaPlug("aiMode");
            if (!plug.isNull() && HasParameter(anodeEntry, "mode", atNode, "constant INT"))
            {
               AiNodeSetInt(atNode, "mode", plug.asShort());
            }
         }
         
         if (attrsSet.find("basis") == attrsEnd)
         {
            plug = FindMayaPlug("aiBasis");
            if (!plug.isNull() && HasParameter(anodeEntry, "basis", atNode, "constant INT"))
            {
               AiNodeSetInt(atNode, "basis", plug.asShort());
            }
         }
      }
      
      if (AiNodeIs(atNode, "ginstance"))
      {
         if (attrsSet.find("node") == attrsEnd)
         {
            AiNodeSetPtr(atNode, "node", m_masterNode);
         }
         
         if (attrsSet.find("inherit_xform") == attrsEnd)
         {
            AiNodeSetBool(atNode, "inherit_xform", false);
         }
      }
      else
      {
         // box or procedural
         if (attrsSet.find("step_size") == attrsEnd)
         {
            plug = FindMayaPlug("step_size");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiStepSize");
            }
            if (!plug.isNull() && HasParameter(anodeEntry, "step_size", atNode, "constant FLOAT"))
            {
               AiNodeSetFlt(atNode, "step_size", plug.asFloat());
            }
         }
      }
      
      if (attrsSet.find("sidedness") == attrsEnd)
      {
         // Use maya shape built-in attribute
         plug = FindMayaPlug("doubleSided");
         if (!plug.isNull() && HasParameter(anodeEntry, "sidedness", atNode, "constant BYTE"))
         {
            AiNodeSetByte(atNode, "sidedness", plug.asBool() ? AI_RAY_ALL : 0);
            
            // Only set invert_normals if doubleSided attribute could be found
            if (!plug.asBool() && attrsSet.find("invert_normals") == attrsEnd)
            {
               // Use maya shape built-in attribute
               plug = FindMayaPlug("opposite");
               if (!plug.isNull() && HasParameter(anodeEntry, "invert_normals", atNode, "constant BOOL"))
               {
                  AiNodeSetBool(atNode, "invert_normals", plug.asBool());
               }
            }
         }
      }
      
      if (attrsSet.find("receive_shadows") == attrsEnd)
      {
         // Use maya shape built-in attribute
         plug = FindMayaPlug("receiveShadows");
         if (!plug.isNull() && HasParameter(anodeEntry, "receive_shadows", atNode, "constant BOOL"))
         {
            AiNodeSetBool(atNode, "receive_shadows", plug.asBool());
         }
      }
      
      if (attrsSet.find("self_shadows") == attrsEnd)
      {
         plug = FindMayaPlug("self_shadows");
         if (plug.isNull())
         {
            plug = FindMayaPlug("aiSelfShadows");
         }
         if (!plug.isNull() && HasParameter(anodeEntry, "self_shadows", atNode, "constant BOOL"))
         {
            AiNodeSetBool(atNode, "self_shadows", plug.asBool());
         }
      }
      
      if (attrsSet.find("opaque") == attrsEnd)
      {
         plug = FindMayaPlug("opaque");
         if (plug.isNull())
         {
            plug = FindMayaPlug("aiOpaque");
         }
         if (!plug.isNull() && HasParameter(anodeEntry, "opaque", atNode, "constant BOOL"))
         {
            AiNodeSetBool(atNode, "opaque", plug.asBool());
         }
      }
      
      if (attrsSet.find("visibility") == attrsEnd)
      {
         if (HasParameter(anodeEntry, "visibility", atNode, "constant BYTE"))
         {
            int visibility = AI_RAY_ALL;
            
            // Use maya shape built-in attribute
            plug = FindMayaPlug("castsShadows");
            if (!plug.isNull() && !plug.asBool())
            {
               visibility &= ~AI_RAY_SHADOW;
            }
            
            // Use maya shape built-in attribute
            plug = FindMayaPlug("primaryVisibility");
            if (!plug.isNull() && !plug.asBool())
            {
               visibility &= ~AI_RAY_CAMERA;
            }
            
            // Use maya shape built-in attribute
            plug = FindMayaPlug("visibleInReflections");
            if (!plug.isNull() && !plug.asBool())
            {
               visibility &= ~AI_RAY_REFLECTED;
            }
            
            // Use maya shape built-in attribute
            plug = FindMayaPlug("visibleInRefractions");
            if (!plug.isNull() && !plug.asBool())
            {
               visibility &= ~AI_RAY_REFRACTED;
            }
            
            plug = FindMayaPlug("diffuse_visibility");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiVisibleInDiffuse");
            }
            if (!plug.isNull() && !plug.asBool())
            {
               visibility &= ~AI_RAY_DIFFUSE;
            }
            
            plug = FindMayaPlug("glossy_visibility");
            if (plug.isNull())
            {
               plug = FindMayaPlug("aiVisibleInGlossy");
            }
            if (!plug.isNull() && !plug.asBool())
            {
               visibility &= ~AI_RAY_GLOSSY;
            }
            
            AiNodeSetByte(atNode, "visibility", visibility & 0xFF);
         }
      }
      
      if (attrsSet.find("sss_setname") == attrsEnd)
      {
         plug = FindMayaPlug("aiSssSetname");
         if (!plug.isNull() && plug.asString().length() > 0)
         {
            if (HasParameter(anodeEntry, "sss_setname", atNode, "constant STRING"))
            {
               AiNodeSetStr(atNode, "sss_setname", plug.asString().asChar());
            }
         }
      }
      
      // Set surface shader
      if (HasParameter(anodeEntry, "shader", atNode, "constant NODE"))
      {
         if (attrsSet.find("shader") == attrsEnd)
         {
            if (shadingEngine.object() != MObject::kNullObj)
            {
               AtNode *shader = ExportNode(shadingEngine.findPlug("message"));
               if (shader != NULL)
               {
                  const AtNodeEntry *entry = AiNodeGetNodeEntry(shader);
                  
                  if (AiNodeEntryGetType(entry) != AI_NODE_SHADER)
                  {
                     MGlobal::displayWarning("[mtoaScriptedTranslators] Node generated from \"" + shadingEngine.name() +
                                             "\" of type " + shadingEngine.typeName() + " for shader is not a shader but a " +
                                             MString(AiNodeEntryGetTypeName(entry)));
                  }
                  else
                  {
                     AiNodeSetPtr(atNode, "shader", shader);
                     
                     if (AiNodeLookUpUserParameter(atNode, "mtoa_shading_groups") == 0)
                     {
                        AiNodeDeclare(atNode, "mtoa_shading_groups", "constant ARRAY NODE");
                        AiNodeSetArray(atNode, "mtoa_shading_groups", AiArrayConvert(1, 1, AI_TYPE_NODE, &shader));
                     }
                  }
               }
            }
         }
      }
   }
   
   ExportLightLinking(atNode);
   
   MPlug plug = FindMayaPlug("aiTraceSets");
   if (!plug.isNull())
   {
      ExportTraceSets(atNode, plug);
   }
   
   // Call cleanup command on last export step
   
   if (!IsMotionBlurEnabled() || !IsLocalMotionBlurEnabled() || int(step) >= (int(GetNumMotionSteps()) - 1))
   {
      if (HasParameter(anodeEntry, "disp_padding", atNode))
      {
         float padding = AiNodeGetFlt(atNode, "disp_padding");
         
         AtPoint cmin = AiNodeGetPnt(atNode, "min");
         AtPoint cmax = AiNodeGetPnt(atNode, "max");
         
         cmin.x -= padding;
         cmin.y -= padding;
         cmin.z -= padding;
         cmax.x += padding;
         cmax.y += padding;
         cmax.z += padding;
         
         AiNodeSetPnt(atNode, "min", cmin.x, cmin.y, cmin.z);
         AiNodeSetPnt(atNode, "max", cmax.x, cmax.y, cmax.z);
      }
      
      if (cleanupCmd != "")
      {
         command = cleanupCmd += "((\"" + m_dagPath.partialPathName() + "\", \"";
         command += AiNodeGetName(atNode);
         command += "\"), ";
         
         if (!m_masterNode)
         {
            command += "None)";
         }
         else
         {
            command += "(\"" + GetMasterInstance().partialPathName() + "\", \"";
            command += AiNodeGetName(m_masterNode);
            command += "\"))";
         }
         
         status = MGlobal::executePythonCommand(command);
         
         if (!status)
         {
            AiMsgError("[mtoa.scriptedTranslators] Failed to cleanup node \"%s\".", node.name().asChar());
         }
      }
   }
}