void BRDFMaterial::bindDrawIndexedRecursive(const ICommandBuffersSP& cmdBuffer, const IGraphicsPipelineSP& graphicsPipeline, const uint32_t bufferIndex) const
{
    bindDescriptorSets(cmdBuffer, graphicsPipeline->getLayout(), bufferIndex);
}