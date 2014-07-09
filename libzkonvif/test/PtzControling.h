#pragma once

#include "../../common/KVConfig.h"
#include "../../../3rd/libvisca-1.1.0/visca/libvisca.h"
#include "ZoomValueConvert.h"

class PtzControlling
{
public:
	virtual ~PtzControlling() {}
	virtual int open() = 0;
	virtual void close() = 0;
	
	virtual void reset() = 0;
	
	virtual void setpos(int x, int y, int sx, int sy) = 0;
	virtual int getpos(int &x, int &y) = 0;

	virtual void stop() = 0;
	virtual void left(int x) = 0;
	virtual void right(int x) = 0;
	virtual void up(int x) = 0;
	virtual void down(int x) = 0;

	virtual void zoom_set(int z) = 0;
	virtual int zoom_get(int &z) = 0;

	virtual void preset_set(int n) = 0;
	virtual void preset_get(int n) = 0;
	virtual void preset_del(int n) = 0;

	struct PtzParam
	{
		double f; // ����
		double ccd_size_width, ccd_size_height;	// cmos ��С
		double pan_min_angle, tilt_min_angle;	// ˮƽ����ֱ������С��
		double pan_max_va, tilt_max_va;		// ˮƽ����ֱ��������ӽǣ�1��ʱ), �������ʣ�ֱ��ʹ�ø�ֵ���Ա��ʼ��� ..
	};

	virtual const PtzParam &getPtzParam() const = 0;
	virtual double getScales() = 0;
};

/** ������̨ʱ ...
 */
class PtzControllingDummy : public PtzControlling
{
	PtzParam param_;

	int open() { return 0; }
	void close() {}

	void reset() {}

	void setpos(int x, int y, int speed_x, int speed_y){}
	int getpos(int &x, int &y) { x = 0, y = 0; return 0; }

	void stop(){}
	void left(int s) {}
	void right(int s) {}
	void up(int s) {}
	void down(int s) {}

	void zoom_set(int z) {}
	int zoom_get(int &z) { z = 0; return 0; }

	const PtzParam &getPtzParam() const { return param_; }

	double getScales() { return 1.0; }

	void preset_set(int n) {}
	void preset_get(int n) {}
	void preset_del(int n) {}
};

/** ��װ��̨�Ļ������� ...
 */
class PtzControllingVisca : public PtzControlling
{
	KVConfig *cfg_;
	VISCAInterface_t visca_;
	VISCACamera_t cam_;	// FIXME: ����֧��һ�����㹻�� :)
	ZoomValueConvert zvc_;
	std::string name_;	// �����ӡ ...

	bool changed_zoom_;		int last_zoom_;
	bool changed_pos_;		int last_x_, last_y_;

public:
	PtzControllingVisca(KVConfig *cfg);
	virtual ~PtzControllingVisca(void);

	int open();
	void close();

	void reset();	// ת���� ptz_init_x, ptz_init_y, ��ͷ�� ptz_init_z
	
	void setpos(int x, int y, int speed_x, int speed_y);
	int getpos(int &x, int &y);

	void stop();
	void left(int s);
	void right(int s);
	void up(int s);
	void down(int s);

	void zoom_set(int z);
	int zoom_get(int &z);

	const PtzParam &getPtzParam() const { return param_; }

	double getScales();	// ��ȡ��ǰ���� ..

	void preset_set(int n);
	void preset_get(int n);
	void preset_del(int n);

protected:
	KVConfig *cfg() { return cfg_; }

private:
	PtzParam param_;
};
