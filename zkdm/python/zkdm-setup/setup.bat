@echo on
@echo ��װpython 2.7.8

@python-2.7.8.msi

@echo ���� c:\Python27

@xcopy .\Python27 c:\Python27 /EY

@echo ���� .\zkdm �� c:\zkdm


@if not exist c:\zkdm (mkdir c:\zkdm)



@if exist c:\zkdm\ptz\teacher.config (copy c:\zkdm\ptz\teacher.config .\zkdm\ptz\teacher.config /Y)


@if exist c:\zkdm\ptz\student.config (copy c:\zkdm\ptz\student.config .\zkdm\ptz\student.config /Y)

@xcopy .\zkdm c:\zkdm /EY

@if exist c:\Windows\SysWOW64 (xcopy .\SysWOW64 c:\Windows\SysWOW64 /EY copy .\System64\curl.exe c:\Windows\System32 /Y)
@echo ��װpythonwin32
@pywin32-218.win32-py2.7.exe

@c:

@cd c:\zkdm\ptz
@echo ���޸Ľ�ʦ�������ļ�
@notepad teacher.config

@echo ���޸�ѧ���������ļ�
@echo off

@notepad student.config

@notepad bd.config
@install_ptz_winservice.bat
