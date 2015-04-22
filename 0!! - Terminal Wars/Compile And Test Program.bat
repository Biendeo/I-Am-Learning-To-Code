cd "End Files"
gcc MainGame.c FileIO.c GameUI.c GameAI.c DrawingUI.c -o TerminalWarsTEST.exe -Wall
cd ..
move "%~dp0End Files\TerminalWarsTest.exe" "%~dp0"
pause
TerminalWarsTest
pause
exit