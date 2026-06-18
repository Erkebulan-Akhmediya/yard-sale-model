## Yard Sale Model

The repo contains a simulation (ysm.c) and a visualization (viz.c) of Yard Sale Model.
I did this for educational purposes out of pure curiosity.

### Getting Started

#### Simulation

To compile:
```
gcc -o ysm -O2 ysm.c
```

To run executable on Linux:
```
./ysm
```

To run executable on Windows:
```
.\ysm.exe
```

#### Simulation Options
- **--csv** - outputs wealth change into csv file where each row is array values after an exchange. this option is helpful for visualizations.

#### Visualization

To compile on Windows:
```
gcc viz.c -o viz -I C:\raylib\w64devkit\include -L C:\raylib\w64devkit\lib -lraylib -lopengl32 -lgdi32 -lwinmm
```