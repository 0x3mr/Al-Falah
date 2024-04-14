g++ -c main.cpp -o .\main.o
g++ -c .\Classes\CLI.cpp -o .\Classes\CLI.o
g++ .\main.o .\Classes\CLI.o -o .\main.exe
del .\main.o
del .\Classes\CLI.o
.\main