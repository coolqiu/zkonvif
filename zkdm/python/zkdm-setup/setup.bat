@echo on
@echo ��װ python 2.7.8
python-2.7.8.msi
@echo ���� c:\Python27
xcopy .\Python27 c:\Python27 /EY
@echo ���� .\zkdm �� c:\zkdm

if not exist c:\zkdm (mkdir c:\zkdm)


if exist c:\zkdm\ptz\teacher.config (copy c:\zkdm\ptz\teacher.config .\zkdm\ptz\teacher.config /Y)

if exist c:\zkdm\ptz\student.config (copy c:\zkdm\ptz\student.config .\zkdm\ptz\student.config /Y)

xcopy .\zkdm c:\zkdm /EY
if exist c:\Windows\SysWOW32 (xcopy .\SysWOW32 c:\Windows\SysWOW32 /EY) else xcopy .\SysWOW64 c:\Windows\SysWOW64 /EY 


@echo ��װ pywin32
pywin32-218.win32-py2.7.exe
c:
cd c:\zkdm\ptz
@echo ���޸Ľ�ʦ�������ļ�
notepad teacher.config
pause
@echo ���޸�ѧ���������ļ�
@echo off
notepad student.config
pause
install_ptz_winservice.bat
