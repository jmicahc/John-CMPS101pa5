#! /usr/bin/env python
#------------------------------------------------------------------------------
#  RandomInput5.py
#  Creates random input file for cmps 101 pa5. To run this program on Linux: 
#
#         python3 RandomInput5.py
#
#------------------------------------------------------------------------------

import sys
import random

# cat()
# returns the concatenation of a list of lists
def cat(L):
   s = []
   for x in L: s += x
   return s

# get user input and initialize local variables
filename = raw_input("Enter name of file to create: ")
n = int(raw_input("Enter number of vertices n (must be positive): "))
if n<=0:
   print "Invalid input n" + str(n) + ".  Value must be positive."
   sys.exit(1)
k = int(raw_input("Enter number of strong components k (1<=k<="+str(n)+"): "))
if k<1 or k>n:
   print "Invalid input k=" + str(k) + \
         ". Value must be in range 1 to " + str(n) + "."
   sys.exit(1)
B = [1]+sorted(random.sample(range(2,n+1),k-1))+[n+1]
C = [ range(B[i], B[i+1]) for i in range(k) ]
N = [ len(x) for x in C ]
Min = sum( [ j for j in N if j>1 ] ) + (k-1)
Max = sum( [ j*(j-1)/2 for j in N if j>1 ] ) + n*(n+1)/2
m = int(raw_input("Enter number of edges m ("+str(Min)+"<=m<="+str(Max)+"): "))
if m<Min or m>Max:
   print "Invalid input m=" + str(m) + \
         ". Value must be in range "+str(Min)+" to "+str(Max)+"."
   sys.exit(1)

# create random digraph
D = cat( [ [ (v,u) for u in x for v in x if u<v ] for x in C ] )
F = [ (u,v) for u in range(1,n+1) for v in range(1,n+1) if u<=v ]
E = D + F
G  = [ (u,u+1) for u in range(1,n) ]
G += [ (B[i+1]-1,B[i]) for i in range(k) if B[i]+1 != B[i+1] ]
H = list(set(E)-set(G))
I = random.sample(H, Max-m)
J = list(set(E)-set(I))
R = range(1,n+1)
random.shuffle(R)
R = [0] + R
M = [ (R[e[0]],R[e[1]]) for e in J ]
M.sort()

# print digraph to file
f = open(filename, 'w')
f.write(str(n)+'\n')
for e in M:
   f.write( str(e[0])+" "+str(e[1])+"\n" )
f.write("0 0\n")
f.close()
