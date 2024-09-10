        void update(dune::deferred_renderer* renderer)
        {
            if (combo_render_targets)
            {
                combo_render_targets->AddItem(L"None", IntToPtr(0));

                for (auto g = renderer->buffers().begin(); g != renderer->buffers().end(); ++g)
                {
                    dune::tstring w = g->second->name;
                    combo_render_targets->AddItem(w.c_str(), IntToPtr(1));
                }
            }
        }