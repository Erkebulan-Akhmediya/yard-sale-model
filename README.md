## Yard Sale Model

The repo contains a simulation (sim) and a visualization (viz) of Yard Sale Model.
I did this for educational purposes out of pure curiosity.

### Getting Started

#### Simulation

To compile:
```
gcc -o sim -O2 sim/main.c
```

#### Simulation Options
- **--export {filename}.csv** - outputs wealth change into csv file where each row is array values after an exchange. this option is helpful for visualizations.

#### Visualization

To compile:
```
make
```

#### Visualization Options
- **-f {filename}.csv** - read csv data from specified file