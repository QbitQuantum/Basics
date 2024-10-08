 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef OS_WINDOWS_VM_INTERFACESUPPORT_WINDOWS_HPP
#define OS_WINDOWS_VM_INTERFACESUPPORT_WINDOWS_HPP

// Contains inlined functions for class InterfaceSupport

static inline void serialize_memory(JavaThread *thread) {
  // due to chained nature of SEH handlers we have to be sure
  // that our handler is always last handler before an attempt to write
  // into serialization page - it can fault if we access this page
  // right in the middle of protect/unprotect sequence by remote
  // membar logic.
  // __try/__except are very lightweight operations (only several
  // instructions not affecting control flow directly on x86)
  // so we can use it here, on very time critical path
  __try {
    os::write_memory_serialize_page(thread);
  } __except (os::win32::
              serialize_fault_filter((_EXCEPTION_POINTERS*)_exception_info()))
    {}
}

#endif // OS_WINDOWS_VM_INTERFACESUPPORT_WINDOWS_HPP
