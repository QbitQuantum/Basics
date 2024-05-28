
import subprocess
import ast
import astunparse
import sys
python_interpreter_path = 'C:\\Program Files\\WindowsApps\\PythonSoftwareFoundation.Python.3.11_3.11.2288.0_x64__qbz5n2kfra8p0\\python.exe'
file_path = 'gener.py'

def change_variable_value(tree, variable_name, new_value):
    for node in ast.walk(tree):
        if isinstance(node, ast.Assign):
            for target in node.targets:
                if (isinstance(target, ast.Name) and (target.id == variable_name)):
                    if isinstance(new_value, str):
                        new_value = ast.Str(new_value)
                    elif isinstance(new_value, int):
                        new_value = ast.Num(new_value)
                    node.value = new_value
a = 0
if (a > 0):
    subprocess.Popen(f'start cmd /k python {file_path}', shell=True)
    with open(file_path, 'r', encoding='utf-8') as file:
        file_contents = file.read()
    tree = ast.parse(file_contents)
    change_variable_value(tree, 'a', (a - 1))
    modified_code = astunparse.unparse(tree)
    with open(file_path, 'w') as file:
        file.write(modified_code)
print('[s]')
