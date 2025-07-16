@echo off
setlocal enableextensions

REM 强制切换工作目录为脚本目录，防止Eclipse下相对路径错误
cd /d "%~dp0"

REM 设置编码
chcp 65001 >nul


REM 获取日期和时间
for /f "tokens=2 delims==." %%a in ('"wmic os get localdatetime /value"') do set ldt=%%a

set YYYY=%ldt:~0,4%
set MM=%ldt:~4,2%
set DD=%ldt:~6,2%
set HH=%ldt:~8,2%
set Min=%ldt:~10,2%

REM 设置文件路径
set SRC=..\src\407vet6\Debug\simple_frame.hex
set SRC_BIN=..\src\407vet6\Debug\simple_frame.bin

set DST=..\fireware\app_%YYYY%%MM%%DD%_%HH%%Min%.hex
set DST_BIN=..\fireware\app_%YYYY%%MM%%DD%_%HH%%Min%.bin



REM 执行复制并重命名
copy "%SRC%" "%DST%" >nul
copy "%SRC_BIN%" "%DST_BIN%" >nul

IF %ERRORLEVEL% EQU 0 (
    echo 文件已成功复制为 a.bin
) ELSE (
    echo 复制失败，检查路径或文件是否存在
)

pause






