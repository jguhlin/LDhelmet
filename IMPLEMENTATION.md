# Implementation Notes

## Language and Build

The software is written in ISO C++ and built using `make`. It relies on the Boost libraries and the GNU Scientific Library. After installing the dependencies, building is performed in the repository root by running `make`, which produces the `ldhelmet` binary.

## Components

`ldhelmet.cc` acts as the entry point and dispatches to several subcommands:

- **find_confs** – scans aligned haplotype sequences and writes unique configurations.
- **table_gen** – generates likelihood lookup tables for a grid of recombination rates.
- **convert_table** – converts LDHat lookup tables to LDhelmet format.
- **pade** – computes Pade coefficients used for likelihood interpolation.
- **rjmcmc** – performs reversible-jump MCMC to infer recombination maps.
- **post_to_text** – converts MCMC output to a human readable format.
- **max_lk** – computes the maximum likelihood estimate under a constant rate model.

Each component parses command-line options using the facilities in `src/common/command_line_options.*` and then executes a workflow implemented in its respective directory.

## Example Scripts

The `example_scripts` folder provides bash scripts illustrating typical usage. They demonstrate calling the subcommands in sequence to generate tables, run `rjmcmc`, and summarize the posterior output.

