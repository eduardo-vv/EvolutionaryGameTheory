from numpy import linspace, array, dot, matmul
from scipy.integrate import odeint
import matplotlib.pyplot as plt

'''
This program solves the 4-strategy replicator equation,
and it is written in a way to simplify the symmetrization 
of a bimatrix game as described by Hofbauer et al.     

HOFBAUER, J.; SIGMUND, K. Evolutionary game dynamics. Bulletin of the
American Mathematical Society, v. 40, n. 4, p. 479–519, 2003. 
Publisher: American Mathematical Society
'''

#payoff configuration
A, B, C, D  = 1, 0, 0, 1
a, b, c, d  = 0, 1, 1, 0

#initial conditions
X0 = [.1, .25, .45, .2]

title = "Solutions.txt"
try:
    file = open(title, "w")
except:
    print("Error opening the file!")

#basis
e = array([[1,0,0,0],[0,1,0,0], [0,0,1,0], [0,0,0,1]])


'''The payoff matrix, written in terms of A...D and a...d, 
can be set up by hand if necessary, 
depending on the application.'''

M = array([[A+a, A+b, B+a, B+b],
           [C+a, C+b, D+a, D+b],
           [A+c, A+d, B+c, B+d],
           [C+c, C+d, D+c, D+d]])    
        
M = (1/2)*M
print(M)

#definition of the 4 differential equations
def diffeqs(X, t):    
    #dxi/dt = xi(<ei|Ax>-<x|Ax>)
    dx0dt = X[0]*(dot(e[0], matmul(M,X))-dot(X,matmul(M,X)))
    dx1dt = X[1]*(dot(e[1], matmul(M,X))-dot(X,matmul(M,X)))
    dx2dt = X[2]*(dot(e[2], matmul(M,X))-dot(X,matmul(M,X)))
    #because x1 + x2 +x3 +x4 = 1
    dx3dt = -dx0dt-dx1dt-dx2dt

    return [dx0dt, dx1dt, dx2dt, dx3dt]


#solving the differential equations
t = linspace(0, 150, 1500)
S = odeint(diffeqs, X0, t)                                           

#extracting the solutions
x1 = S[:,0]
x2 = S[:,1]
x3 = S[:,2]
x4 = S[:,3]

#writing
file.write("RE solution\n")
file.write("A {:.2f} B {:.2f} C {:.2f} D {:.2f}\n".format(A,B,C,D))
file.write("a {:.2f} b {:.2f} c {:.2f} d {:.2f}\n".format(a,b,c,d))
file.write("t      x1     x2     x3     x4\n")
for i in range(0,len(x1)):
    file.write("{:.4f} {:.4f} {:.4f} {:.4f} {:.4f}\n"
               .format(t[i], x1[i], x2[i], x3[i], x4[i]))

plt.plot(t, x1)
plt.plot(t, x2)
plt.plot(t, x3)
plt.plot(t, x4)

plt.show()
file.close()
