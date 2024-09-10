// Reference code (it's in document)
void AStar::FindPath(Node *start, Node *end)
{
    start->SetF(0);
    start->SetG(0);
    start->SetH(0);
    this->PushNode(start);

    while (open.count() > 0)
    {
        // Find node by lowest F value
        Node *node = this->PopNode();
        this->IncreaseNodeCount();

        if (node == end)
        {
            this->ReconstructPath(end);
            return;
        }

        closed.append(node);

        for (int i = 0; i < node->GetConnectors().count(); i++)
        {
            Connector *connector = node->GetConnectors().at(i);
            Node *neighbour = connector->GetChild();

            if (this->closed.contains(neighbour))
                continue;

            double g = node->GetG() + GetCost(node,connector);

            if (!open.contains(neighbour) || g < neighbour->GetG())
            {
                neighbour->SetParent(node);
                neighbour->SetG(g);
                neighbour->SetH(GetHeuristic(neighbour,end));
                neighbour->SetF(neighbour->GetG() + neighbour->GetH());
                //this->IncreaseNodeCount();

                if (!this->open.contains(neighbour))
                    this->PushNode(neighbour);
            }
        }
    }

    this->ReconstructPath(end);
}