@echo off

REM Compile and execute the C++ file
g++ knightmn.cpp -o knightmn.exe
.\knightmn.exe


REM Run the Python file
python visualize.py