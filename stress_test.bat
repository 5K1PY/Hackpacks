@echo off

for /l %%i in (1, 1, 100) do (
    echo %%i

    python Gen.py > input.txt
    Program.exe < input.txt > output.txt
    Program2.exe < input.txt > answer.txt

    fc output.txt answer.txt || goto :out
)

:out