#ifdef WIN32

#include "sysperf.h"
#include "../../../common/log.h"
#include <comutil.h>
#include <assert.h>

#pragma comment(lib, "comsuppw.lib")

SysPerf::SysPerf()
{
	quit_ = false;
	start();
}

SysPerf::~SysPerf()
{
	quit_ = true;
	join();
}

void SysPerf::run()
{
	CoInitialize(0);
	IWbemLocator *locator = 0;
	IWbemServices *services = 0;

	HRESULT hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (void**)&locator);
	if (hr != S_OK) {
		log(LOG_ERROR, "%s: can't create CLSID_WbemLocator objects, hr=%08x\n", __func__, hr);
	}

	CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
		);

	hr = locator->ConnectServer(BSTR(L"ROOT\\CIMV2"), 0, 0, 0, 0, 0, 0, &services);
	if (hr != S_OK) {
		log(LOG_ERROR, "%s: IWebLocator::ConnectServer err, hr=%08x\n", __func__, hr);
		locator->Release();
		locator = 0;
	}

	hr = CoSetProxyBlanket(services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, 0, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, 0, EOAC_NONE);
	if (hr != S_OK) {
		log(LOG_ERROR, "%s: CoSetProxyBlanket err, hr=%08x\n", __func__, hr);
		services->Release(), services = 0;
		locator->Release(), locator = 0;
	}

	while (!quit_) {
		once(services);
		sleep(1000);	// ÿ��1��ˢ�� ...
	}

	if (services)
		services->Release(), services = 0;

	if (locator)
		locator->Release(), locator = 0;

	CoUninitialize();
}

void SysPerf::once(IWbemServices *s)
{
	update_cpu(s);
	update_mem(s);
	update_disk(s);
	update_net(s);

	fprintf(stderr, "cpu: %%%.3f, mem: tot=%.3f, used=%.3f\n", cpurate_, mem_tot_ / 1000000.0, mem_used_ / 1000000.0);
}

void SysPerf::update_cpu(IWbemServices *s)
{
	IEnumWbemClassObject *em = 0;
	IWbemClassObject *obj = 0;

	// cpu
	HRESULT hr = s->ExecQuery(bstr_t("WQL"), bstr_t("SELECT PercentProcessorTime FROM Win32_PerfFormattedData_PerfOS_Processor where Name='_Total'"),
							  WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 0, &em);
	while (1) {
		ULONG got;
		hr = em->Next(WBEM_INFINITE, 1, &obj, &got);
		if (got == 0)
			break;

		VARIANT val;
		VariantInit(&val);

		hr = obj->Get(L"PercentProcessorTime", 0, &val, 0, 0);
		/// Note  When querying for property values with a uint64 or sint64 data type in a scripting language like VBScript, WMI returns string values.
		///    �泶������ .
		assert(val.vt == VT_BSTR);

		cpurate_ = atof((char*)bstr_t(val.bstrVal));

		obj->Release();
	}

	em->Release();
}

void SysPerf::update_mem(IWbemServices *s)
{
	IEnumWbemClassObject *em = 0;
	IWbemClassObject *obj = 0;

	HRESULT hr = s->ExecQuery(bstr_t("WQL"), bstr_t("SELECT CommittedBytes,CommitLimit FROM Win32_PerfFormattedData_PerfOS_Memory"),
							  WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 0, &em);
	while (1) {
		ULONG got;
		hr = em->Next(WBEM_INFINITE, 1, &obj, &got);
		if (got == 0)
			break;

		VARIANT val;
		VariantInit(&val);

		hr = obj->Get(L"CommittedBytes", 0, &val, 0, 0);
		assert(val.vt == VT_BSTR);
		mem_used_ = atof((char*)bstr_t(val.bstrVal));

		hr = obj->Get(L"CommitLimit", 0, &val, 0, 0);
		assert(val.vt == VT_BSTR);
		mem_tot_ = atof((char*)bstr_t(val.bstrVal));
	}
}

void SysPerf::update_net(IWbemServices *s)
{
	IEnumWbemClassObject *em = 0;
	IWbemClassObject *obj = 0;

	// TODO: ��Ҫָ���������֣� ....

}

void SysPerf::update_disk(IWbemServices *s)
{
	// ����ĸ�������
	// 
}

#endif // 
