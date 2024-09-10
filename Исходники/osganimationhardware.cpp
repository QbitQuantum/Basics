    bool init(osgAnimation::RigGeometry& geom)
    {
        osg::Vec3Array* pos = dynamic_cast<osg::Vec3Array*>(geom.getVertexArray());
        if (!pos) {
            osg::notify(osg::WARN) << "RigTransformHardware no vertex array in the geometry " << geom.getName() << std::endl;
            return false;
        }

        if (!geom.getSkeleton()) {
            osg::notify(osg::WARN) << "RigTransformHardware no skeleting set in geometry " << geom.getName() << std::endl;
            return false;
        }

        osgAnimation::BoneMapVisitor mapVisitor;
        geom.getSkeleton()->accept(mapVisitor);
        osgAnimation::BoneMap bm = mapVisitor.getBoneMap();

        if (!createPalette(pos->size(),bm, geom.getVertexInfluenceSet().getVertexToBoneList()))
            return false;

        int attribIndex = 11;
        int nbAttribs = getNumVertexAttrib();

        // use a global program for all avatar
        if (!program.valid()) {
            program = new osg::Program;
            program->setName("HardwareSkinning");
            if (!_shader.valid())
                _shader = osg::Shader::readShaderFile(osg::Shader::VERTEX,"shaders/skinning.vert");

            if (!_shader.valid()) {
                osg::notify(osg::WARN) << "RigTransformHardware can't load VertexShader" << std::endl;
                return false;
            }

            // replace max matrix by the value from uniform
            {
                std::string str = _shader->getShaderSource();
                std::string toreplace = std::string("MAX_MATRIX");
                std::size_t start = str.find(toreplace);
                std::stringstream ss;
                ss << getMatrixPaletteUniform()->getNumElements();
                str.replace(start, toreplace.size(), ss.str());
                _shader->setShaderSource(str);
                osg::notify(osg::INFO) << "Shader " << str << std::endl;
            }

            program->addShader(_shader.get());

            for (int i = 0; i < nbAttribs; i++)
            {
                std::stringstream ss;
                ss << "boneWeight" << i;
                program->addBindAttribLocation(ss.str(), attribIndex + i);

                osg::notify(osg::INFO) << "set vertex attrib " << ss.str() << std::endl;
            }
        }
        for (int i = 0; i < nbAttribs; i++)
        {
            std::stringstream ss;
            ss << "boneWeight" << i;
            geom.setVertexAttribArray(attribIndex + i, getVertexAttrib(i));
        }

        osg::ref_ptr<osg::StateSet> ss = new osg::StateSet;
        ss->addUniform(getMatrixPaletteUniform());
        ss->addUniform(new osg::Uniform("nbBonesPerVertex", getNumBonesPerVertex()));
        ss->setAttributeAndModes(program.get());
        geom.setStateSet(ss.get());
        _needInit = false;
        return true;
    }