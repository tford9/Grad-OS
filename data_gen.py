# Author: Trenton W. Ford
# Date: 10/23/2017
# Purpose: Automate simulator calls and record results.

from subprocess import Popen, PIPE, STDOUT

TravAlgs = [1,2];
ReplPol= [1,2,3];
DatForms = [1,2];

CacheSizesKB = [8, 64, 128, 256, 512, 1024]
PageSizesKB = [2,4,8,16,32,64]

output_file = open('output.txt', 'w')

for cs in CacheSizesKB :
    string = "";
    string += str(cs) + '\n';
    for ps in PageSizesKB :
        string1="";
        string1 +=string + str(ps) + '\n';
        for rp in ReplPol:
            string2="";
            string2 +=string1 + "1\n" + str(rp) +"\n2\n./edgelists/g1\n"

            p = Popen(['./sim', ''], stdout=PIPE, stdin=PIPE, stderr=PIPE) 
            sim_stdout, sim_stderr = p.communicate(input=bytes(string2, encoding='ascii'))
            output_file.write(sim_stdout.decode());
            # print(string2);





