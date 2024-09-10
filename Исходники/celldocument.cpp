/*!
 * \author Ingemar Axelsson
 */
void CellDocument::mouseClickedOnCell(Cell *clickedCell)
{

    // 2006-04-25, AF
    if( lastClickedCell_ == clickedCell )
        return;
    else
        lastClickedCell_ = clickedCell;


    //Deselect all selection
    clearSelection();

    //Remove focus from old cell.
    if(getCursor()->currentCell()->isClosed())
    {
        getCursor()->currentCell()->child()->setReadOnly(true);
        getCursor()->currentCell()->child()->setFocus(false);
    }
    else
    {
        getCursor()->currentCell()->setReadOnly(true);
    }

    //Add focus to the cell clicked on.
    if(clickedCell->parentCell()->isClosed())
    {
        getCursor()->moveAfter(clickedCell->parentCell());
    }
    else
    {
        getCursor()->moveAfter(clickedCell); //Results in bus error why?
    }

    if( typeid(LatexCell) == typeid(*clickedCell))
    {
        LatexCell *latexcell = dynamic_cast<LatexCell*>(clickedCell);
        bool r =latexcell->isEvaluated();
        if(r==true)
        {
            latexcell->input_->setReadOnly(true);
            latexcell->setFocus(true);
        }
        else
        {
            latexcell->input_->setReadOnly(false);
        }
    }
    else
    {
        clickedCell->setReadOnly(false);
        clickedCell->setFocus(true);
    }
    emit cursorChanged();

}