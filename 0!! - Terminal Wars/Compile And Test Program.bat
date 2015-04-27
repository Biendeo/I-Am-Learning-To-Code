cd "%~dp0End Files"
gcc GameUI.c MainGame.c DrawingUI.c FileIO.c GameAI.c -o TerminalWarsTEST.exe -Wall
pause
cd ..
move "%~dp0End Files\TerminalWarsTest.exe" "%~dp0"
TerminalWarsTest
pause
del "%~dp0TerminalWarsTest.exe" /P
exit
