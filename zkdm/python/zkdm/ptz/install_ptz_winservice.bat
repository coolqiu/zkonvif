@echo on
c:\Python27\python PtzWinService.py install

sc config zonekey.service.ptz start= auto

sc start zonekey.service.ptz

@echo zonekey.service.ptz �ɹ���װ������
@echo off
pause