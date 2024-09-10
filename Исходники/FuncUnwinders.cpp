UnwindPlanSP
FuncUnwinders::GetEHFrameAugmentedUnwindPlan (Target &target, Thread &thread, int current_offset)
{
    if (m_unwind_plan_eh_frame_augmented_sp.get() || m_tried_unwind_plan_eh_frame_augmented)
        return m_unwind_plan_eh_frame_augmented_sp;

    // Only supported on x86 architectures where we get eh_frame from the compiler that describes
    // the prologue instructions perfectly, and sometimes the epilogue instructions too.
    if (target.GetArchitecture().GetCore() != ArchSpec::eCore_x86_32_i386
        && target.GetArchitecture().GetCore() != ArchSpec::eCore_x86_64_x86_64
        && target.GetArchitecture().GetCore() != ArchSpec::eCore_x86_64_x86_64h)
    {
            m_tried_unwind_plan_eh_frame_augmented = true;
            return m_unwind_plan_eh_frame_augmented_sp;
    }

    std::lock_guard<std::recursive_mutex> guard(m_mutex);
    m_tried_unwind_plan_eh_frame_augmented = true;

    UnwindPlanSP eh_frame_plan = GetEHFrameUnwindPlan (target, current_offset);
    if (!eh_frame_plan)
        return m_unwind_plan_eh_frame_augmented_sp;

    m_unwind_plan_eh_frame_augmented_sp.reset(new UnwindPlan(*eh_frame_plan));

    // Augment the eh_frame instructions with epilogue descriptions if necessary so the
    // UnwindPlan can be used at any instruction in the function.

    UnwindAssemblySP assembly_profiler_sp (GetUnwindAssemblyProfiler(target));
    if (assembly_profiler_sp)
    {
        if (!assembly_profiler_sp->AugmentUnwindPlanFromCallSite (m_range, thread, *m_unwind_plan_eh_frame_augmented_sp))
        {
            m_unwind_plan_eh_frame_augmented_sp.reset();
        }
    }
    else
    {
        m_unwind_plan_eh_frame_augmented_sp.reset();
    }
    return m_unwind_plan_eh_frame_augmented_sp;
}