// Connection.cpp : Implementation of CConnection
#include "stdafx.h"
#include "XBase.h"
#include "Connection.h"

/////////////////////////////////////////////////////////////////////////////
// CConnection


STDMETHODIMP CConnection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IConnection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CConnection::FinalRelease()
{
	// Release the resources allocated by our library.
	xBaseFree(&this->hndBase);
}

STDMETHODIMP CConnection::Open(BSTR dbfPath)
{
	// Open the database.
	if (!xBaseOpen(&this->hndBase, dbfPath))
	{
		ERROR(TEXT("Couldn't open the database file"));
		return E_FAIL;
	}

	// Read the database header.
	if (!xBaseReadHeader(&this->hndBase))
	{
		ERROR(TEXT("Couldn't read the database file header"));
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CConnection::Close()
{
	// Close the database since we no longer need it.
	if (!xBaseClose(&this->hndBase))
	{
		ERROR(TEXT("Couldn't close the database file"));
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CConnection::Free()
{
	// Free up any resources.
	if (!xBaseFree(&this->hndBase))
	{
		ERROR(TEXT("Couldn't free the database handle resources"));
		return E_FAIL;
	}

	return S_OK;
}
