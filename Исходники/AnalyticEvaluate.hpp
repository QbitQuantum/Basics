/*! \brief Analytic evaluation of ionic liquid Green's function and its derivatives
 *
 *  \f[
 *  \begin{align}
 *  \phantom{G(\vect{r},\vect{r}^\prime)}
 *  &\begin{aligned}
 *    G(\vect{r},\vect{r}^\prime) = \frac{\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|}
 *  \end{aligned}\\
 *  &\begin{aligned}
 *    \pderiv{}{{\vect{n}_{\vect{r}^\prime}}}G(\vect{r},\vect{r}^\prime) =
 *    \frac{(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}^\prime}\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^3}
 *    +\kappa\frac{(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}^\prime}\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^2}
 *   \end{aligned}\\
 *   &\begin{aligned}
 *     \pderiv{}{{\vect{n}_{\vect{r}}}}G(\vect{r},\vect{r}^\prime) =
 *     -\frac{(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}}\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^3}
 *     -\kappa\frac{(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}}\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^2}
 *    \end{aligned}\\
 *   &\begin{aligned}
 *     \frac{\partial^2}{\partial{\vect{n}_{\vect{r}}}\partial{\vect{n}_{\vect{r}^\prime}}}G(\vect{r},\vect{r}^\prime) &=
 *     \frac{\vect{n}_{\vect{r}}\cdot \vect{n}_{\vect{r}^\prime}\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^3}
 *     -\kappa\frac{[(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}}][(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}^\prime}]\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^4}\\
 *     &-3\frac{[(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}}][(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}^\prime}]\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^5}
 *     + \kappa\frac{\vect{n}_{\vect{r}}\cdot \vect{n}_{\vect{r}^\prime}\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^2} \\
 *     &-\kappa^2\frac{[(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}}][(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}^\prime}]\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^3}\\
 *     &-2\kappa\frac{[(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}}][(\vect{r}-\vect{r}^\prime)\cdot \vect{n}_{\vect{r}^\prime}]\mathrm{e}^{-\kappa|\vect{r}-\vect{r}^\prime|}}{4\pi\diel|\vect{r}-\vect{r}^\prime|^4}
 *    \end{aligned}
 *  \end{align}
 *  \f]
 */
inline Eigen::Array4d analyticIonicLiquid(double eps, double k,
        const Eigen::Vector3d & spNormal,
        const Eigen::Vector3d & sp,
        const Eigen::Vector3d & ppNormal, const Eigen::Vector3d & pp) {
    Eigen::Array4d result = Eigen::Array4d::Zero();
    double distance = (sp - pp).norm();
    double distance_3 = std::pow(distance, 3);
    double distance_5 = std::pow(distance, 5);

    // Value of the function
    result(0) = std::exp(- k * distance) / (eps * distance);
    // Value of the directional derivative wrt probe
    result(1) = (sp - pp).dot(ppNormal) * (1 + k * distance ) * std::exp(
                    - k * distance) / (eps * distance_3);
    // Directional derivative wrt source
    result(2) = - (sp - pp).dot(spNormal) * (1 + k * distance ) * std::exp(
                    - k * distance) / (eps * distance_3);
    // Value of the Hessian
    result(3) = spNormal.dot(ppNormal) * (1 + k * distance) * std::exp(
                    - k * distance) / (eps * distance_3)
                - std::pow(k, 2) * (sp - pp).dot(spNormal) * (sp - pp).dot(
                    ppNormal) * std::exp(- k * distance) / (eps * distance_3)
                - 3 * (sp - pp).dot(spNormal) * (sp - pp).dot(
                    ppNormal) * (1 + k * distance) * std::exp(- k * distance) /
                (eps * distance_5);

    return result;
}