 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "KoPathSegment.h"
#include "KoPathPoint.h"
#include <FlakeDebug.h>
#include <QPainterPath>
#include <QTransform>
#include <math.h>

/// Maximal recursion depth for finding root params
const int MaxRecursionDepth = 64;
/// Flatness tolerance for finding root params
const qreal FlatnessTolerance = ldexp(1.0,-MaxRecursionDepth-1);

class BezierSegment
{
public:
    BezierSegment(int degree = 0, QPointF *p = 0)
    {
        if (degree) {
            for (int i = 0; i <= degree; ++i)
                points.append(p[i]);
        }
    }

    void setDegree(int degree)
    {
        points.clear();