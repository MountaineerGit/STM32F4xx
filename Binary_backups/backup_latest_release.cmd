REM Backing up release elf file from ../Release F407 8MHz
@echo off

set BACKUP_FILE_SOURCE="Release F407 8MHz/grblHAL F407 8MHz.elf"
set OTHER_BACKUP_FILES="D:\Projekte\CNC\APPS\ioSender.XL.2.0.44\ioSender XL 2.0.44\settings.txt"
set ZIPPER="C:\Program Files\7-Zip\7z.exe"

set dt=%DATE:~6,4%_%DATE:~3,2%_%DATE:~0,2%__%TIME:~0,2%_%TIME:~3,2%_%TIME:~6,2%
set dt=%dt: =0%

echo %dt%


REM one level up to make git commands functional
cd ..

REM create status-log
wsl --exec git log -1 > git_status.txt
wsl --exec git submodule foreach "git status" > git_status_subs.txt


%ZIPPER% a ^
 Binary_backups/%dt%_backup.7z ^
 %BACKUP_FILE_SOURCE% ^
 %OTHER_BACKUP_FILES% ^
 git_status.txt ^
 git_status_subs.txt

if %errorlevel% neq 0 echo "ERROR: Something went wrong"

pause
