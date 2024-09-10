void EngineSound::Apply(const Event& event) {
    class EngineSoundVisitor: public EventVisitor {
    public:
        EngineSoundVisitor(EngineSound* engine) :
            engine(engine) {
        }

        void Visit(const EventProjectileAdded& eventProjectileAdded) {
            engine->processEventProjectileAdded(eventProjectileAdded);
        }

    private:
        EngineSound* engine;
    };
    EngineSoundVisitor visitor(this);
    event.accept(visitor);
}