/*
 *  Function:   K_OS
 *
 *  The program compute the value of formula (47) in J. Chem. Phys. 84(7),3963
 *
 *  %Latex formula
 *  \begin{equation}
 *      K(\alpha_1, alpha_2, \mathbf{A}, \mathbf{B})
 *      = \frac{\sqrt{2}\pi^{\fact{5}{4}}}{\alpha_1 + \alpha_2}
 *        exp\left(-\frac{\alpha_1\alpha_2}{\alpha_1 + \alpha_2}
 *        \mathbf{AB}^2 \right)
 *  \end{equation}
 */
inline double K_OS(const GTO_PARTIAL *gp1,const GTO_PARTIAL *gp2,const COORD *c)
{
    int i = gp1->cid;
    int j = gp2->cid;
    double AB  = DISTANCE(c[i], c[j]);
    double zeta = gp1->alpha + gp2->alpha;

    return M_SQRT2 * PI_1_25 / zeta * exp(-gp1->alpha * gp2->alpha / zeta * AB);
}