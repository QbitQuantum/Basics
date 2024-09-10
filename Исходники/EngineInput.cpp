void EngineInput::Apply(const Event& event) {
    class EngineInputVisitor: public EventVisitor {
    public:
        EngineInputVisitor(EngineInput* engine) :
            engine(engine) {
        }

        void Visit(const EventWindowCreated& evenWindowCreated) {
            engine->renderWindow = evenWindowCreated.getWindow();
            engine->input = &(engine->renderWindow->GetInput());
            engine->clientManager->GetInputModel()->SetInput(engine->input);
        }
    private:
        EngineInput* engine;
    };
    EngineInputVisitor visitor(this);
    event.accept(visitor);
}