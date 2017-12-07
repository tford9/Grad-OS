# Author: Trenton W. Ford
# Date: 10/23/2017
# Purpose: Automate simulator calls and record results.
import numpy as np
from subprocess import Popen, PIPE, STDOUT
from sys import argv, exit  

TravAlgs = [2];
DatForms = [1];
ReplPol= [4];

CacheSizesKB = np.arange(8,13,1);

print(CacheSizesKB)

if len(argv) < 2:
    print('Specify graph name (g1 / g2 .. / g10) as argument. Exiting!')
    exit(0) 

output_file = open('output_{}.txt'.format(argv[1]), 'w')

for i in range(10):
    for cs in CacheSizesKB :
        string = "";
        string += str(2**cs) + '\n';
        PageSizesKB = np.arange(2,cs-1);
        PageSizesKB = [5];
        for ps in PageSizesKB:
            string1="";
            string1 +=string + str(2**ps) + '\n';
            for ta in TravAlgs:
                string2 = "";
                string2 +=string1 + str(ta) + '\n';
                for df in DatForms:
                    string3 = "";
                    string3 = string2 + str(df) + '\n';
                    for rp in ReplPol:
                        string4="";
                        string4 +=string3 + str(rp) + '\n' + "./edgelists/{}\n".format(argv[1]);

                        p = Popen(['./sim', ''], stdout=PIPE, stdin=PIPE, stderr=PIPE) 
                        sim_stdout, sim_stderr = p.communicate(input=bytearray(string4))
                        output_file.write(sim_stdout.decode());
                        print(string4);
output_file.close();
