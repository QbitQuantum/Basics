    void PhantomGame::exit(int returncode) {
        _running = false;
        vector<Composite*> components = getComponents();
        for(auto component = components.begin(); component != components.end(); ++component) {
            (*component)->destroy();
        }
        components.clear();

        clearDisposables();

        onExit(returncode);
    }