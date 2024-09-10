// Actualiza y aplica al display el factor de zoom segun el tamaño del display 
// pero con limite el tamaño de la imagen
// Devuelve el zoom o ratio aplicado
double ControlImagenes::ActualizaZoom(CButton& m_control_group, CStatic&	m_control)
{
    // Ancho y alto maximo posible
    RECT Rect;
    m_control_group.GetClientRect(&Rect);
    long anchoDisplay = abs(Rect.right);
    long altoDisplay = abs(Rect.bottom);

    // calcula el zoom optimo (maximo) dentro de lo posible
    // el resultado esta en m_factorZoom
    CalculaZoom(anchoDisplay,altoDisplay,
        m_nAnchoImagen,m_nAltoImagen);

    //Ajustar la ventana de display al zoom calculado
    long alto,ancho;
    if (m_factorZoom < 0)
    {
        ancho = (long)floor(m_nAnchoImagen * -1.0/m_factorZoom + 0.5);
        alto = (long)floor(m_nAltoImagen * -1.0/m_factorZoom + 0.5);
    }
    else 
    {
        ancho = (long)floor(m_nAnchoImagen * m_factorZoom + 0.5);
        alto = (long)floor(m_nAltoImagen * m_factorZoom + 0.5);
    }

    m_control.SetWindowPos(NULL,0,0,ancho,alto,SWP_NOMOVE | SWP_NOZORDER);

    MdispZoom(m_Mildisplay, m_factorZoom, m_factorZoom);

    return m_factorZoom;
}