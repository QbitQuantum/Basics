XMMATRIX GetMatrix(json::array_t accessor)
{
    return XMMatrixSet(accessor[0],  accessor[1],  accessor[2],  accessor[3],
                       accessor[4],  accessor[5],  accessor[6],  accessor[7],
                       accessor[8],  accessor[9],  accessor[10], accessor[11],
                       accessor[12], accessor[13], accessor[14], accessor[15]);
}