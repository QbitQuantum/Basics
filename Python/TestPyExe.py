import subprocess
import sys
print("Hello, World!")
result = subprocess.run(['ipconfig'], stdout=subprocess.PIPE, shell=True)
print ('---------------------------------------------------------------')
print(result.stdout.decode('cp866'))  # декодируем байты в строку
result = subprocess.run(['pause'], stdout=subprocess.PIPE, shell=True)
ress = exec()