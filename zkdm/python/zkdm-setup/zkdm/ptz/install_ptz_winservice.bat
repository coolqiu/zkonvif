@echo on

@c:\Python27\python PtzWinService.py install

@
sc config zonekey.service.ptz start= auto


@sc start zonekey.service.ptz
@echo �ɹ���װ zonekey.service.ptz ����
@echo off

pause