@echo off

setlocal

REM 强制切换工作目录为脚本目录，防止Eclipse下相对路径错误
cd /d "%~dp0"

REM 设置编码
chcp 65001 >nul

call post_build.bat
call test.bat

endlocal







