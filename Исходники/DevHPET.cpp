/**
 * 32-bit write to a HPET timer register.
 *
 * @returns Strict VBox status code.
 *
 * @param   pThis           The HPET state.
 * @param   idxReg          The register being written to.
 * @param   u32NewValue     The value being written.
 *
 * @remarks The caller should not hold the device lock, unless it also holds
 *          the TM lock.
 */
static int hpetTimerRegWrite32(HPET *pThis, uint32_t iTimerNo, uint32_t iTimerReg, uint32_t u32NewValue)
{
    Assert(!PDMCritSectIsOwner(&pThis->CritSect) || TMTimerIsLockOwner(pThis->aTimers[0].CTX_SUFF(pTimer)));

    if (   iTimerNo >= HPET_CAP_GET_TIMERS(pThis->u32Capabilities)
        || iTimerNo >= RT_ELEMENTS(pThis->aTimers) )    /* Parfait - see above. */
    {
        static unsigned s_cOccurences = 0;
        if (s_cOccurences++ < 10)
            LogRel(("HPET: using timer above configured range: %d\n", iTimerNo));
        return VINF_SUCCESS;
    }
    HPETTIMER *pHpetTimer = &pThis->aTimers[iTimerNo];

    switch (iTimerReg)
    {
        case HPET_TN_CFG:
        {
            DEVHPET_LOCK_RETURN(pThis, VINF_IOM_R3_MMIO_WRITE);
            uint64_t    u64Mask = HPET_TN_CFG_WRITE_MASK;

            Log(("write HPET_TN_CFG: %d: %x\n", iTimerNo, u32NewValue));
            if (pHpetTimer->u64Config & HPET_TN_PERIODIC_CAP)
                u64Mask |= HPET_TN_PERIODIC;

            if (pHpetTimer->u64Config & HPET_TN_SIZE_CAP)
                u64Mask |= HPET_TN_32BIT;
            else
                u32NewValue &= ~HPET_TN_32BIT;

            if (u32NewValue & HPET_TN_32BIT)
            {
                Log(("setting timer %d to 32-bit mode\n", iTimerNo));
                pHpetTimer->u64Cmp    = (uint32_t)pHpetTimer->u64Cmp;
                pHpetTimer->u64Period = (uint32_t)pHpetTimer->u64Period;
            }
            if ((u32NewValue & HPET_TN_INT_TYPE) == HPET_TIMER_TYPE_LEVEL)
            {
                static unsigned s_cOccurences = 0;
                if (s_cOccurences++ < 10)
                    LogRel(("level-triggered config not yet supported\n"));
                AssertFailed();
            }

            /* We only care about lower 32-bits so far */
            pHpetTimer->u64Config = hpetUpdateMasked(u32NewValue, pHpetTimer->u64Config, u64Mask);
            DEVHPET_UNLOCK(pThis);
            break;
        }

        case HPET_TN_CFG + 4: /* Interrupt capabilities - read only. */
        {
            Log(("write HPET_TN_CFG + 4, useless\n"));
            break;
        }

        case HPET_TN_CMP: /* lower bits of comparator register */
        {
            DEVHPET_LOCK_BOTH_RETURN(pThis, VINF_IOM_R3_MMIO_WRITE);
            Log(("write HPET_TN_CMP on %d: %#x\n", iTimerNo, u32NewValue));

            if (pHpetTimer->u64Config & HPET_TN_PERIODIC)
                pHpetTimer->u64Period = RT_MAKE_U64(u32NewValue, RT_HI_U32(pHpetTimer->u64Period));
            pHpetTimer->u64Cmp     = RT_MAKE_U64(u32NewValue, RT_HI_U32(pHpetTimer->u64Cmp));
            pHpetTimer->u64Config &= ~HPET_TN_SETVAL;
            Log2(("after HPET_TN_CMP cmp=%#llx per=%#llx\n", pHpetTimer->u64Cmp, pHpetTimer->u64Period));

            if (pThis->u64HpetConfig & HPET_CFG_ENABLE)
                hpetProgramTimer(pHpetTimer);
            DEVHPET_UNLOCK_BOTH(pThis);
            break;
        }

        case HPET_TN_CMP + 4: /* upper bits of comparator register */
        {
            DEVHPET_LOCK_BOTH_RETURN(pThis, VINF_IOM_R3_MMIO_WRITE);
            Log(("write HPET_TN_CMP + 4 on %d: %#x\n", iTimerNo, u32NewValue));
            if (!hpet32bitTimer(pHpetTimer))
            {
                if (pHpetTimer->u64Config & HPET_TN_PERIODIC)
                    pHpetTimer->u64Period = RT_MAKE_U64(RT_LO_U32(pHpetTimer->u64Period), u32NewValue);
                pHpetTimer->u64Cmp = RT_MAKE_U64(RT_LO_U32(pHpetTimer->u64Cmp), u32NewValue);

                Log2(("after HPET_TN_CMP+4 cmp=%llx per=%llx tmr=%d\n", pHpetTimer->u64Cmp, pHpetTimer->u64Period, iTimerNo));

                pHpetTimer->u64Config &= ~HPET_TN_SETVAL;

                if (pThis->u64HpetConfig & HPET_CFG_ENABLE)
                    hpetProgramTimer(pHpetTimer);
            }
            DEVHPET_UNLOCK_BOTH(pThis);
            break;
        }

        case HPET_TN_ROUTE:
        {
            Log(("write HPET_TN_ROUTE\n"));
            break;
        }

        case HPET_TN_ROUTE + 4:
        {
            Log(("write HPET_TN_ROUTE + 4\n"));
            break;
        }

        default:
        {
            static unsigned s_cOccurences = 0;
            if (s_cOccurences++ < 10)
                LogRel(("invalid timer register write: %d\n", iTimerReg));
            break;
        }
    }

    return VINF_SUCCESS;
}