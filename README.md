## Yard Sale Model

The repo contains a simulation (sim) and a visualization (viz) of Yard Sale Model.
I did this for educational purposes out of pure curiosity.

### Getting Started

#### Simulation

To compile:
```
gcc -o ysm -O2 sim/main.c
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
- **--export {filename}.csv** - outputs wealth change into csv file where each row is array values after an exchange. this option is helpful for visualizations.

#### Visualization

To compile on Windows:
```
gcc viz/main.c viz/dstr.c viz/dstr.h -o viz -I C:\raylib\w64devkit\include -L C:\raylib\w64devkit\lib -lraylib -lopengl32 -lgdi32 -lwinmm -O2
```

#### Visualization Options
- **-f {filename}.csv** - read csv data from specified file