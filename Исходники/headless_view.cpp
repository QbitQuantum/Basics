HeadlessView::~HeadlessView() {
    activate();
    clearBuffers();
    deactivate();

    destroyContext();
}