# Cowboy3i
Just a cowboy game


## Compiling from source in console

### Creating GLFW static library using gcc:
Compile to object files:

```
gcc -D_GLFW_WIN32 -Iinclude -lgdi32 -c .\src\context.c .\src\init.c .\src\input.c .\src\monitor.c .\src\null_init.c .\src\null_joystick.c .\src\null_monitor.c .\src\null_window.c .\src\platform.c .\src\vulkan.c .\src\window.c .\src\win32_*.c .\src\wgl_context.c .\src\egl_context.c .\src\osmesa_context.c
```

Create static library (archive)
```
ar -rcv glfw.a *.o
```
Can run `ar -t glfw.a` to see a table of object files in the archive.

### Creating glad object file using gcc

```
gcc -Iinclude -c .\src\glad.c
```

### Compiling Main program 


```
g++ -ICowboyPewPew\vendor\Glad\include\ -ICowboyPewPew\vendor\GLFW\include\ -c .\CowboyPewPew\src\Main.cpp
```

### Final linking to create executable triangle example:

```
g++ -o test.exe Main.o .\glad.o .\glfw.a -lgdi32 -o test.exe
```

```
em++ --use-port=contrib.glfw3 -sFULL_ES3 .\Main.o .\glad.o -o index.html 
```

