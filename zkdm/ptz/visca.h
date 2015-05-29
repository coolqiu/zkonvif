#pragma once

/** ���ļ�ģ�� libvisca �ӿ�
 */

#ifdef __cplusplus
extern "C" {
#endif // c++

typedef struct visca_serial_t visca_serial_t;

enum {
	VISCA_ERR_OK = 0,
	VISCA_ERR_FAULT = -1,		// һ����� ...
	VISCA_ERR_SERIAL_OPEN = -2,	// �޷��򿪴���
};

/// �򿪣��رմ���
visca_serial_t *visca_open_serial(const char *serial_name, int *err);
void visca_close(visca_serial_t *ctx);

const char *visca_name(visca_serial_t *ctx);

/// ���� set address �㲥�룬������̨���� ..
int visca_set_address(visca_serial_t *ctx, int *num);


/// ��̨ת������
int visca_left(visca_serial_t *ctx, int addr, int speed);
int visca_right(visca_serial_t *ctx, int addr, int speed);
int visca_up(visca_serial_t *ctx, int addr, int speed);
int visca_down(visca_serial_t *ctx, int addr, int speed);
int visca_stop(visca_serial_t *ctx, int addr);

/// position
int visca_set_pos(visca_serial_t *ctx, int addr, int x, int y, int sx, int sy, int wait_complete);
int visca_set_rpos(visca_serial_t *ctx, int addr, int x, int y, int sx, int sy);
int visca_get_pos(visca_serial_t *ctx, int addr, int *x, int *y);

// zoom
int visca_zoom_tele(visca_serial_t *ctx, int addr, int speed);
int visca_zoom_wide(visca_serial_t *ctx, int addr, int speed);
int visca_zoom_stop(visca_serial_t *ctx, int addr);
int visca_get_zoom(visca_serial_t *ctx, int addr, int *z);
int visca_set_zoom(visca_serial_t *ctx, int addr, int z, int wait_complete);

#ifdef __cplusplus
}
#endif // c++
