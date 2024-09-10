// Agent Manager Destructor: called at the end of the show
AgentManager::~AgentManager()
{
    // Terminate using low-level functions
    for (Agent *c = first; c != 0; c = c->next)
	c->terminate(true);
}