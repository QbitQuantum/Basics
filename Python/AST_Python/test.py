import ast
import astunparse
import re
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
with open(file_path, 'r', encoding='utf-8') as file:
    file_contents = file.read()
tree = ast.parse(file_contents)

change_variable_value(tree, 'a', 0)

modified_code = astunparse.unparse(tree)
with open(file_path, 'w') as file:
    file.write(modified_code)