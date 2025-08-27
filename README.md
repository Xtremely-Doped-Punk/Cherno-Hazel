# Cherno-Hazel
This repository is a walkthrough of game-engine development tutorial based on the references provided below.
- Official Repository: https://github.com/TheCherno/Hazel
- Youtube Playlist: https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

## Setup
### Premake
1. Download latest premake-core release into "support/bin/premake" relative to project ([reference](support/bin/premake/readme.md))
2. Open terminal in project root and run the premake application with respect to the editor studio you are using. For example:
```bat
support\bin\premake\premake5.exe vs2022
REM to generate Visual Studio .sln & .proj files with proper config
```
3. You can replace the similar platform based command into a bash file like `GenerateProjects.sh` instead of .bat file (for windows only) and directly run it instead of manually setting up everytime