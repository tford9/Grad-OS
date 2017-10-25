# Author: Trenton W. Ford
# Date: 10/23/2017
# Purpose: Automate simulator calls and record results.

from subprocess import Popen, PIPE, STDOUT

TravAlgs = [1,2];
DatForms = [1,2];
ReplPol= [1,2,3];

CacheSizesKB = [8, 64, 128, 256, 512, 1024]
PageSizesKB = [2,4,8,16,32,64]

output_file = open('output.txt', 'w')

for cs in CacheSizesKB :
    string = "";
    string += str(cs) + '\n';
    for ps in PageSizesKB :
        string1="";
        string1 +=string + str(ps) + '\n';
        for ta in TravAlgs:
            string2 = "";
            string2 +=string1 + str(ta) + '\n';
            for df in DatForms:
                string3 = "";
                string3 = string2 + str(df) + '\n';
                for rp in ReplPol:
                    string4="";
                    string4 +=string3 + str(rp) + '\n' + "./edgelists/g2\n";

                    p = Popen(['./sim', ''], stdout=PIPE, stdin=PIPE, stderr=PIPE) 
                    sim_stdout, sim_stderr = p.communicate(input=bytes(string4, encoding='ascii'))
                    output_file.write(sim_stdout.decode());
                    print(string4);





