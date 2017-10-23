# Author: Trenton W. Ford
# Date: 10/23/2017
# Purpose:
import subprocess
from subprocess import Popen, PIPE

p = Popen("", stdin=PIPE,stdout=PIPE)   # set environment, start new shell
p.communicate("./sim")
p.communicate("64")
p.communicate("8")
p.communicate("1")
p.communicate("2")
p.communicate("2")
p.communicate("/edgelists/g6-36692,367662")






