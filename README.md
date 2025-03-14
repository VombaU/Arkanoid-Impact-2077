# 🎮 Arkanoid-Impact-2077

A personal recreation of the classic Arkanoid game, built using a bare bones C++ graphics library I got from a dear friend after he's failed one of his interviews. Despite the lack of documentation, I held my head up high and managed to reverse-engineer its functionality and successfully make the game.

![image](https://github.com/user-attachments/assets/7fe91bd4-6976-49e3-9f38-4de5e2942cb4)

**N.B.** Only works on Windows x64
# 🖥️ How to playtest
A built version has been included in this repository for the lazybones and risque alike, but - below are some building instructions if you're neither!

**N.B.** To exit the game, just press 'Esc' on your keyboard.
# ⚙️ How to build
**Visual Studio**
1. Create a project -> Empty C++ Project
2. Copy the files from the lib, include, and src and place them all together with the project files. They MUST be in the same folder (Framework issue, not fixable as I don't have its source)
3. Do the same with the data folder, except that you don't get the files from it you just copy the entire folder (that is, the images inside data MUST belong to a 'data' folder) (Framework issue)
4. Go to your project's settings -> Linker -> Input
5. Edit 'Additional Dependencies' and add 'FrameworkRelease_x64.lib'
6. Next, still in the project's settings, go to C/C++ -> Preprocessor
7. Edit 'Preprocessor Definitions' and add '_WINDOWS'
8. Build the project

**CMake**
- Coming Soon! -
