@echo off
chcp 860
SET dir=%cd%
gcc -Wall "%dir%\src\main.c" -o "%dir%\build\debug\4_em_linha" -Og -static-libgcc -static-libstdc++
echo END OF COMPILATION
echo.
PAUSE