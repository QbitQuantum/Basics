 virtual R handleMethodInvocation(ArgumentsTuple<arglist...> & args) override
 {
     std::shared_ptr<Destructible> destructablePtr = _recordedActions.front();
     Destructible &destructable = *destructablePtr;
     Action<R, arglist...> &action = dynamic_cast<Action<R, arglist...> &>(destructable);
     std::function<void()> finallyClause = [&]() -> void {
         if (action.isDone())
             _recordedActions.erase(_recordedActions.begin());
     };
     Finally onExit(finallyClause);
     return action.invoke(args);
 }