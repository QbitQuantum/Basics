//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
DAF::LightsOutSolver::ReduceGameMatrix()
{
    _vbElementaryOperationMatrix = IdentityMatrix();
    _vbReducedGameMatrix = GameMatrix();
    
    const std::size_t kuGameDimension = _uDimension * _uDimension;
    
    std::size_t uNextRow = 0;
    for (std::size_t uColumn = 0; uColumn < kuGameDimension; ++uColumn)
    {
        for (std::size_t uRow = uNextRow; uRow < kuGameDimension; ++uRow)
        {
            const std::size_t kuLinearIndex = ConvertToLinearIndex(kuGameDimension, uRow, uColumn);
            if ( _vbReducedGameMatrix[kuLinearIndex] )
            {
                SwapRows(kuGameDimension, _vbElementaryOperationMatrix, uNextRow, uRow);
                SwapRows(kuGameDimension, _vbReducedGameMatrix, uNextRow, uRow);
                
                for (size_t uClearRow = 0; uClearRow < kuGameDimension; ++uClearRow)
                {
                    if ( uClearRow == uNextRow )
                        continue;
                    
                    const size_t kuClearLinearIndex = ConvertToLinearIndex(kuGameDimension, uClearRow, uColumn);
                    if ( _vbReducedGameMatrix[kuClearLinearIndex] )
                    {
                        AddRowToRow(kuGameDimension, _vbElementaryOperationMatrix, uNextRow, uClearRow);
                        AddRowToRow(kuGameDimension, _vbReducedGameMatrix, uNextRow, uClearRow);
                    }
                }
                
                ++uNextRow;
                
                break;
            }
        }
    }
    
    FindNullSpaceBasis();
}