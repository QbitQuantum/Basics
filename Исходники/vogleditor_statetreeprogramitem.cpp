vogleditor_stateTreeProgramItem::vogleditor_stateTreeProgramItem(QString name, QString value, vogleditor_stateTreeItem *parentNode, vogl_program_state &state, const vogl_context_info &info)
    : vogleditor_stateTreeItem(name, value, parentNode),
      m_pState(&state)
{
    QString tmp;

    // basic info
    this->appendChild(new vogleditor_stateTreeProgramBoolItem("GL_LINK_STATUS", &vogl_program_state::get_link_status, this, state));
    if (info.supports_extension("GL_ARB_separate_shader_objects"))
        this->appendChild(new vogleditor_stateTreeProgramBoolItem("GL_PROGRAM_SEPARABLE", &vogl_program_state::get_separable, this, state));
    this->appendChild(new vogleditor_stateTreeProgramBoolItem("GL_DELETE_STATUS", &vogl_program_state::get_marked_for_deletion, this, state));
    this->appendChild(new vogleditor_stateTreeProgramBoolItem("GL_VALIDATE_STATUS", &vogl_program_state::get_verify_status, this, state));
    if (info.get_version() >= VOGL_GL_VERSION_3_1)
    {
        this->appendChild(new vogleditor_stateTreeProgramUIntItem("GL_ACTIVE_UNIFORM_BLOCKS", &vogl_program_state::get_num_active_uniform_blocks, this, state));
    }

    // program binary
    this->appendChild(new vogleditor_stateTreeItem("GL_PROGRAM_BINARY_RETRIEVABLE_HINT", "TODO", this));
    this->appendChild(new vogleditor_stateTreeProgramUIntItem("GL_PROGRAM_BINARY_LENGTH", &vogl_program_state::get_program_binary_size, this, state));
    this->appendChild(new vogleditor_stateTreeProgramEnumItem("GL_PROGRAM_BINARY_FORMAT", &vogl_program_state::get_program_binary_format, this, state));
    if (m_pState->get_program_binary().size() > 0)
    {
        this->appendChild(new vogleditor_stateTreeItem("Program Binary", "TODO: open in a new tab", this));
    }

    // info log
    this->appendChild(new vogleditor_stateTreeProgramLogItem("GL_INFO_LOG_LENGTH", &vogl_program_state::get_info_log, this, state));

    // linked shaders
    const vogl_unique_ptr<vogl_program_state> &linked_program = m_pState->get_link_time_snapshot();
    if (linked_program.get())
    {
        uint num_attached_shaders = linked_program->get_shaders().size();
        vogleditor_stateTreeItem *pLinkedShadersNode = new vogleditor_stateTreeItem("Linked Shaders", tmp.sprintf("[%u]", num_attached_shaders), this);
        this->appendChild(pLinkedShadersNode);

        for (uint i = 0; i < num_attached_shaders; i++)
        {
            vogl_shader_state &shader = const_cast<vogl_shader_state &>(linked_program->get_shaders()[i]);
            GLuint64 shaderId = shader.get_snapshot_handle();
            pLinkedShadersNode->appendChild(new vogleditor_stateTreeShaderItem(tmp.sprintf("%" PRIu64, shaderId), enum_to_string(shader.get_shader_type()), pLinkedShadersNode, shader));
        }
    }

    // attached shaders
    uint num_attached_shaders = m_pState->get_shaders().size();
    vogleditor_stateTreeItem *pAttachedShadersNode = new vogleditor_stateTreeItem("GL_ATTACHED_SHADERS", tmp.sprintf("[%u]", num_attached_shaders), this);
    this->appendChild(pAttachedShadersNode);
    for (uint i = 0; i < num_attached_shaders; i++)
    {
        vogl_shader_state &shader = const_cast<vogl_shader_state &>(m_pState->get_shaders()[i]);
        GLuint64 shaderId = shader.get_snapshot_handle();
        pAttachedShadersNode->appendChild(new vogleditor_stateTreeShaderItem(tmp.sprintf("%" PRIu64, shaderId), enum_to_string(shader.get_shader_type()), pAttachedShadersNode, shader));
    }

    // active attribs
    vogleditor_stateTreeItem *pAttribsNode = new vogleditor_stateTreeItem("GL_ACTIVE_ATTRIBUTES", tmp.sprintf("[%u]", m_pState->get_num_active_attribs()), this);
    this->appendChild(pAttribsNode);
    uint num_active_attributes = m_pState->get_attrib_state_vec().size();
    for (uint i = 0; i < num_active_attributes; i++)
    {
        const vogl_program_attrib_state &attrib = m_pState->get_attrib_state_vec()[i];
        vogleditor_stateTreeProgramAttribItem *pItem = new vogleditor_stateTreeProgramAttribItem(tmp.sprintf("%s", attrib.m_name.get_ptr()), pAttribsNode, attrib);
        m_attribItems.push_back(pItem);
        pAttribsNode->appendChild(pItem);
    }

    // uniforms
    vogleditor_stateTreeItem *pUniformsNode = new vogleditor_stateTreeItem("GL_ACTIVE_UNIFORMS", tmp.sprintf("[%u]", m_pState->get_num_active_uniforms()), this);
    this->appendChild(pUniformsNode);
    uint num_uniforms = m_pState->get_uniform_state_vec().size();
    for (uint i = 0; i < num_uniforms; i++)
    {
        const vogl_program_uniform_state &uniform = m_pState->get_uniform_state_vec()[i];
        //      pUniformsNode->appendChild(new vogleditor_stateTreeItem(QString(uniform.m_name.get_ptr()), tmp.sprintf("Loc: %d, Size: %d, Type: %s", uniform.m_base_location, uniform.m_size, enum_to_string(uniform.m_type).toStdString().c_str()), pUniformsNode));
        vogleditor_stateTreeProgramUniformItem *pItem = new vogleditor_stateTreeProgramUniformItem(QString(uniform.m_name.get_ptr()), pUniformsNode, uniform);
        m_uniformItems.push_back(pItem);
        pUniformsNode->appendChild(pItem);
    }

    // uniform blocks
}