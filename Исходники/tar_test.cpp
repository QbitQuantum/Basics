// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <common.cxx>
#include <tar>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

CASE("Reading single entry tar file")
{
  tar::Reader r;
  struct stat st;
  int res = stat("test-single.tar", &st);
  EXPECT(res != -1);
  size_t size = st.st_size;
  int fd = open("test-single.tar", O_RDONLY);
  EXPECT_NOT(fd == -1);
  const uint8_t *mem = (const uint8_t *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
  tar::Tar tar = r.read_uncompressed(mem, size);
  EXPECT(tar.num_elements() == 1);
  auto names = tar.element_names();
  EXPECT(names.size() == 1);
  const auto& elements = tar.elements();
  EXPECT(elements.size() == 1);
  const auto& e = elements.at(0);
  EXPECT_NOT(e.is_dir());
  EXPECT(e.typeflag_is_set());
  EXPECT(e.typeflag() == REGTYPE); // regular file