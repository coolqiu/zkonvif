@echo on
@echo ��װ python 2.7.8
python-2.7.8.msi
@echo ���� c:\Python27
xcopy .\Python27 c:\Python27 /EY
@echo ���� .\zkdm �� c:\zkdm

mkdir c:\zkdm

xcopy .\zkdm c:\zkdm /EY

@echo ��װ pywin32
pywin32-218.win32-py2.7.exe
@echo off
cd  c:\zkdm\ptz
install_ptz_winservice.bat