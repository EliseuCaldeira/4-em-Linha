@echo off
chcp 860
SET dir=%cd%
gcc "%dir%\src\main.c" -o "%dir%\build\release\4_em_linha" -Ofast -static-libgcc -static-libstdc++
echo END OF COMPILATION
echo.
PAUSE