void EnginePlayer::Apply(const Event& event) {
    class EnginePlayerVisitor: public EventVisitor {
    public:
        EnginePlayerVisitor(EnginePlayer* engine) :
            engine(engine) {
        }

        void Visit(const EventKeyPressed& eventKeyPressed) {
            engine->processEventKeyPressed(eventKeyPressed);
            engine->refleshPlayersAction();
        }

        void Visit(const EventKeyReleased& eventKeyReleased) {
            engine->processEventKeyReleased(eventKeyReleased);
            engine->refleshPlayersAction();
        }

        void Visit(const EventMouseButtonPressed& eventMouseButtonPressed) {
            engine->processEventMouseButtonPressed(eventMouseButtonPressed);
            engine->refleshPlayersAction();
        }

        void Visit(const EventMouseButtonReleased& eventMouseButtonReleased) {
            engine->processEventMouseButtonReleased(eventMouseButtonReleased);
            engine->refleshPlayersAction();
        }
    private:
        EnginePlayer* engine;
    };
    EnginePlayerVisitor visitor(this);
    event.accept(visitor);
}