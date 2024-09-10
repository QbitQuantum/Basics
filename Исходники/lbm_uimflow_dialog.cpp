void LBMUIMFlowDialog::fillDiagram(void)
{
    QCustomPlot * sp = m_ui->sequencePlot;
    seq_analysis_info_t new_sa;

    new_sa = m_sequence_analysis;
    new_sa.items = g_queue_new();
    new_sa.ht = NULL;
    new_sa.num_nodes = 0;
    lbm_uimflow_get_analysis(m_capture_file, &new_sa);
    m_num_items = sequence_analysis_get_nodes(&new_sa);
    m_sequence_diagram->setData(&new_sa);
    sequence_analysis_list_free(&m_sequence_analysis);
    m_sequence_analysis = new_sa;

    QFontMetrics vfm = QFontMetrics(sp->xAxis2->labelFont());
    m_node_label_width = 0;
    for (guint i = 0; i < m_sequence_analysis.num_nodes; i++)
    {
        QString addr_str = address_to_display_qstring(&(m_sequence_analysis.nodes[i]));
        int label_w = vfm.width(addr_str);
        if (m_node_label_width < label_w)
        {
            m_node_label_width = label_w;
        }
    }
    m_node_label_width = (m_node_label_width * 3 / 4) + m_one_em;

    mouseMoved(NULL);
    resetAxes();

    // XXX QCustomPlot doesn't seem to draw any sort of focus indicator.
    sp->setFocus();
}