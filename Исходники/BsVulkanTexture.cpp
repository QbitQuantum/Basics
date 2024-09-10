	void VulkanTexture::unlockImpl()
	{
		// Possibly map() failed with some error
		if (!mIsMapped)
			return;

		// Note: If we did any writes they need to be made visible to the GPU. However there is no need to execute 
		// a pipeline barrier because (as per spec) host writes are implicitly visible to the device.

		if (mStagingBuffer == nullptr)
			mImages[mMappedDeviceIdx]->unmap();
		else
		{
			mStagingBuffer->unmap();

			bool isWrite = mMappedLockOptions != GBL_READ_ONLY;

			// If the caller wrote anything to the staging buffer, we need to upload it back to the main buffer
			if (isWrite)
			{
				VulkanRenderAPI& rapi = static_cast<VulkanRenderAPI&>(RenderAPI::instance());
				VulkanDevice& device = *rapi._getDevice(mMappedDeviceIdx);

				VulkanCommandBufferManager& cbManager = gVulkanCBManager();
				GpuQueueType queueType;
				UINT32 localQueueIdx = CommandSyncMask::getQueueIdxAndType(mMappedGlobalQueueIdx, queueType);

				VulkanImage* image = mImages[mMappedDeviceIdx];
				VulkanTransferBuffer* transferCB = cbManager.getTransferBuffer(mMappedDeviceIdx, queueType, localQueueIdx);

				VulkanImageSubresource* subresource = image->getSubresource(mMappedFace, mMappedMip);
				VkImageLayout curLayout = subresource->getLayout();

				// If the subresource is used in any way on the GPU, we need to wait for that use to finish before
				// we issue our copy
				UINT32 useMask = subresource->getUseInfo(VulkanUseFlag::Read | VulkanUseFlag::Write);
				bool isNormalWrite = false;
				if (useMask != 0) // Subresource is currently used on the GPU
				{
					// Try to avoid the wait by checking for special write conditions

					// Caller guarantees he won't touch the same data as the GPU, so just copy
					if (mMappedLockOptions == GBL_WRITE_ONLY_NO_OVERWRITE)
					{
						// Fall through to copy()
					}
					// Caller doesn't care about buffer contents, so just discard the existing buffer and create a new one
					else if (mMappedLockOptions == GBL_WRITE_ONLY_DISCARD)
					{
						// We need to discard the entire image, even though we're only writing to a single sub-resource
						image->destroy();

						image = createImage(device, mInternalFormats[mMappedDeviceIdx]);
						mImages[mMappedDeviceIdx] = image;

						subresource = image->getSubresource(mMappedFace, mMappedMip);
					}
					else // Otherwise we have no choice but to issue a dependency between the queues
					{
						transferCB->appendMask(useMask);
						isNormalWrite = true;
					}
				}
				else
					isNormalWrite = true;

				const TextureProperties& props = getProperties();

				// Check if the subresource will still be bound somewhere after the CBs using it finish
				if (isNormalWrite)
				{
					UINT32 useCount = subresource->getUseCount();
					UINT32 boundCount = subresource->getBoundCount();

					bool isBoundWithoutUse = boundCount > useCount;

					// If image is queued for some operation on a CB, then we need to make a copy of the subresource to
					// avoid modifying its use in the previous operation
					if (isBoundWithoutUse)
					{
						VulkanImage* newImage = createImage(device, mInternalFormats[mMappedDeviceIdx]);

						// Avoid copying original contents if the image only has one sub-resource, which we'll overwrite anyway
						if (props.getNumMipmaps() > 0 || props.getNumFaces() > 1)
						{
							VkImageLayout oldImgLayout = image->getOptimalLayout();

							curLayout = newImage->getOptimalLayout();
							copyImage(transferCB, image, newImage, oldImgLayout, curLayout);
						}

						image->destroy();
						image = newImage;
						mImages[mMappedDeviceIdx] = image;
					}
				}

				VkImageSubresourceRange range;
				range.aspectMask = image->getAspectFlags();
				range.baseArrayLayer = mMappedFace;
				range.layerCount = 1;
				range.baseMipLevel = mMappedMip;
				range.levelCount = 1;

				VkImageSubresourceLayers rangeLayers;
				rangeLayers.aspectMask = range.aspectMask;
				rangeLayers.baseArrayLayer = range.baseArrayLayer;
				rangeLayers.layerCount = range.layerCount;
				rangeLayers.mipLevel = range.baseMipLevel;

				VkExtent3D extent;
				PixelUtil::getSizeForMipLevel(props.getWidth(), props.getHeight(), props.getDepth(), mMappedMip,
											  extent.width, extent.height, extent.depth);

				VkImageLayout transferLayout;
				if (mDirectlyMappable)
					transferLayout = VK_IMAGE_LAYOUT_GENERAL;
				else
					transferLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

				// Transfer texture to a valid layout
				VkAccessFlags currentAccessMask = image->getAccessFlags(curLayout);
				transferCB->setLayout(image->getHandle(), currentAccessMask, VK_ACCESS_TRANSFER_WRITE_BIT,
									  curLayout, transferLayout, range);

				// Queue copy command
				mStagingBuffer->copy(transferCB->getCB(), image, extent, rangeLayers, transferLayout);

				// Transfer back to original  (or optimal if initial layout was undefined/preinitialized)
				VkImageLayout dstLayout = image->getOptimalLayout();

				currentAccessMask = image->getAccessFlags(dstLayout);
				transferCB->setLayout(image->getHandle(), VK_ACCESS_TRANSFER_WRITE_BIT, currentAccessMask,
									  transferLayout, dstLayout, range);

				// Notify the command buffer that these resources are being used on it
				transferCB->getCB()->registerResource(mStagingBuffer, VK_ACCESS_TRANSFER_READ_BIT, VulkanUseFlag::Read);
				transferCB->getCB()->registerResource(image, range, VulkanUseFlag::Write, ResourceUsage::Transfer);

				// We don't actually flush the transfer buffer here since it's an expensive operation, but it's instead
				// done automatically before next "normal" command buffer submission.
			}

			mStagingBuffer->destroy();
			mStagingBuffer = nullptr;
		}

		mIsMapped = false;
	}