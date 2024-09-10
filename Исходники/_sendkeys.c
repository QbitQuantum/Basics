char2keycode(char) -> int \n\
\n\
Converts character to virtual key code \n\
";
static PyObject*
char2keycode(PyObject* self, PyObject* args)
{
char c = 0;
int vk = 0;
if(!PyArg_ParseTuple(args, "c", &c))
return NULL;
vk = VkKeyScanA(c);
return Py_BuildValue("i", vk);
}