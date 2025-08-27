#include "PrecompHead.h"
/*  Lesson: https://www.youtube.com/watch?v=eSI4wctZUto

- precompiled header make sures every cpp file within the project
- must have to include it during compile time.

- its a practice to be adapted when working a huge project with lots of dependencies
- which eventually saves a lot of build time reducing from exponential to linear time(s). How?

- all headers inside pch.h file is compiled as a single reference look ahead
- rather than manually jummpin only resp individual headers when they are included in the prog files.

- add option to display build time through: Tools -> Options -> Projects & Solutions -> VC++ Proj Settings

- note: not to add frequently changing header files in pch.h, why?
- well pch.h also like any header file, is be compiled, the main reason for the need to pch.h
- is to reduce the look ahead time of static libraries (like the std c++ libraries in most cases)
- u can ur own user's header files, but if it keeps changing, pch.h also needs to be compiled everytime it changes.

- "pch.h" will have to be used in every single source file then.

- most commonly used for code that are'nt yours, external libraries / dependencies
- for example: window api lib -> "Window.h" which is a massive header file that includes billion other header files
- and those code, u never gonna be touching into anytime ever, thus very much suitable to add it into pch.h

- pros: all dependencies are accessable from one header file itself
- cons: distinguishing readability 
- to figuring out which dependencies are used specifially resp cpp files across the project
- not an ideal practice: to add a library that being used by only one module like say GLFW
- that is to be used by Application Window handlers only perhaps
*/
