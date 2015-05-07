cd "%~dp0End Files"
gcc GameUI.c MainGame.c DrawingUI.c FileIO.c GameAI.c icon.res -o TerminalWarsTEST.exe -Wall -lws2_32
pause
cd ..
move "%~dp0End Files\TerminalWarsTest.exe" "%~dp0"
TerminalWarsTest
pause
del "%~dp0TerminalWarsTest.exe" /P
exit
