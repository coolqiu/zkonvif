#include "../soap/soapPullPointSubscriptionBindingProxy.h"
#include "../soap/wsseapi.h"
#include "../../common/log.h"
#include "../../common/utils.h"
#include "../../common/KVConfig.h"

// �����豸���� ...
void test_devicemgrt(const tds__Service *service)
{
	fprintf(stdout, "\n\n%s: url=%s\n", __FUNCTION__, service->XAddr.c_str());
}