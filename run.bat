@REM g++ -c main.cpp -o .\main.o
@REM g++ -c .\Classes\duhr.cpp -o .\Classes\duhr.o
@REM g++ .\main.o .\Classes\duhr.o -o .\main.exe
@REM del .\main.o
@REM del .\Classes\duhr.o
@REM .\main
g++ main.cpp -o main -lwininet
.\main.exe