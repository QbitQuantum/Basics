void ShaderParamsDialog::buildLayout()
{
   QPushButton *loadButton = NULL;
   QPushButton *saveButton = NULL;
   QPushButton *removeButton = NULL;
   QPushButton *applyButton = NULL;
   QHBoxLayout *topButtonLayout = NULL;
   QMenu *loadMenu = NULL;
   QMenu *saveMenu = NULL;
   QMenu *removeMenu = NULL;
   struct video_shader *menu_shader = NULL;
   struct video_shader *video_shader = NULL;
   struct video_shader *avail_shader = NULL;
   const char *shader_path = NULL;
   unsigned i;
   bool hasPasses = false;

   getShaders(&menu_shader, &video_shader);

   /* NOTE: For some reason, menu_shader_get() returns a COPY of what get_current_shader() gives us.
    * And if you want to be able to change shader settings/parameters from both the raster menu and
    * Qt at the same time... you must change BOTH or one will overwrite the other.
    *
    * AND, during a context reset, video_shader will be NULL but not menu_shader, so don't totally bail
    * just because video_shader is NULL.
    *
    * Someone please fix this mess.
    */

   if (video_shader)
   {
      avail_shader = video_shader;

      if (video_shader->passes == 0)
         setWindowTitle(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SHADER_OPTIONS));
   }
   /* Normally we'd only use video_shader, but the vulkan driver returns a NULL shader when there
    * are zero passes, so just fall back to menu_shader.
    */
   else if (menu_shader)
   {
      avail_shader = menu_shader;

      if (menu_shader->passes == 0)
         setWindowTitle(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SHADER_OPTIONS));
   }
   else
   {
      setWindowTitle(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SHADER_OPTIONS));

      /* no shader is available yet, just keep retrying until it is */
      QTimer::singleShot(0, this, SLOT(buildLayout()));
      return;
   }

   clearLayout();

   /* Only check video_shader for the path, menu_shader seems stale... e.g. if you remove all the shader passes,
    * it still has the old path in it, but video_shader does not
    */
   if (video_shader)
   {
      if (!string_is_empty(video_shader->path))
      {
         shader_path = video_shader->path;
         setWindowTitle(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_CURRENT_SHADER)) + ": " + QFileInfo(shader_path).fileName());
      }
   }
   else if (menu_shader)
   {
      if (!string_is_empty(menu_shader->path))
      {
         shader_path = menu_shader->path;
         setWindowTitle(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_CURRENT_SHADER)) + ": " + QFileInfo(shader_path).fileName());
      }
   }
   else
      setWindowTitle(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SHADER_OPTIONS));

   loadButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_LOAD), this);
   saveButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_SAVE), this);
   removeButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_REMOVE), this);
   applyButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_APPLY), this);

   loadMenu = new QMenu(loadButton);
   loadMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SHADER_PRESET), this, SLOT(onShaderLoadPresetClicked()));
   loadMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_SHADER_ADD_PASS), this, SLOT(onShaderAddPassClicked()));

   loadButton->setMenu(loadMenu);

   saveMenu = new QMenu(saveButton);
   saveMenu->addAction(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SHADER_PRESET_SAVE_AS)) + "...", this, SLOT(onShaderSavePresetAsClicked()));
   saveMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SHADER_PRESET_SAVE_CORE), this, SLOT(onShaderSaveCorePresetClicked()));
   saveMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SHADER_PRESET_SAVE_PARENT), this, SLOT(onShaderSaveParentPresetClicked()));
   saveMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SHADER_PRESET_SAVE_GAME), this, SLOT(onShaderSaveGamePresetClicked()));

   saveButton->setMenu(saveMenu);

   removeMenu = new QMenu(removeButton);

   /* When there are no passes, at least on first startup, it seems video_shader erroneously shows 1 pass, with an empty source file.
    * So we use menu_shader instead for that.
    */
   if (menu_shader)
   {
      for (i = 0; i < menu_shader->passes; i++)
      {
         QFileInfo fileInfo(menu_shader->pass[i].source.path);
         QString shaderBasename = fileInfo.completeBaseName();
         QAction *action = removeMenu->addAction(shaderBasename, this, SLOT(onShaderRemovePassClicked()));

         action->setData(i);
      }
   }

   removeMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_SHADER_CLEAR_ALL_PASSES), this, SLOT(onShaderClearAllPassesClicked()));

   removeButton->setMenu(removeMenu);

   connect(applyButton, SIGNAL(clicked()), this, SLOT(onShaderApplyClicked()));

   topButtonLayout = new QHBoxLayout();
   topButtonLayout->addWidget(loadButton);
   topButtonLayout->addWidget(saveButton);
   topButtonLayout->addWidget(removeButton);
   topButtonLayout->addWidget(applyButton);

   m_layout->addLayout(topButtonLayout);

   /* NOTE: We assume that parameters are always grouped in order by the pass number, e.g., all parameters for pass 0 come first, then params for pass 1, etc. */
   for (i = 0; avail_shader && i < avail_shader->passes; i++)
   {
      QFormLayout *form = NULL;
      QGroupBox *groupBox = NULL;
      QFileInfo fileInfo(avail_shader->pass[i].source.path);
      QString shaderBasename = fileInfo.completeBaseName();
      QHBoxLayout *filterScaleHBoxLayout = NULL;
      QComboBox *filterComboBox = new QComboBox(this);
      QComboBox *scaleComboBox = new QComboBox(this);
      QToolButton *moveDownButton = NULL;
      QToolButton *moveUpButton = NULL;
      unsigned j = 0;

      /* Sometimes video_shader shows 1 pass with no source file, when there are really 0 passes. */
      if (shaderBasename.isEmpty())
         continue;

      hasPasses = true;

      filterComboBox->setProperty("pass", i);
      scaleComboBox->setProperty("pass", i);

      moveDownButton = new QToolButton(this);
      moveDownButton->setText("↓");
      moveDownButton->setProperty("pass", i);

      moveUpButton = new QToolButton(this);
      moveUpButton->setText("↑");
      moveUpButton->setProperty("pass", i);

      /* Can't move down if we're already at the bottom. */
      if (i < avail_shader->passes - 1)
         connect(moveDownButton, SIGNAL(clicked()), this, SLOT(onShaderPassMoveDownClicked()));
      else
         moveDownButton->setDisabled(true);

      /* Can't move up if we're already at the top. */
      if (i > 0)
         connect(moveUpButton, SIGNAL(clicked()), this, SLOT(onShaderPassMoveUpClicked()));
      else
         moveUpButton->setDisabled(true);

      for (;;)
      {
         QString filterLabel = getFilterLabel(j);

         if (filterLabel.isEmpty())
            break;

         if (j == 0)
            filterLabel = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DONT_CARE);

         filterComboBox->addItem(filterLabel, j);

         j++;
      }

      for (j = 0; j < 7; j++)
      {
         QString label;

         if (j == 0)
            label = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DONT_CARE);
         else
            label = QString::number(j) + "x";

         scaleComboBox->addItem(label, j);
      }

      filterComboBox->setCurrentIndex(static_cast<int>(avail_shader->pass[i].filter));
      scaleComboBox->setCurrentIndex(static_cast<int>(avail_shader->pass[i].fbo.scale_x));

      /* connect the signals only after the initial index is set */
      connect(filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onFilterComboBoxIndexChanged(int)));
      connect(scaleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onScaleComboBoxIndexChanged(int)));

      form = new QFormLayout();
      groupBox = new QGroupBox(shaderBasename);
      groupBox->setLayout(form);
      groupBox->setProperty("pass", i);
      groupBox->setContextMenuPolicy(Qt::CustomContextMenu);

      connect(groupBox, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onGroupBoxContextMenuRequested(const QPoint&)));

      m_layout->addWidget(groupBox);

      filterScaleHBoxLayout = new QHBoxLayout();
      filterScaleHBoxLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
      filterScaleHBoxLayout->addWidget(new QLabel(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_FILTER)) + ":", this));
      filterScaleHBoxLayout->addWidget(filterComboBox);
      filterScaleHBoxLayout->addWidget(new QLabel(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SCALE)) + ":", this));
      filterScaleHBoxLayout->addWidget(scaleComboBox);
      filterScaleHBoxLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));

      if (moveUpButton)
         filterScaleHBoxLayout->addWidget(moveUpButton);

      if (moveDownButton)
         filterScaleHBoxLayout->addWidget(moveDownButton);

      form->addRow("", filterScaleHBoxLayout);

      for (j = 0; j < avail_shader->num_parameters; j++)
      {
         struct video_shader_parameter *param = &avail_shader->parameters[j];

         if (param->pass != static_cast<int>(i))
            continue;

         addShaderParam(param, form);
      }
   }

   if (!hasPasses)
   {
      QLabel *noParamsLabel = new QLabel(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_SHADER_NO_PASSES), this);
      noParamsLabel->setAlignment(Qt::AlignCenter);

      m_layout->addWidget(noParamsLabel);
   }

   m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

   /* Why is this required?? The layout is corrupt without both resizes. */
   resize(width() + 1, height());
   show();
   resize(width() - 1, height());
}