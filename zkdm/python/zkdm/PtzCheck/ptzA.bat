@echo on
@echo �����̨�Ƿ�Ӵ�˿ں�
@echo.
@echo ���뱻��̨����(Ʃ�� student,teacher...)
@set /p ptz_name= 
@curl "http://127.0.0.1:10003/ptz/%ptz_name%/set_pos?x=0&y=0"

ping -n 3 127.0.0.1>nul

@curl "http://127.0.0.1:10003/ptz/%ptz_name%/set_pos?x=400&y=400"

ping -n 3 127.0.0.1>nul

@curl "http://127.0.0.1:10003/ptz/%ptz_name%/set_pos?x=-400&y=-400"

ping -n 3 127.0.0.1>nul

@curl "http://127.0.0.1:10003/ptz/%ptz_name%/set_pos?x=0&y=0"
@echo.
@echo.
@echo.
@echo off
@pause