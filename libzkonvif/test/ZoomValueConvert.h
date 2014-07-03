#pragma once

#include "../../common/KVConfig.h"
#include "polyfit.h"

/** ��̨������ ptz_zoom_get ���֮��Ĺ�ϵ */
class ZoomValueConvert
{
	KVConfig *cfg_;
	double factors_[6];	// ����ʽϵ��
	double factors2_[6];	

public:
	ZoomValueConvert(KVConfig *cfg);
	~ZoomValueConvert(void);

	// ���� zv (ptz_zoom_get()�ķ���) �����㱶��
	double mp_zoom(int zv);
	int pm_zoom(double scale); // �ӱ���ת���� zoom value

private:
	// ����ϵ��
	int load_factors();
};
