# Mathematical Background

LDhelmet implements statistical methods for inferring recombination rates from sequence alignments. The key algorithm is a reversible-jump Markov chain Monte Carlo (RJMCMC) sampler that explores piecewise-constant recombination maps.

Lookup tables of two-locus likelihoods are precomputed using dynamic programming and Pade approximations. During MCMC, these tables are used to evaluate the likelihood of proposed recombination rate changes.

This repository does not contain a formal proof of correctness, but the algorithms follow those described in the publications cited in `README.md`. The code implements the recursions and acceptance probabilities required by those methods.
