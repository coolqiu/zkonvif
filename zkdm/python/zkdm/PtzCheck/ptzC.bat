@echo on
@echo �������,��̨˫��ͨѶ
@echo.
@echo ���뱻��̨����(Ʃ�� student,teacher...)
@set /p ptz_name= 
@curl http://127.0.0.1:10003/ptz/%ptz_name%/is_prepared
@echo.
@echo.
@echo.
@echo off
@pause
