1. step 1, open git CMD and navigate to your vcpkg folder using 'cd vcpkg'
2. step 2, run the command ./vcpkg install imgui[sdl2-binding] this is using the SDL2 dependency
3. run the command, ./integrate install
4. step 4 install SDL2 via vcpkg 
5. run the command ./vcpkg install sdl2
6. run the command ./vcpkg integrate install
7. next step is to open visual studio and go to the solution explorer. Right click on references, and click "manage nuget packages".
8. Search for "sdl" and it should be the first option, "sdl2.nuget by kosmotema, xapdkop".
