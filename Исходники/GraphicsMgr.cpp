//==============================================================================
void Mtx44::BuildRotateZ (float rot, Mtx44 * output) {
    ASSERT(output);
    XMMATRIX result = XMMatrixRotationZ(rot);
    memcpy(output->m, result.m, sizeof(output->m));
}