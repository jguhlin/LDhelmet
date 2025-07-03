# LDhelmet Overview

LDhelmet is a C++ implementation for estimating fine-scale recombination rates from population genomic data. It includes utilities to prepare input haplotype configurations, create lookup tables, run reversible-jump MCMC inference, and extract results. Example bash scripts demonstrate a typical workflow.

**Key features**

- Command line tool `ldhelmet` with subcommands such as `find_confs`, `table_gen`, `convert_table`, `pade`, `rjmcmc`, `post_to_text`, and `max_lk`.
- Uses Boost and the GNU Scientific Library as dependencies.
- Designed for multi-threaded execution and whole genome analyses.
- Distributed under the GNU GPLv3.

For full usage instructions see the included PDF manual.
