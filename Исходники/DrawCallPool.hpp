            inline static
            Ptr
            create(RendererPtr renderer)
            {
                Ptr ptr = std::shared_ptr<DrawCallPool>(new DrawCallPool(renderer));

                ptr->initialize();

                return ptr;
            }