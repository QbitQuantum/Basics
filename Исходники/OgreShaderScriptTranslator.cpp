//-----------------------------------------------------------------------------
void SGScriptTranslator::translatePass(ScriptCompiler* compiler, const AbstractNodePtr &node)
{
    ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(node.get());    
    Pass* pass = any_cast<Pass*>(obj->parent->context);
    Technique* technique = pass->getParent();
    Material* material = technique->getParent();
    ShaderGenerator* shaderGenerator = ShaderGenerator::getSingletonPtr();
    String dstTechniqueSchemeName = obj->name;
    bool techniqueCreated;

    // Make sure the scheme name is valid - use default if none exists.
    if (dstTechniqueSchemeName.empty()) 
        dstTechniqueSchemeName = ShaderGenerator::DEFAULT_SCHEME_NAME;  


    // Create the shader based technique.
    techniqueCreated = shaderGenerator->createShaderBasedTechnique(material->getName(), 
        material->getGroup(), 
        technique->getSchemeName(), 
        dstTechniqueSchemeName,
        shaderGenerator->getCreateShaderOverProgrammablePass());


    // Case technique successfully created.
    if (techniqueCreated)
    {
        // Go over all the render state properties.
        for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop = static_cast<PropertyAbstractNode*>((*i).get());

                // Handle light count property.
                if (prop->name == "light_count")
                {
                    if (prop->values.size() != 3)
                    {
                        compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    }
                    else
                    {
                        int lightCount[3];

                        if (false == SGScriptTranslator::getInts(prop->values.begin(), prop->values.end(), lightCount, 3))
                        {
                            compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                        }
                        else
                        {
                            shaderGenerator->createScheme(dstTechniqueSchemeName);
                            RenderState* renderState = shaderGenerator->getRenderState(dstTechniqueSchemeName, 
                                material->getName(), material->getGroup(), pass->getIndex());

                            renderState->setLightCount(lightCount);
                            renderState->setLightCountAutoUpdate(false);
                        }
                    }                   
                }

                // Handle the rest of the custom properties.
                else
                {
                    SubRenderState* subRenderState = ShaderGenerator::getSingleton().createSubRenderState(compiler, prop, pass, this);
                    if (subRenderState)
                    {
                        addSubRenderState(subRenderState, dstTechniqueSchemeName, material->getName(), material->getGroup(), pass->getIndex());
                    }
                }               
            }
            else
            {
                processNode(compiler, *i);
            }
        }

        mGeneratedRenderState = NULL;
    }

}