CustomDialogRecipe::CustomDialogRecipe(Container * parent) :
        CustomControl(parent)
{
    bool connectResult;
    Q_UNUSED(connectResult);

    Container *recipeContainer = new Container();
    recipeContainer->setLayout(new AbsoluteLayout());

    mFlame = ImageView::create("asset:///images/customdialog/flame.png");

    // Connect to the layout handler of the flame image, we need the image size
    // in order to set the pivot point for scaling correctly.
    LayoutUpdateHandler::create(mFlame).onLayoutFrameChanged(this,
            SLOT(flameLayoutFrameUpdated(QRectF)));

    // The flame animation gradually scales the flame up in Y direction and
    // finally triggers the CustomDialog.
    mRisingFlame = SequentialAnimation::create(mFlame)
            .add(ScaleTransition::create(mFlame).toY(1.2).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.1).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.4).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.3).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.6).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.5).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.9).duration(400))
            .add(ScaleTransition::create(mFlame).toY(1.7).duration(400))
            .add(ScaleTransition::create(mFlame).toY(2.0).duration(400)).parent(this);

    // Connect to the animation ended signal, when triggered the dialog will be shown.
    connectResult = connect(mRisingFlame, SIGNAL(ended()), this, SLOT(onHideAnimEnded()));
    Q_ASSERT(connectResult);

    ImageView *candle = ImageView::create("asset:///images/customdialog/background.png");
    candle->setScalingMethod(ScalingMethod::AspectFit);

    // The CustomDialog is added as an attached object since it is visible in the
    // UI from the start. Since a dialog is often used in many different places in an application,
    // it is set up as a separate component. This is to easily add it to other Pages.
    mAlarmDialog = new CustomDialogAlarm(this);
    connectResult = connect(mAlarmDialog, SIGNAL(visibleChanged(bool)), this, SLOT(onDialogVisible(bool)));
    Q_ASSERT(connectResult);

    recipeContainer->add(mFlame);
    recipeContainer->add(candle);

    setRoot(recipeContainer);

    mRisingFlame->play();
}