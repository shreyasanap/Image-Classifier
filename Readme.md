Tried PyQt for the first time and this all problems that i faced:

⚔️ Round 1: CMake and Compiler Chaos
I ran:

cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.9.1/mingw_64/lib/cmake"
And got hit with:

CMAKE_CXX_COMPILER not set
'nmake' not found
Turns out:

I hadn’t added mingw32-make to my system PATH

Needed to specify "MinGW Makefiles" instead of default NMake

✅ Fix: Added C:\Qt\Tools\mingw1310_64\bin to PATH and reconfigured.

😶 Round 2: The Invisible GUI
Even after building successfully, running .exe did... nothing. No errors, no window. Silent fail.

I later realized:

I had edited source files outside the build directory

I hadn’t re-run cmake or mingw32-make after editing

I was launching from the wrong directory

✅ Fix:

cmake ..
mingw32-make
.\ImageClassifierApp.exe
Boom 💥 — GUI appeared.

❌ Round 3: QML Modules Missing
As soon as I added a file dialog to QML, new errors flooded in:

module "QtQuick.Dialogs" is not installed
module "Qt.labs.platform" is not installed
Even worse:

QML QQuickImage: Protocol "c" is unknown
Turns out:

I couldn’t use FileDialog without extra QML modules (which weren’t installed)

QML doesn’t recognize raw Windows paths like C:\Users\...

It needs file:/// URLs to display images

✅ Fixes:

Replaced FileDialog with a simple TextField for file input

Manually prefixed the image path with file:/// before previewing

Made sure backend.imagePath was a valid URL for QML

Victory: GUI Finally Functional
After struggling through:

CMake config failures

Qt plugin issues

Missing modules

Path format errors

The GUI now:

Loads perfectly

Accepts image input

Previews the image

Connects with backend for classification