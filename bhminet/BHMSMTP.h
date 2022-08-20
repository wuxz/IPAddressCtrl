// BHMSMTP.h : Declaration of the CBHMSMTP

#ifndef __BHMSMTP_H_
#define __BHMSMTP_H_

#include "resource.h"       // main symbols
#include <asptlb.h>         // Active Server Pages Definitions

/////////////////////////////////////////////////////////////////////////////
// CBHMSMTP
class ATL_NO_VTABLE CBHMSMTP : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBHMSMTP, &CLSID_BHMSMTP>,
	public ISupportErrorInfo,
	public IDispatchImpl<IBHMSMTP, &IID_IBHMSMTP, &LIBID_BHMINETLib>
{
public:
	CBHMSMTP()
	{ 
		USES_CONVERSION;

		m_bOnStartPageCalled = FALSE;
		m_strRcpt = _T("");
		m_strFrom = _T("");
		m_strFromName = _T("");
		m_strSubject = _T("");
		m_strMessage = _T("");
		m_strContentType = _T("text/plain");
		m_strServer = _T("");
		m_bSocketInited = FALSE;
		m_strAttach = _T("");
	}

public:

DECLARE_REGISTRY_RESOURCEID(IDR_BHMSMTP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBHMSMTP)
	COM_INTERFACE_ENTRY(IBHMSMTP)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBHMSMTP
public:
	STDMETHOD(get_Attach)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Attach)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Server)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Server)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ContentType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ContentType)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Message)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Message)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Subject)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Subject)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_FromName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FromName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_From)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_From)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Rcpt)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Rcpt)(/*[in]*/ BSTR newVal);
	STDMETHOD(Send)();
	//Active Server Pages Methods
	STDMETHOD(OnStartPage)(IUnknown* IUnk);
	STDMETHOD(OnEndPage)();

private:
	CComPtr<IRequest> m_piRequest;					//Request Object
	CComPtr<IResponse> m_piResponse;				//Response Object
	CComPtr<ISessionObject> m_piSession;			//Session Object
	CComPtr<IServer> m_piServer;					//Server Object
	CComPtr<IApplicationObject> m_piApplication;	//Application Object
	BOOL m_bOnStartPageCalled;						//OnStartPage successful?

	CComBSTR m_strRcpt, m_strFrom, m_strFromName, m_strSubject, m_strMessage,
		m_strContentType, m_strServer, m_strAttach;
protected:
	BOOL IsValidFilePath(LPCTSTR strPath);
	BOOL m_bSocketInited;
	void InitSocket();
};

#endif //__BHMSMTP_H_
