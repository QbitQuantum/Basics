bool SceneMouse::mouseMoved(const OIS::MouseEvent& _arg)
{
    const OIS::MouseState ms = _arg.state;

    // check if handled by the camera
    if (!gEnv->cameraManager || gEnv->cameraManager->mouseMoved(_arg))
        return true;

    // experimental mouse hack
    if (ms.buttonDown(OIS::MB_Left) && mouseGrabState == 0)
    {
        lastMouseY = ms.Y.abs;
        lastMouseX = ms.X.abs;

        Ray mouseRay = getMouseRay();

        // walk all trucks
        Beam** trucks = m_sim_controller->GetBeamFactory()->getTrucks();
        int trucksnum = m_sim_controller->GetBeamFactory()->getTruckCount();
        minnode = -1;
        grab_truck = NULL;
        for (int i = 0; i < trucksnum; i++)
        {
            if (trucks[i] && trucks[i]->state == SIMULATED)
            {
                // check if our ray intersects with the bounding box of the truck
                std::pair<bool, Real> pair = mouseRay.intersects(trucks[i]->boundingBox);
                if (!pair.first)
                    continue;

                for (int j = 0; j < trucks[i]->free_node; j++)
                {
                    if (trucks[i]->node_mouse_grab_disabled[j])
                        continue;

                    // check if our ray intersects with the node
                    std::pair<bool, Real> pair = mouseRay.intersects(Sphere(trucks[i]->nodes[j].AbsPosition, 0.1f));
                    if (pair.first)
                    {
                        // we hit it, check if its the nearest node
                        if (pair.second < mindist)
                        {
                            mindist = pair.second;
                            minnode = j;
                            grab_truck = trucks[i];
                            break;
                        }
                    }
                }
            }

            if (grab_truck)
                break;
        }

        // check if we hit a node
        if (grab_truck && minnode != -1)
        {
            mouseGrabState = 1;
            pickLineNode->setVisible(true);

            for (std::vector<hook_t>::iterator it = grab_truck->hooks.begin(); it != grab_truck->hooks.end(); it++)
            {
                if (it->hookNode->id == minnode)
                {
                    grab_truck->hookToggle(it->group, MOUSE_HOOK_TOGGLE, minnode);
                }
            }
        }
    }
    else if (ms.buttonDown(OIS::MB_Left) && mouseGrabState == 1)
    {
        // force applying and so forth happens in update()
        lastMouseY = ms.Y.abs;
        lastMouseX = ms.X.abs;
        // not fixed
        return false;
    }
    else if (!ms.buttonDown(OIS::MB_Left) && mouseGrabState == 1)
    {
        releaseMousePick();
        // not fixed
        return false;
    }

    return false;
}