@echo off
cd /d "%~dp0"

echo Changes to be pushed:
git status --short
echo.

set /p msg=Enter commit message:
if "%msg%"=="" (
    echo No message entered. Cancelled.
    pause
    exit /b 1
)

git add -A
git commit -m "%msg%"
git push -u origin main

echo.
echo Done.
pause
