@echo on
@echo ��װ zonekey.service.ptz ����
c:\Python27\python PtzWinService.py install


@echo ���� zonekey.service.ptz Ϊ�Զ�����
sc config zonekey.service.ptz start= auto

@echo.
@echo.
@echo.
@echo **********************************************************************
@echo *                       ע������                                      *
@echo * ��windows services��,�鿴 zonekey.service.ptz �Ƿ����? ������:     *
@echo *   1  ��c:\zkdm\ptzĿ¼��,�޸������ļ�teacher.config��student.config *
@echo *   (hva,vva�ֱ�Ϊˮƽ�ӽ�,��ֱ�ӽ�,�Զ�Ϊ��λ)                       *
@echo *   2 ���� zonekey.service.ptz  ����                                  *
@echo **********************************************************************
@echo.
@echo off
pause



