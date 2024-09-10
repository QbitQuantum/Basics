s32 sys_event_queue_receive(PPUThread& ppu, u32 equeue_id, vm::ptr<sys_event_t> dummy_event, u64 timeout)
{
    sys_event.trace("sys_event_queue_receive(equeue_id=0x%x, *0x%x, timeout=0x%llx)", equeue_id, dummy_event, timeout);

    const u64 start_time = get_system_time();

    LV2_LOCK;

    const auto queue = idm::get<lv2_event_queue_t>(equeue_id);

    if (!queue)
    {
        return CELL_ESRCH;
    }

    if (queue->type != SYS_PPU_QUEUE)
    {
        return CELL_EINVAL;
    }

    if (queue->events.size())
    {
        // event data is returned in registers (dummy_event is not used)
        std::tie(ppu.GPR[4], ppu.GPR[5], ppu.GPR[6], ppu.GPR[7]) = queue->events.front();

        queue->events.pop_front();

        return CELL_OK;
    }

    // cause (if cancelled) will be returned in r3
    ppu.GPR[3] = 0;

    // add waiter; protocol is ignored in current implementation
    sleep_queue_entry_t waiter(ppu, queue->sq);

    while (!ppu.unsignal())
    {
        CHECK_EMU_STATUS;

        if (timeout)
        {
            const u64 passed = get_system_time() - start_time;

            if (passed >= timeout)
            {
                return CELL_ETIMEDOUT;
            }

            ppu.cv.wait_for(lv2_lock, std::chrono::microseconds(timeout - passed));
        }
        else
        {
            ppu.cv.wait(lv2_lock);
        }
    }

    if (ppu.GPR[3])
    {
        if (idm::check<lv2_event_queue_t>(equeue_id))
        {
            throw EXCEPTION("Unexpected");
        }

        return CELL_ECANCELED;
    }

    // r4-r7 registers must be set by push()
    return CELL_OK;
}