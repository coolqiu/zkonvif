@echo on
@echo �����̨������ȡ
@echo.
@echo ���뱻��̨����(Ʃ�� student,teacher...)
@set /p ptz_name= 
@echo ������̨����(Ʃ�� 1000)
@set /p zoom= 
@curl http://127.0.0.1:10003/ptz/%ptz_name%/set_zoom?%p_zoom%
@curl http://127.0.0.1:10003/ptz/%ptz_name%/get_zoom
@echo.
@echo.
@echo.
@echo off
@pause
