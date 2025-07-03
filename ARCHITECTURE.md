# Architecture

The source tree is organized by component with shared code under `src/common`.

```
src/
  common/          # Shared utilities for command line parsing, data structures
  convert_table/   # Conversion of LDHat tables to LDhelmet tables
  find_confs/      # Extraction of haplotype configurations
  max_lk/          # Constant-rate maximum likelihood estimation
  pade/            # Pade coefficient computation for interpolation
  post_to_text/    # Transformation of MCMC output to text
  rjmcmc/          # Reversible-jump MCMC sampler
  table_gen/       # Likelihood lookup table generation
  ldhelmet.cc      # Main entry point and command dispatcher
```

The `rjmcmc` module drives the core inference. It loads mutation matrices, SNP sequences, and precomputed lookup tables using utilities in `src/common`, partitions the SNPs, then launches a thread pool to sample recombination maps for each partition. Results are merged and stored in a binary format that `post_to_text` later interprets.

Lookup tables are created by `table_gen` (or `convert_table`) and may be refined using `pade`. Other modules such as `find_confs` preprocess input alignments to identify unique haplotype configurations.
