:: takie cos znalazlem zeby uruchomic wszystki badania na raz, fajne co. ma to sie znajdowac w folderze gdzie jest aizo_2.exe ktory usunalem, wiec to wisi w folderze data

@echo off
setlocal EnableDelayedExpansion

set PROGRAM=aizo_2.exe
set OUTPUT_DIR=..\data\results


if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%


set DENSITIES=25 50 99
set VERTICES=60 80 100 120 140 160 180
set ALGORITHMS=0 1 2 3
set REPRESENTATIONS=0 1
set COUNT=50
set SRC=0


for %%D in (%DENSITIES%) do (
    for %%V in (%VERTICES%) do (
        call set /A DST=%%V-1

        for %%R in (%REPRESENTATIONS%) do (
            for %%A in (%ALGORITHMS%) do (
                echo === ALGORYTM %%A i GESTOSC %%D i WIERZCHOLKI %%V i REP %%R ===

                set "OUTFILE=%OUTPUT_DIR%\alg%%A_dens%%D_v%%V_rep%%R.txt"

                if %%A==0 (
                    call %PROGRAM% --test %%A %%R %%D %%V %COUNT% !OUTFILE! %SRC%
                ) else if %%A GEQ 2 (
                    call %PROGRAM% --test %%A %%R %%D %%V %COUNT% !OUTFILE! %SRC% !DST!
                ) else (
                    call %PROGRAM% --test %%A %%R %%D %%V %COUNT% !OUTFILE!
                )

                echo Zapisano do !OUTFILE!
            )
        )
    )
)

echo === KONIEC ===
pause
