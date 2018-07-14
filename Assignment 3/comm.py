#!/usr/bin/python

import random, sys
from optparse import OptionParser

class comm:
    def __init__(self, filename, filename2):
        if filename == '-':
           g = open(filename2, 'r')
           self.lines2 = g.readlines()
           g.close()
           self.lines1 = sys.stdin.readlines()
        elif filename2 == '-':
            f = open(filename, 'r')
            self.lines1 = f.readlines()
            f.close()
            self.lines2 = sys.stdin.readlines()
        else:
            f = open(filename, 'r')
            self.lines1 = f.readlines()
            f.close()
            g = open(filename2, 'r')
            self.lines2 = g.readlines()
            g.close()

    def difference_output(self, is_unsorted, col_1_suppressed, col_2_suppressed, col_3_suppressed):
        print_string = ""
        if is_unsorted == "False":
            file_set = 1
            a = 0
            b = 0
            lines1_length = len(self.lines1)
            lines2_length = len(self.lines2)
            while (len(self.lines1) > 0 or len(self.lines2) > 0):#TODO: change and to or
                if(len(self.lines1) <= 0):
                    if(col_1_suppressed == "True" and col_2_suppressed == "False"):
                        for i in range(len(self.lines2)):
                            print_string+= self.lines2[i]# + "\n"
                    elif(col_1_suppressed == "False" and col_2_suppressed == "False"):
                        for i in range(len(self.lines2)):
                            print_string+= "\t"+self.lines2[i]# + "\n"
                    sys.stdout.write(print_string)
                    return
                if(len(self.lines2) <= 0):
                    if(col_1_suppressed == "False"):
                        for i in range(len(self.lines1)):
                            print_string+= self.lines1[i]# + "\n"
                    
                    sys.stdout.write(print_string)
                    return
                if(file_set == 1):
                    for i in range(len(self.lines1)):
                        for j in range(len(self.lines2)):
                           # print "File 1: " +  self.lines1[i]
                           # print "File 2: " + self.lines2[j]
                            if self.lines1[i] == self.lines2[j]:
                                if(col_1_suppressed == "True" and col_2_suppressed == "False" and col_3_suppressed == "False"):
                                    print_string += "\t"+self.lines1[i]#+"\n"
                                elif(col_1_suppressed == "True" and col_2_suppressed == "True" and col_3_suppressed == "False"):
                                    print_string += self.lines1[i]#+"\n"
                                elif(col_1_suppressed == "False" and col_2_suppressed == "True" and col_3_suppressed == "False"):
                                    print_string += "\t"+self.lines1[i]#+"\n"
                                elif(col_1_suppressed == "False" and col_2_suppressed == "False" and col_3_suppressed == "False"):
                                     print_string += "\t\t" + self.lines1[i]#+"\n"
                                self.lines1.remove(self.lines1[i])
                                self.lines2.remove(self.lines2[j])
                                break
                            elif j == len(self.lines2)-1:
                                if(col_1_suppressed == "False"):
                                    print_string += self.lines1[i]#+"\n"
                                self.lines1.remove(self.lines1[i])
                        break
                    lines1_length-=1;
                    if (len(self.lines1) != 0 and len(self.lines2)!=0):
                        #print "1: " + self.lines1[0]
                        #print "2: " + self.lines2[0]
                        if(self.lines1[0] < self.lines2[0]):
                            file_set = 1 
                        else:
                            file_set = 2
                if(file_set == 2):
                    for i in range(len(self.lines2)):
                        for j in range(len(self.lines1)):
                            #print "File 2: " + self.lines2[i]
                            #print "File 1: " + self.lines1[j]
                            if self.lines2[i] == self.lines1[j]:
                                if(col_1_suppressed == "True" and col_2_suppressed == "False" and col_3_suppressed == "False"):
                                    print_string += "\t"+self.lines2[i]#+"\n"
                                elif(col_1_suppressed == "True" and col_2_suppressed == "True" and col_3_suppressed == "False"):
                                    print_string += self.lines2[i]#+"\n"
                                elif(col_1_suppressed == "False" and col_2_suppressed == "True" and col_3_suppressed == "False"):
                                    print_string += "\t"+self.lines2[i]#+"\n"
                                elif(col_1_suppressed == "False" and col_2_suppressed == "False" and col_3_suppressed == "False"):
                                    print_string += "\t\t" + self.lines2[i]#+"\n"
                                self.lines1.remove(self.lines1[j])
                                self.lines2.remove(self.lines2[i])
                                break
                            elif j == len(self.lines1)-1:
                                if(col_1_suppressed == "True" and col_2_suppressed == "False"):
                                    print_string += self.lines2[i]#+"\n"
                                elif(col_1_suppressed == "False" and col_2_suppressed == "False"):
                                    print_string += "\t" +  self.lines2[i]#+"\n"
                                self.lines2.remove(self.lines2[i])
                        break
                    lines2_length-=1;
                    if (len(self.lines1) != 0 and len(self.lines2)!=0):
                        #print "1: " + self.lines1[0]
                        #print "2: " + self.lines2[0]
                        if(self.lines1[0] < self.lines2[0]):
                            file_set = 1
                        else:
                            file_set = 2
            sys.stdout.write(print_string)
            return
        
        else:
            for i in range(len(self.lines1)):
                for j in range(len(self.lines2)):
                    
                    if self.lines1[i] == self.lines2[j]:
                        if(col_1_suppressed == "True" and col_2_suppressed == "False" and col_3_suppressed == "False"):
                            print_string += "\t"+self.lines1[i]#+"\n"
                        elif(col_1_suppressed == "True" and col_2_suppressed == "True" and col_3_suppressed == "False"):
                            print_string += self.lines1[i]#+"\n"
                        elif(col_1_suppressed == "False" and col_2_suppressed == "True" and col_3_suppressed == "False"):
                            print_string += "\t"+self.lines1[i]#+"\n"
                        elif(col_1_suppressed == "False" and col_2_suppressed == "False" and col_3_suppressed == "False"):
                            print_string += "\t\t" + self.lines1[i]#+"\n"
                        self.lines2.remove(self.lines2[j])
                        break

                    elif j == len(self.lines2)-1:
                        if(col_1_suppressed == "False"):
                            print_string += self.lines1[i]#+"\n"
            for i in range(len(self.lines2)):
                if(col_1_suppressed == "False" and col_2_suppressed == "False"):
                    print_string += "\t" + self.lines2[i]
                elif(col_1_suppressed == "True" and col_2_suppressed == "False"):
                    print_string += self.lines2[i]
                else:
                    break
            sys.stdout.write(print_string)
            return
        


