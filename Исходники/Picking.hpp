            inline static
            Ptr
            create(NodePtr camera, bool addPickingLayoutToNodes = true, bool emulateMouseWithTouch = true)
            {
                Ptr picking = std::shared_ptr<Picking>(new Picking());

                picking->initialize(camera, addPickingLayoutToNodes, emulateMouseWithTouch);

                return picking;
            }