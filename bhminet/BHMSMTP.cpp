// BHMSMTP.cpp : Implementation of CBHMSMTP
#include "stdafx.h"
#include "BHMINet.h"
#include "BHMSMTP.h"
#include "smtp.h"
#include "string.h"

/////////////////////////////////////////////////////////////////////////////
// CBHMSMTP

STDMETHODIMP CBHMSMTP::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBHMSMTP,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBHMSMTP::OnStartPage (IUnknown* pUnk)  
{
	if(!pUnk)
		return E_POINTER;

	CComPtr<IScriptingContext> spContext;
	HRESULT hr;

	// Get the IScriptingContext Interface
	hr = pUnk->QueryInterface(IID_IScriptingContext, (void **)&spContext);
	if(FAILED(hr))
		return hr;

	// Get Request Object Pointer
	hr = spContext->get_Request(&m_piRequest);
	if(FAILED(hr))
	{
		spContext.Release();
		return hr;
	}

	// Get Response Object Pointer
	hr = spContext->get_Response(&m_piResponse);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		return hr;
	}
	
	// Get Server Object Pointer
	hr = spContext->get_Server(&m_piServer);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		m_piResponse.Release();
		return hr;
	}
	
	// Get Session Object Pointer
	hr = spContext->get_Session(&m_piSession);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		m_piResponse.Release();
		m_piServer.Release();
		return hr;
	}

	// Get Application Object Pointer
	hr = spContext->get_Application(&m_piApplication);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		m_piResponse.Release();
		m_piServer.Release();
		m_piSession.Release();
		return hr;
	}
	m_bOnStartPageCalled = TRUE;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::OnEndPage ()  
{
	m_bOnStartPageCalled = FALSE;
	// Release all interfaces
	m_piRequest.Release();
	m_piResponse.Release();
	m_piServer.Release();
	m_piSession.Release();
	m_piApplication.Release();

	return S_OK;
}


STDMETHODIMP CBHMSMTP::Send()
{
	USES_CONVERSION;

	InitSocket();
	if (!m_bSocketInited)
	{
		CString sResponse = _T("Can not init winsock");

		if (m_piResponse)
		{
			sResponse = _T("<p>") + sResponse;
			sResponse += _T("<p>");
			CComVariant va = sResponse;
			m_piResponse->Write(va);
			return S_OK;
		}
		else
			return Error(sResponse);
	}
//	LPHOSTENT lphost;
//	lphost = gethostbyname("linyf");

	CSMTPConnection conn;
	CSMTPMessage msg;

	if (!conn.Connect(OLE2T(m_strServer)))
	{
		CString sResponse = conn.GetLastCommandResponse();
		if (sResponse.IsEmpty())
			sResponse = _T("Can not link to mail server");

		if (m_piResponse)
		{
			sResponse = _T("<p>") + sResponse;
			sResponse += _T("<p>");
			CComVariant va = sResponse;
			m_piResponse->Write(va);
			return S_OK;
		}
		else
			return Error(sResponse);
	}

	CSMTPAddress From(OLE2A(m_strFromName), OLE2A(m_strFrom));
	msg.m_From = From;
	CSMTPAddress To(OLE2A(m_strRcpt));
	msg.AddRecipient(To, CSMTPMessage::TO);
	msg.m_sSubject = OLE2A(m_strSubject);
	msg.AddBody(OLE2A(m_strMessage));
	
	CString strAttach = OLE2A(m_strAttach);
	CString strField;
	int j = 0;
	CSMTPAttachment * pAtt;
	
	while (j < strAttach.GetLength())
	{
		if (strAttach[j] != _T(';'))
			strField += strAttach[j];
		else if (strField.GetLength())
		{
			if (IsValidFilePath(strField))
			{
				pAtt = new CSMTPAttachment;
				pAtt->Attach(strField);
				msg.AddAttachment(pAtt);
			}

			strField.Empty();
		}

		j ++;
	}

	if (strField.GetLength())
	{
		if (IsValidFilePath(strField))
		{
			pAtt = new CSMTPAttachment;
			pAtt->Attach(strField);
			msg.AddAttachment(pAtt);
		}
	}
	
	int i;

	if (!conn.SendMessage(msg))
	{
		for (i = msg.GetNumberOfAttachments(); i > 0; i --)
		{
			delete msg.GetAttachment(0);
			msg.RemoveAttachment(0);
		}

		CString sResponse = conn.GetLastCommandResponse();
		if (sResponse.IsEmpty())
			sResponse = _T("Can not send mail");

		if (m_piResponse)
		{
			sResponse = _T("<p>") + sResponse;
			sResponse += _T("<p>");
			CComVariant va = sResponse;
			m_piResponse->Write(va);
			return S_OK;
		}
		else
			return Error(sResponse);
	}
	
	for (i = msg.GetNumberOfAttachments(); i > 0; i --)
	{
		delete msg.GetAttachment(0);
		msg.RemoveAttachment(0);
	}

	//Disconnect from the server
	conn.Disconnect();
	WSACleanup();;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_Rcpt(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strRcpt.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_Rcpt(BSTR newVal)
{
	USES_CONVERSION;
	m_strRcpt = newVal;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_From(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strFrom.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_From(BSTR newVal)
{
	USES_CONVERSION;
	m_strFrom = newVal;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_FromName(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strFromName.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_FromName(BSTR newVal)
{
	USES_CONVERSION;
	m_strFromName = newVal;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_Subject(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strSubject.Copy();
	
	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_Subject(BSTR newVal)
{
	USES_CONVERSION;
	m_strSubject = newVal;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_Message(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strMessage.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_Message(BSTR newVal)
{
/*	if (SysStringLen(newVal) > 64000)
	{
		SysFreeString(newVal);
		if (m_piResponse)
		{
			CComVariant va = _T("Message can not exceed 64k");
			m_piResponse->Write(va);
			return S_OK;
		}
		else
			return Error(_T("Message can not exceed 64k"));
	}
*/
	USES_CONVERSION;
	m_strMessage = newVal;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_ContentType(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strContentType.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_ContentType(BSTR newVal)
{
	m_strContentType = newVal;

	return S_OK;
}

void CBHMSMTP::InitSocket()
{
	m_bSocketInited = FALSE;
	// initialize Winsock library
	WSADATA wsaData, * lpwsaData = NULL;
	if (lpwsaData == NULL)
		lpwsaData = &wsaData;
	
	WORD wVersionRequested = MAKEWORD(1, 1);
	int nResult = WSAStartup(wVersionRequested, lpwsaData);
	if (nResult != 0)
		return;
	
	if (LOBYTE(lpwsaData->wVersion) != 1 || HIBYTE(lpwsaData->wVersion) != 1)
	{
		WSACleanup();
		m_bSocketInited = TRUE;
		return;
	}
}

STDMETHODIMP CBHMSMTP::get_Server(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strServer.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_Server(BSTR newVal)
{
	m_strServer = newVal;

	return S_OK;
}

STDMETHODIMP CBHMSMTP::get_Attach(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = m_strAttach.Copy();

	return S_OK;
}

STDMETHODIMP CBHMSMTP::put_Attach(BSTR newVal)
{
	m_strAttach = newVal;

	return S_OK;
}

BOOL CBHMSMTP::IsValidFilePath(LPCTSTR strPath)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(strPath, &findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return TRUE;
	}
	else
		return FALSE;
}
