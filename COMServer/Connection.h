// Connection.h : Declaration of the CConnection

#ifndef __CONNECTION_H_
#define __CONNECTION_H_

#include "resource.h"       // main symbols
#include "..\LIBXBASE\xbasestruct.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CConnection
class ATL_NO_VTABLE CConnection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnection, &CLSID_Connection>,
	public ISupportErrorInfo,
	public IDispatchImpl<IConnection, &IID_IConnection, &LIBID_XBASELib>
{
public:
	CConnection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CONNECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CConnection)
	COM_INTERFACE_ENTRY(IConnection)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

void FinalRelease();

// IConnection
public:
	STDMETHOD(Free)();
	STDMETHOD(Close)();
	STDMETHOD(Open)(/*[in]*/ BSTR dbfPath);
protected:
	xBaseHandle hndBase;
};

#endif //__CONNECTION_H_
