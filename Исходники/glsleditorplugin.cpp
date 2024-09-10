bool GLSLEditorPlugin::initialize(const QStringList & /*arguments*/, QString *error_message)
{
    Core::ICore *core = Core::ICore::instance();
    if (!core->mimeDatabase()->addMimeTypes(QLatin1String(":/glsleditor/GLSLEditor.mimetypes.xml"), error_message))
        return false;

    parseGlslFile(QLatin1String("glsl_120.frag"), &m_glsl_120_frag);
    parseGlslFile(QLatin1String("glsl_120.vert"), &m_glsl_120_vert);
    parseGlslFile(QLatin1String("glsl_120_common.glsl"), &m_glsl_120_common);
    parseGlslFile(QLatin1String("glsl_es_100.frag"), &m_glsl_es_100_frag);
    parseGlslFile(QLatin1String("glsl_es_100.vert"), &m_glsl_es_100_vert);
    parseGlslFile(QLatin1String("glsl_es_100_common.glsl"), &m_glsl_es_100_common);


//    m_modelManager = new ModelManager(this);
//    addAutoReleasedObject(m_modelManager);

    addAutoReleasedObject(new GLSLHoverHandler(this));

    Core::Context context(GLSLEditor::Constants::C_GLSLEDITOR_ID);

    m_editor = new GLSLEditorFactory(this);
    addObject(m_editor);

    addAutoReleasedObject(new GLSLCompletionAssistProvider);

    m_actionHandler = new TextEditor::TextEditorActionHandler(GLSLEditor::Constants::C_GLSLEDITOR_ID,
                                                              TextEditor::TextEditorActionHandler::Format
                                                              | TextEditor::TextEditorActionHandler::UnCommentSelection
                                                              | TextEditor::TextEditorActionHandler::UnCollapseAll);
    m_actionHandler->initializeActions();

    Core::ActionManager *am =  core->actionManager();
    Core::ActionContainer *contextMenu = am->createMenu(GLSLEditor::Constants::M_CONTEXT);
    Core::ActionContainer *glslToolsMenu = am->createMenu(Core::Id(Constants::M_TOOLS_GLSL));
    glslToolsMenu->setOnAllDisabledBehavior(Core::ActionContainer::Hide);
    QMenu *menu = glslToolsMenu->menu();
    //: GLSL sub-menu in the Tools menu
    menu->setTitle(tr("GLSL"));
    am->actionContainer(Core::Constants::M_TOOLS)->addMenu(glslToolsMenu);

    Core::Command *cmd = 0;

    // Insert marker for "Refactoring" menu:
    Core::Context globalContext(Core::Constants::C_GLOBAL);
    Core::Command *sep = createSeparator(am, this, globalContext,
                                         Constants::SEPARATOR1);
    sep->action()->setObjectName(Constants::M_REFACTORING_MENU_INSERTION_POINT);
    contextMenu->addAction(sep);
    contextMenu->addAction(createSeparator(am, this, globalContext,
                                           Constants::SEPARATOR2));

    cmd = am->command(TextEditor::Constants::UN_COMMENT_SELECTION);
    contextMenu->addAction(cmd);

    error_message->clear();

    Core::FileIconProvider *iconProvider = Core::FileIconProvider::instance();
    Core::MimeDatabase *mimeDatabase = Core::ICore::instance()->mimeDatabase();
    iconProvider->registerIconOverlayForMimeType(QIcon(QLatin1String(":/glsleditor/images/glslfile.png")),
                                                 mimeDatabase->findByType(QLatin1String(GLSLEditor::Constants::GLSL_MIMETYPE)));
    iconProvider->registerIconOverlayForMimeType(QIcon(QLatin1String(":/glsleditor/images/glslfile.png")),
                                                 mimeDatabase->findByType(QLatin1String(GLSLEditor::Constants::GLSL_MIMETYPE_VERT)));
    iconProvider->registerIconOverlayForMimeType(QIcon(QLatin1String(":/glsleditor/images/glslfile.png")),
                                                 mimeDatabase->findByType(QLatin1String(GLSLEditor::Constants::GLSL_MIMETYPE_FRAG)));
    iconProvider->registerIconOverlayForMimeType(QIcon(QLatin1String(":/glsleditor/images/glslfile.png")),
                                                 mimeDatabase->findByType(QLatin1String(GLSLEditor::Constants::GLSL_MIMETYPE_VERT_ES)));
    iconProvider->registerIconOverlayForMimeType(QIcon(QLatin1String(":/glsleditor/images/glslfile.png")),
                                                 mimeDatabase->findByType(QLatin1String(GLSLEditor::Constants::GLSL_MIMETYPE_FRAG_ES)));

    Core::BaseFileWizardParameters fragWizardParameters(Core::IWizard::FileWizard);
    fragWizardParameters.setCategory(QLatin1String(Constants::WIZARD_CATEGORY_GLSL));
    fragWizardParameters.setDisplayCategory(QCoreApplication::translate("GLSLEditor", Constants::WIZARD_TR_CATEGORY_GLSL));
    fragWizardParameters.setDescription
        (tr("Creates a fragment shader in the OpenGL/ES 2.0 Shading "
            "Language (GLSL/ES). Fragment shaders generate the final "
            "pixel colors for triangles, points and lines rendered "
            "with OpenGL."));
    fragWizardParameters.setDisplayName(tr("Fragment Shader (OpenGL/ES 2.0)"));
    fragWizardParameters.setId(QLatin1String("F.GLSL"));
    addAutoReleasedObject(new GLSLFileWizard(fragWizardParameters, GLSLFileWizard::FragmentShaderES, core));

    Core::BaseFileWizardParameters vertWizardParameters(Core::IWizard::FileWizard);
    vertWizardParameters.setCategory(QLatin1String(Constants::WIZARD_CATEGORY_GLSL));
    vertWizardParameters.setDisplayCategory(QCoreApplication::translate("GLSLEditor", Constants::WIZARD_TR_CATEGORY_GLSL));
    vertWizardParameters.setDescription
        (tr("Creates a vertex shader in the OpenGL/ES 2.0 Shading "
            "Language (GLSL/ES). Vertex shaders transform the "
            "positions, normals and texture co-ordinates of "
            "triangles, points and lines rendered with OpenGL."));
    vertWizardParameters.setDisplayName(tr("Vertex Shader (OpenGL/ES 2.0)"));
    vertWizardParameters.setId(QLatin1String("G.GLSL"));
    addAutoReleasedObject(new GLSLFileWizard(vertWizardParameters, GLSLFileWizard::VertexShaderES, core));

    fragWizardParameters.setDescription
        (tr("Creates a fragment shader in the Desktop OpenGL Shading "
            "Language (GLSL). Fragment shaders generate the final "
            "pixel colors for triangles, points and lines rendered "
            "with OpenGL."));
    fragWizardParameters.setDisplayName(tr("Fragment Shader (Desktop OpenGL)"));
    fragWizardParameters.setId(QLatin1String("J.GLSL"));
    addAutoReleasedObject(new GLSLFileWizard(fragWizardParameters, GLSLFileWizard::FragmentShaderDesktop, core));

    vertWizardParameters.setDescription
        (tr("Creates a vertex shader in the Desktop OpenGL Shading "
            "Language (GLSL). Vertex shaders transform the "
            "positions, normals and texture co-ordinates of "
            "triangles, points and lines rendered with OpenGL."));
    vertWizardParameters.setDisplayName(tr("Vertex Shader (Desktop OpenGL)"));
    vertWizardParameters.setId(QLatin1String("K.GLSL"));
    addAutoReleasedObject(new GLSLFileWizard(vertWizardParameters, GLSLFileWizard::VertexShaderDesktop, core));

    return true;
}