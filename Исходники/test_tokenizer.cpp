 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include "tokenizer.hpp"
#include <sstream>
#include "catch.hpp"

TEST_CASE( "Parsing Tokens", "[Tokenizer::parse]" ) {
	Tokenizer tok;
	std::stringstream test;
	test <<
		"test_project {" << std::endl <<
		"test=1," << std::endl <<
		"	 meep = 39" << std::endl <<
		"}" << std::endl;

	tok = Tokenizer(test);
	CHECK(tok.next() == "test_project");
	Token token = tok.getToken();
	CHECK_FALSE(token.getType() == ERROR);
	CHECK(token.getType() == PROJECT);
	CHECK(token.getValue() == "test_project");
}
