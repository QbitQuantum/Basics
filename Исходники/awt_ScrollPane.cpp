void AwtScrollPane::RecalcSizes(int parentWidth, int parentHeight,
                                int childWidth, int childHeight)
{
    JNIEnv *env = (JNIEnv *)JNU_GetEnv(jvm, JNI_VERSION_1_2);
    if (env->EnsureLocalCapacity(2) < 0) {
        return;
    }

    /* Determine border width without scrollbars. */
    int horzBorder;
    int vertBorder;
    if (IS_WIN4X) {
        horzBorder = ::GetSystemMetrics(SM_CXEDGE);
        vertBorder = ::GetSystemMetrics(SM_CYEDGE);
    } else {
        horzBorder = ::GetSystemMetrics(SM_CXBORDER);
        vertBorder = ::GetSystemMetrics(SM_CYBORDER);
    }

    parentWidth -= (horzBorder * 2);
    parentHeight -= (vertBorder * 2);

    /* Enable each scrollbar as needed. */
    jobject target = AwtObject::GetTarget(env);
    jint policy = env->GetIntField(target,
                                   AwtScrollPane::scrollbarDisplayPolicyID);

    BOOL needsHorz=(policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS ||
                    (policy == java_awt_ScrollPane_SCROLLBARS_AS_NEEDED &&
                     childWidth > parentWidth));
    if (needsHorz) {
        parentHeight -= ::GetSystemMetrics(SM_CYHSCROLL);
    }
    BOOL needsVert=(policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS ||
                    (policy ==java_awt_ScrollPane_SCROLLBARS_AS_NEEDED &&
                     childHeight > parentHeight));
    if (needsVert) {
        parentWidth -= ::GetSystemMetrics(SM_CXVSCROLL);
    }
    /*
     * Since the vertical scrollbar may have reduced the parent width
     * enough to now require a horizontal scrollbar, we need to
     * recalculate the horizontal metrics and scrollbar boolean.
     */
    if (!needsHorz) {
        needsHorz = (policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS ||
                     (policy == java_awt_ScrollPane_SCROLLBARS_AS_NEEDED &&
                      childWidth > parentWidth));
        if (needsHorz) {
            parentHeight -= ::GetSystemMetrics(SM_CYHSCROLL);
        }
    }

    /* Now set ranges -- setting the min and max the same disables them. */
    if (needsHorz) {
        jobject hAdj =
            env->GetObjectField(target, AwtScrollPane::hAdjustableID);
        env->SetIntField(hAdj, AwtScrollPane::blockIncrementID, parentWidth);
        SetScrollInfo(SB_HORZ, childWidth - 1, parentWidth,
                      (policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS));
        env->DeleteLocalRef(hAdj);
    } else {
        SetScrollInfo(SB_HORZ, 0, 0,
                      (policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS));
    }

    if (needsVert) {
        jobject vAdj =
            env->GetObjectField(target, AwtScrollPane::vAdjustableID);
        env->SetIntField(vAdj, AwtScrollPane::blockIncrementID, parentHeight);
        SetScrollInfo(SB_VERT, childHeight - 1, parentHeight,
                      (policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS));
        env->DeleteLocalRef(vAdj);
    } else {
        SetScrollInfo(SB_VERT, 0, 0,
                      (policy == java_awt_ScrollPane_SCROLLBARS_ALWAYS));
    }

    env->DeleteLocalRef(target);
}