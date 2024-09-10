	VkResult wait_for_event(VkEvent event, u64 timeout)
	{
		u64 t = 0;
		while (true)
		{
			switch (const auto status = vkGetEventStatus(*g_current_renderer, event))
			{
			case VK_EVENT_SET:
				return VK_SUCCESS;
			case VK_EVENT_RESET:
				break;
			default:
				die_with_error(HERE, status);
				return status;
			}

			if (timeout)
			{
				if (!t)
				{
					t = get_system_time();
					continue;
				}

				if ((get_system_time() - t) > timeout)
				{
					LOG_ERROR(RSX, "[vulkan] vk::wait_for_event has timed out!");
					return VK_TIMEOUT;
				}
			}

			//std::this_thread::yield();
			_mm_pause();
		}
	}