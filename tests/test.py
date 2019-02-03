# import os
import math
import subprocess
from colorama import init, Fore

init(autoreset=True)

cmds = {'echo "X=20 Y=100" | ./calc "(X + 10) * lg(Y)"': round((20 + 10) * math.log10(100), 4),
        'echo "x=5" | ./calc "sin(x) - cos(x)"': round((math.sin(5) - math.cos(5)), 4),
        'echo "" | ./calc "44 * 2 % 3 - ln( 5 )"': round(44 * 2 % 3 - math.log(5), 4),
        'echo "Z=33" | ./calc "abs(sin(Z)) + cos(Z)"': round(math.fabs(math.sin(33)) + math.cos(33), 4),
        'echo "X=0.3 y=4 Z=5" | ./calc "y-16*asin(X)-acos(X)*y"': round(4 - 16 * math.asin(0.3) - math.acos(0.3)*4, 4),
        'echo "var=3" | ./calc " 5 * var ^ var / 4"': round(5 * math.pow(3, 3) / 4, 4),
        'echo "x1=3 x2=22" | ./calc "x1 % lg(x2) +-4 "': round(3 % math.log10(22) - 4, 4),
        'echo "X=4" | ./calc "tan(X) / 20"': round(math.tan(4) / 20, 4),
        'echo "R=156" | ./calc "R^2 - atan(R)"': round(math.pow(156, 2) - math.atan(156), 4),
        'echo "X=3.567 Y=0.5" | ./calc "X^Y * Y^X * (X - Y)"':
            round(math.pow(3.567, 0.5) * math.pow(0.5, 3.567) * (3.567 - 0.5), 4)}

# stdout = os.popen(cmd, 'r', 1)
# result = stdout.read()
# print('the result is: ' + result)
# with subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE) as proc:
# print(proc.stout.read())

total = 0
errors = 0

for cmd, res in cmds.items():
    proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    out = proc.stdout.readline()
    print(cmd)
    total += 1
    if round(float(out), 4) == res:
        print('OK: ' + str(res))
    else:
        print(Fore.RED + 'ERROR', 'c++calc: ' + str(float(out)) + ' pymath: ' + str(res))
        errors += 1
    print('\n')

print(Fore.GREEN + 'Done with ' + str(errors) + ' errors from ' + str(total))
