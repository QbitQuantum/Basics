/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ComponentTransitPtr SceneComponentTreeComponentGenerator::getTreeComponent(Tree* const Parent, 
                                                                            const boost::any& Value, 
                                                                            bool IsSelected, 
                                                                            bool Expanded, 
                                                                            bool Leaf, 
                                                                            UInt32 Row, 
                                                                            bool HasFocus)
{
    std::string Text;
    if(Value.type() == typeid(Scene* const))
    {
        Text = "Scene";
    }
    else if(Value.type() == typeid(UInt32))
    {
        switch(boost::any_cast<UInt32>(Value))
        {
        case SceneTreeModel::BasicComponent:              //Basic
            Text = "Basic";
            break;
        case SceneTreeModel::BackgroundComponent:              //Background
            Text = "Background";
            break;
        case SceneTreeModel::CameraComponent:              //Camera
            Text = "Camera";
            break;
        case SceneTreeModel::ForegroundsComponent:              //Foregrounds
            Text = "Foregrounds";
            break;
        case SceneTreeModel::SceneObjectsComponent:              //Models
            Text = "SceneObjects";
            break;
        case SceneTreeModel::LightsComponent:              //Models
            Text = "Lights";
            break;
        case SceneTreeModel::DynamicsComponent:              //Dynamics
            Text = "Dynamics";
            break;
        case SceneTreeModel::ScriptsComponent:              //Scripts
            Text = "Scripts";
            break;
        case SceneTreeModel::BehavioursComponent:              //Behaviours
            Text = "Behaviours";
            break;
        case SceneTreeModel::AnimationsComponent:              //Animations
            Text = "Animations";
            break;
        }
    }
    else if(Value.type() == typeid(Foreground* const))
    {
        ForegroundRecPtr FG= boost::any_cast<Foreground* const>(Value);
        const Char8* Name(getName(FG));
        Text = std::string(Name ? Name : "No Name" ) + " [" + FG->getType().getName() + "]";
    }
    else if(Value.type() == typeid(SceneObject* const))
    {
        SceneObjectRecPtr SO= boost::any_cast<SceneObject* const>(Value);
        const Char8* Name(getName(SO));
        Text = (Name ? Name : "No Name" );
    }
    else if(Value.type() == typeid(Light* const))
    {
        LightRecPtr SceneLight= boost::any_cast<Light* const>(Value);
        const Char8* Name(getName(SceneLight));
        Text = std::string(Name ? Name : "No Name" ) + " [" + SceneLight->getType().getName() + "]";
    }

    ComponentRecPtr LabelComp = getTreeComponentText(Parent, Text, IsSelected, Expanded, Leaf, Row, HasFocus);

    if(Value.type() == typeid(UInt32))
    {
        switch(boost::any_cast<UInt32>(Value))
        {
        case SceneTreeModel::ForegroundsComponent:              //Foregrounds
            {
                if(_AddForegroundButton == NULL)
                {
                    _AddForegroundButton = MenuButton::create();
                    _AddForegroundButton->setText("+");
                    _AddForegroundButton->setToolTipText("Create new Foreground");
                    _AddForegroundButton->setPreferredSize(Vec2f(17.0f,17.0f));
                    _AddForegroundButton->setAlignment(Vec2f(0.5f,0.5f));
                    _AddForegroundButton->setFont(dynamic_pointer_cast<Label>(LabelComp)->getFont());

                    //Fill with all of the foreground types
                    DerivedFieldContainerComboBoxModelRecPtr MenuModel = DerivedFieldContainerComboBoxModel::create();
                    MenuModel->editMFDerivedFieldContainerTypes()->push_back(Foreground::getClassType().getCName());
                    MenuModel->setIncludeAbstract(false);

                    _AddForegroundButton->setModel(MenuModel);

                    //Connect
                    _AddForegroundConnection.disconnect();
                    _AddForegroundConnection = _AddForegroundButton->connectMenuActionPerformed(boost::bind(&SceneComponentTree::handleAddForeground, _SceneComponentTree, _1, _AddForegroundButton.get()));
                }

                SpringLayoutRecPtr TreeCompLayout = SpringLayout::create();
                PanelRecPtr CompPanel = Panel::createEmpty();

                TreeCompLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, LabelComp, 0, SpringLayoutConstraints::NORTH_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LabelComp, 0, SpringLayoutConstraints::SOUTH_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, LabelComp, 0, SpringLayoutConstraints::EAST_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, LabelComp, 0, SpringLayoutConstraints::WEST_EDGE, CompPanel);

                TreeCompLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AddForegroundButton, -5, SpringLayoutConstraints::EAST_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AddForegroundButton, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CompPanel);

                CompPanel->setLayout(TreeCompLayout);
                CompPanel->pushToChildren(LabelComp);
                CompPanel->pushToChildren(_AddForegroundButton);
                
                return ComponentTransitPtr(CompPanel);
            }
            break;
        case SceneTreeModel::SceneObjectsComponent:              //Models
            {
                if(_AddSceneObjectButton == NULL)
                {
                    _AddSceneObjectButton = Button::create();
                    _AddSceneObjectButton->setText("+");
                    _AddSceneObjectButton->setToolTipText("Create new Scene Object");
                    _AddSceneObjectButton->setPreferredSize(Vec2f(17.0f,17.0f));
                    _AddSceneObjectButton->setAlignment(Vec2f(0.5f,0.5f));
                    _AddSceneObjectButton->setFont(dynamic_pointer_cast<Label>(LabelComp)->getFont());

                    //Connect
                    _AddSceneObjectConnection.disconnect();
                    _AddSceneObjectConnection = _AddSceneObjectButton->connectActionPerformed(boost::bind(&SceneComponentTree::handleAddSceneObject, _SceneComponentTree, _1));
                }

                SpringLayoutRecPtr TreeCompLayout = SpringLayout::create();
                PanelRecPtr CompPanel = Panel::createEmpty();

                TreeCompLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, LabelComp, 0, SpringLayoutConstraints::NORTH_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LabelComp, 0, SpringLayoutConstraints::SOUTH_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, LabelComp, 0, SpringLayoutConstraints::EAST_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, LabelComp, 0, SpringLayoutConstraints::WEST_EDGE, CompPanel);

                TreeCompLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AddSceneObjectButton, -5, SpringLayoutConstraints::EAST_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AddSceneObjectButton, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CompPanel);

                CompPanel->setLayout(TreeCompLayout);
                CompPanel->pushToChildren(LabelComp);
                CompPanel->pushToChildren(_AddSceneObjectButton);
                
                return ComponentTransitPtr(CompPanel);
            }
            break;
        case SceneTreeModel::LightsComponent:              //Lights
            {
                if(_AddLightButton == NULL)
                {
                    _AddLightButton = MenuButton::create();
                    _AddLightButton->setText("+");
                    _AddLightButton->setToolTipText("Create new Light");
                    _AddLightButton->setPreferredSize(Vec2f(17.0f,17.0f));
                    _AddLightButton->setAlignment(Vec2f(0.5f,0.5f));
                    _AddLightButton->setFont(dynamic_pointer_cast<Label>(LabelComp)->getFont());
                    //Connect
                    _AddLightConnection.disconnect();
                    _AddLightConnection = _AddLightButton->connectMenuActionPerformed(boost::bind(&SceneComponentTree::handleAddLight, _SceneComponentTree, _1, _AddLightButton.get()));
                }

                //Fill with all of the light types
                DerivedFieldContainerComboBoxModelRecPtr MenuModel = DerivedFieldContainerComboBoxModel::create();
                MenuModel->editMFDerivedFieldContainerTypes()->push_back(Light::getClassType().getCName());
                MenuModel->setIncludeAbstract(false);

                _AddLightButton->setModel(MenuModel);

                SpringLayoutRecPtr TreeCompLayout = SpringLayout::create();
                PanelRecPtr CompPanel = Panel::createEmpty();

                TreeCompLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, LabelComp, 0, SpringLayoutConstraints::NORTH_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LabelComp, 0, SpringLayoutConstraints::SOUTH_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, LabelComp, 0, SpringLayoutConstraints::EAST_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, LabelComp, 0, SpringLayoutConstraints::WEST_EDGE, CompPanel);

                TreeCompLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AddLightButton, -5, SpringLayoutConstraints::EAST_EDGE, CompPanel);
                TreeCompLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AddLightButton, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CompPanel);

                CompPanel->setLayout(TreeCompLayout);
                CompPanel->pushToChildren(LabelComp);
                CompPanel->pushToChildren(_AddLightButton);
                
                return ComponentTransitPtr(CompPanel);
            }
            break;
        }
    }
    else if(Value.type() == typeid(Foreground* const))
    {
        return createButtonedComp(LabelComp, boost::bind(&SceneComponentTree::handleRemoveForeground, _SceneComponentTree, _1, boost::any_cast<Foreground* const>(Value)));
    }
    else if(Value.type() == typeid(SceneObject* const))
    {
        return createButtonedComp(LabelComp, boost::bind(&SceneComponentTree::handleRemoveSceneObject, _SceneComponentTree, _1, boost::any_cast<SceneObject* const>(Value)));
    }
    else if(Value.type() == typeid(Light* const))
    {
        return createButtonedComp(LabelComp, boost::bind(&SceneComponentTree::handleRemoveLight, _SceneComponentTree, _1, boost::any_cast<Light* const>(Value)));
    }

    return ComponentTransitPtr(LabelComp);
}