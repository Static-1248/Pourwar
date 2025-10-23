



### Dev Env Setup: Windows 10/11 x86_64 + Msys2 + UCRT64 set + Clang

1. Install Msys2 on Windows. Notice that you can modify its installation path.

2. Open Msys2 **UCRT64** terminal that comes with the installation. I recommend to pin it to the start menu for easy access.

3. Install following packages: 

- toolchain: `mingw-w64-ucrt-x86_64-toolchain`
- clang: `mingw-w64-ucrt-x86_64-clang`
- cmake: `mingw-w64-ucrt-x86_64-cmake`
- sdl2: `mingw-w64-ucrt-x86_64-SDL2`

```bash
# Update package database and core system packages
pacman -Syu
# It may prompt you to close the terminal window and reopen it to continue updating. Do so if prompted.
# Then do it again to ensure everything is up to date.
pacman -Syu

# Install "toolchain" package group
pacman -S --needed mingw-w64-ucrt-x86_64-toolchain
# when it prompts for selecting packages in the "toolchain" set, just press Enter to select all of them.

# Install clang, cmake, sdl2
pacman -S mingw-w64-ucrt-x86_64-clang mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-SDL2

# Update package database and core system packages again to ensure everything is up to date.
pacman -Syu
```

4. Set up system PATH variable to include Msys2 UCRT64 toolchain binaries. You can do this by adding the following path to your system PATH variable:

```C:\msys64\ucrt64\bin
```

**(Replace `C:\msys64` with your actual Msys2 installation path if it's different.)**