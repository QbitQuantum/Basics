bool RBT::Delete(Node* toDelete)
{
    if (!toDelete)
        return false;

    COLOR deletedColor = toDelete->GetColor();
    Node* toFix;

    if (toDelete->GetLeft() == NIL)
    {
        toFix = toDelete->GetRight();
        Transplant(toDelete, toDelete->GetRight());
    }
    else if (toDelete->GetRight() == NIL)
    {
        toFix = toDelete->GetLeft();
        Transplant(toDelete, toDelete->GetLeft());
    }
    else
    {
        Node* successor = GetSuccessorOf(toDelete);
        deletedColor = successor->GetColor();
        toFix = successor->GetRight();

        if (successor->GetParent() == NIL)
            toFix->SetParent(successor);
        else
        {
            Transplant(successor, successor->GetRight());
            successor->SetRight(toDelete->GetRight());
            successor->GetRight()->SetParent(successor);
        }

        Transplant(toDelete, successor);
        successor->SetLeft(toDelete->GetLeft());
        successor->GetLeft()->SetParent(successor);
        successor->SetColor(toDelete->GetColor());
    }

    if (deletedColor == BLACK)
        FixDeletion(toFix);

    return true;
}