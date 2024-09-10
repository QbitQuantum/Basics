                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);
                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWMechanics::CreatureStats::AiSetting setting = (MWMechanics::CreatureStats::AiSetting)mIndex;

                    MWMechanics::Stat<int> stat = ptr.getClass().getCreatureStats(ptr).getAiSetting(setting);
                    stat.setModified(value, 0);
                    ptr.getClass().getCreatureStats(ptr).setAiSetting(setting, stat);
                }