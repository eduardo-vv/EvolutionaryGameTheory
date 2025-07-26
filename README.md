# Simulations on Evolutionary Game Theory

This repository contains code pertaining to evolutionary game theory, covering topics from the solution of replicator equations to imitation dynamics. The code here was generated as tools for my master's degree. 

## Replicator Equations

In evolutionary game theory, the replicator equation (RE) is a set of equations that describes the evolution of the frequencies $x_i$​ of individuals using strategy indexed by $i$ [1]. For a game with $N$ strategies and a payoff matrix $M=[m_{ij​}]$, the replicator equation is defined as
$$	\dot x_i = x_i\left(\sum_{j}m_{ij} x_j-\sum_{i}\sum_{j}{x_i m_{ij} x_j}\right), \quad i = 1,..., N$$

where $\sum_i x_i = 1$. Or, more succintly, in vector form:
$$\dot{x}_i = x_i\left((M\vec{x})_i-\vec{x}^TM\vec{x}\right).$$
This equation holds when we assume an infinite population.

Furthermore, it's been shown that the imitation dynamics associated with the same game in a finite population approaches exactly this equation as $N\to\infty$ [2,3].

The Python code in this repository solves the replicator equations, while the C code uses a Monte Carlo method to simulate the imitation dynamics [4]. Currently, I've only addressed the four-strategy case, but theoretically, the code could be expanded trivially. More specifically, the code is written to facilitate the symmetrization of an asymmetric bimatrix game, as described by Gaunersdorfer _et al_ [5]. However, the values can be changed directly in the matrix M, and the code will work for any four-strategy game. The image below shows the comparison between the two approaches.

![Comparison between the RE solution and the Monte Carlo simulation](comparison.png  "Comparisson" )

**Important:** Don't trust this code blindly, as I can't guarantee it will work in every scenario. Use it at your own risk.

### References
[1] NOWAK, M. A. Evolutionary dynamics: exploring the equations of life. Cambridge, Mass: Belknap Press of Harvard University Press, 2006. ISBN 978-0-674-02338-3.

[2] TRAULSEN, A.; CLAUSSEN, J. C.; HAUERT, C. Coevolutionary Dynamics: From
Finite to Infinite Populations. Physical Review Letters, v. 95, n. 23, p. 238701,
dez. 2005. ISSN 0031-9007, 1079-7114. Available at: https://link.aps.org/doi/10.1103/
PhysRevLett.95.238701

[3] FONTANARI, J. F. Imitation dynamics and the replicator equation. Europhysics
Letters, v. 146, n. 4, p. 47001, maio 2024. ISSN 0295-5075, 1286-4854. Available at:
https://iopscience.iop.org/article/10.1209/0295-5075/ad473e

[4]CAPRARO, V.; PERC, M.; VILONE, D. The evolution of lying in well-mixed
populations. Journal of The Royal Society Interface, v. 16, n. 156, p. 20190211, jul.
2019. ISSN 1742-5689, 1742-5662. Available at: https://royalsocietypublishing.org/doi/
10.1098/rsif.2019.0211

[5] GAUNERSDORFER, A.; HOFBAUER, J.; SIGMUND, K. On the dynamics
of asymmetric games. Theoretical Population Biology, v. 39, n. 3, p. 345–357,
jun. 1991. ISSN 00405809. Available at: https://linkinghub.elsevier.com/retrieve/pii/
004058099190028E

