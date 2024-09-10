void MakeHouse(IloModel model,
               IloNumExpr cost,
               IloIntervalVarArray allTasks,
               IloIntervalVarArray joeTasks,
               IloIntervalVarArray jimTasks,
               IloIntArray joeLocations,
               IloIntArray jimLocations,
               IloInt loc,
               IloInt rd,
               IloInt dd,
               IloNum weight) {
    IloEnv env = model.getEnv();

    /* CREATE THE INTERVALS VARIABLES. */
    char name[128];

    IloIntervalVarArray tasks(env, NbTasks);
    for (IloInt i=0; i<NbTasks; ++i) {
        sprintf(name, "H%ld-%s", loc, TaskNames[i]);
        tasks[i] = IloIntervalVar(env, TaskDurations[i], name);
        allTasks.add(tasks[i]);
    }

    /* SPAN CONSTRAINT. */
    sprintf(name, "H%ld", loc);
    IloIntervalVar house(env, name);
    model.add(IloSpan(env, house, tasks));

    /* ADDING PRECEDENCE CONSTRAINTS. */
    house.setStartMin(rd);
    model.add(IloEndBeforeStart(env, tasks[masonry],   tasks[carpentry]));
    model.add(IloEndBeforeStart(env, tasks[masonry],   tasks[plumbing]));
    model.add(IloEndBeforeStart(env, tasks[masonry],   tasks[ceiling]));
    model.add(IloEndBeforeStart(env, tasks[carpentry], tasks[roofing]));
    model.add(IloEndBeforeStart(env, tasks[ceiling],   tasks[painting]));
    model.add(IloEndBeforeStart(env, tasks[roofing],   tasks[windows]));
    model.add(IloEndBeforeStart(env, tasks[roofing],   tasks[facade]));
    model.add(IloEndBeforeStart(env, tasks[plumbing],  tasks[facade]));
    model.add(IloEndBeforeStart(env, tasks[roofing],   tasks[garden]));
    model.add(IloEndBeforeStart(env, tasks[plumbing],  tasks[garden]));
    model.add(IloEndBeforeStart(env, tasks[windows],   tasks[moving]));
    model.add(IloEndBeforeStart(env, tasks[facade],    tasks[moving]));
    model.add(IloEndBeforeStart(env, tasks[garden],    tasks[moving]));
    model.add(IloEndBeforeStart(env, tasks[painting],  tasks[moving]));

    /* ALLOCATING TASKS TO WORKERS. */
    joeTasks.add(tasks[masonry]);
    joeLocations.add(loc);
    joeTasks.add(tasks[carpentry]);
    joeLocations.add(loc);
    jimTasks.add(tasks[plumbing]);
    jimLocations.add(loc);
    jimTasks.add(tasks[ceiling]);
    jimLocations.add(loc);
    joeTasks.add(tasks[roofing]);
    joeLocations.add(loc);
    jimTasks.add(tasks[painting]);
    jimLocations.add(loc);
    jimTasks.add(tasks[windows]);
    jimLocations.add(loc);
    joeTasks.add(tasks[facade]);
    joeLocations.add(loc);
    joeTasks.add(tasks[garden]);
    joeLocations.add(loc);
    jimTasks.add(tasks[moving]);
    jimLocations.add(loc);

    /* DEFINING MINIMIZATION OBJECTIVE. */
    cost += TardinessCost(house, dd, weight);
    cost += IloLengthOf(house);
}