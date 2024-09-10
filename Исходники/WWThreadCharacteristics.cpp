void
WWThreadCharacteristics::Setup(void)
{
    HRESULT hr = S_OK;

    if (WWSTTNone != m_schedulerTaskType) {
        // マルチメディアクラススケジューラーサービスのスレッド特性設定。
        dprintf("D: %s() AvSetMmThreadCharacteristics(%S)\n",
                __FUNCTION__, WWSchedulerTaskTypeToStr(m_schedulerTaskType));

        m_mmcssHandle =
                AvSetMmThreadCharacteristics(WWSchedulerTaskTypeToStr(m_schedulerTaskType), &m_mmcssTaskIndex);
        if (nullptr == m_mmcssHandle) {
            dprintf("Failed to enable MMCSS on render thread: 0x%08x\n", GetLastError());
            m_mmcssTaskIndex = 0;
            m_result.avSetMmThreadCharacteristicsResult = false;
        } else {
            m_result.avSetMmThreadCharacteristicsResult = true;
        }

        if (m_result.avSetMmThreadCharacteristicsResult && WWTPNone != m_threadPriority) {
            // スレッド優先度設定。
            dprintf("D: %s() AvSetMmThreadPriority(%S)\n",
                    __FUNCTION__, WWMMThreadPriorityTypeToStr(m_threadPriority));

            assert(m_mmcssHandle != nullptr);

            m_result.avSetMmThreadPriorityResult =
                    !!AvSetMmThreadPriority(m_mmcssHandle, WWMMThreadPriorityTypeToAvrtPriority(m_threadPriority));
        }
    }

    if (WWMMCSSDoNotCall != m_mmcssCallType) {
        // MMCSSの有効、無効の設定。
        hr = DwmEnableMMCSS(m_mmcssCallType==WWMMCSSEnable);
        dprintf("D: %s() DwmEnableMMCSS(%d) 0x%08x\n", __FUNCTION__, (int)(m_mmcssCallType==WWMMCSSEnable), hr);
        // 失敗することがあるが、続行する。
        m_result.dwmEnableMMCSSResult = hr;
    }

}