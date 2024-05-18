@REM g++ -c main.cpp -o .\main.o
@REM g++ -c .\Classes\duhr.cpp -o .\Classes\duhr.o
@REM g++ .\main.o .\Classes\duhr.o -o .\main.exe
@REM del .\main.o
@REM del .\Classes\duhr.o
@REM .\main

@REM g++ main.cpp -o main -lwininet

set SCRIPT_DIR=%~dp0
cd "%SCRIPT_DIR%"
g++ -J -O2 -o main main.cpp Functions/*.cpp -IFunctions -lwininet && main.exe