def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
usage=usage_msg)
    parser.add_option("-u", "--unsorted",
                      action="store_true", dest="is_unsorted", default="False", help="determines whether function is sorted or unsorted.")
    parser.add_option("-1", "--suppress_col_1", 
                      action="store_true", dest="col_1_suppressed", default="False", help="choose to suppress column 1 in the output.")
    parser.add_option("-2", "--suppress_col_2",
                      action="store_true", dest="col_2_suppressed", default="False", help="choose to suppress column 2 in the output.")
    parser.add_option("-3", "--suppress_col_3", 
                      action="store_true", dest="col_3_suppressed", default="False", help="choose to suppress column 3 in the output.")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        is_unsorted = str(options.is_unsorted)
    except:
        parser.error("invalid value for UNSORTED: {0}".
                     format(options.is_unsorted))
    try:
        col_1_suppressed = str(options.col_1_suppressed)
    except:
        parser.error("invalid value for COL_1_SUPPRESSED: {0}".
                     format(options.col_1_suppressed))
    try:
        col_2_suppressed = str(options.col_2_suppressed)
    except:
        parser.error("invalid value for COL_2_SUPPRESSED: {0}".
                     format(options.col_2_suppressed))
    try:
        col_3_suppressed = str(options.col_3_suppressed)
    except:
        parser.error("invalid value for COL_3_SUPPRESSED: {0}".
                     format(options.col_3_suppressed))

    if len(args) != 2: #TODO: check this
        parser.error("wrong number of operands")
        
    file_1 = args[0]
    file_2 = args[1]
    #TODO: check if '-' is input
    try:
        generator = comm(file_1, file_2)
        generator.difference_output(is_unsorted, col_1_suppressed, col_2_suppressed, col_3_suppressed)
    except IOError(errno, strerror):
        parser.error("I/O error({0}): {1}".
                    format(errno, strerror))

if __name__ == "__main__":
    main()

