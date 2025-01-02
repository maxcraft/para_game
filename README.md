# Para game
A small pet project of an old Paratrooper game. Built on Raylib. Used to test different concepts and having fun. The game doesn't not replicate the original in 100%.

## Linux
### Building
Building with default options are easy: just run
```
make
```

If one needs to specify additional CXXFLAGS, it's possible to run make like this:
```
make CXXFLAGS="-Wall -O3"
```

Also RAYLIB_HOME can be set to point non-standard Raylib directory.

### Running
Start game with no parameters:
```
./para_game
```

With Raylib installed in non-standard path use LD_LIBRARY_PATH environment variable:

```
LD_LIBRARY_PATH=/home/user/opt/lib ./para_game
```

## Other OS
The game was not tested on other OS like MacOS or Windows.