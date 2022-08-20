#include "stdafx.h"
#include "string.h"
#include <stdio.h>

#define AFX_STATIC extern
#define AFX_STATIC_DATA extern __declspec(selectany)
#define AFX_COMDAT __declspec(selectany)
#define INT_MAX 2147483647

AFX_STATIC_DATA int _afxInitData[] = { -1, 0, 0, 0 };
AFX_STATIC_DATA CStringData* _afxDataNil = (CStringData*)&_afxInitData;
TCHAR afxChNil = '\0';
AFX_COMDAT LPCTSTR _afxPchNil = (LPCTSTR)(((BYTE*)&_afxInitData)+sizeof(CStringData));
const CString& AFXAPI AfxGetEmptyString()
{ return *(CString*)&_afxPchNil; }
#define afxEmptyString AfxGetEmptyString()

//validadd.cpp
BOOL AFXAPI AfxIsValidString(LPCWSTR lpsz, int nLength)
{
	if (lpsz == NULL)
		return FALSE;
	return ::IsBadStringPtrW(lpsz, nLength) == 0;
}

// As above, but for ANSI strings.

BOOL AFXAPI AfxIsValidString(LPCSTR lpsz, int nLength)
{
	if (lpsz == NULL)
		return FALSE;
	return ::IsBadStringPtrA(lpsz, nLength) == 0;
}

BOOL AFXAPI AfxIsValidAddress(const void* lp, UINT nBytes,
							  BOOL bReadWrite)
{
	// simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}

//afx.inl
CStringData* CString::GetData() const
{ 
	ATLASSERT(m_pchData != NULL); 
	return ((CStringData*)m_pchData)-1; 
}

void CString::Init()
{
	m_pchData = afxEmptyString.m_pchData; 
}

CString::CString()
{
	m_pchData = afxEmptyString.m_pchData; 
}

CString::CString(const unsigned char* lpsz)
{
	Init(); *this = (LPCSTR)lpsz; 
}

const CString& CString::operator=(const unsigned char* lpsz)
{
	*this = (LPCSTR)lpsz; return *this; 
}

#ifdef _UNICODE
const CString& CString::operator+=(char ch)
{
	*this += (TCHAR)ch; return *this; 
}

const CString& CString::operator=(char ch)
{
	*this = (TCHAR)ch; return *this; 
}

CString AFXAPI operator+(const CString& string, char ch)
{
	return string + (TCHAR)ch; 
}

CString AFXAPI operator+(char ch, const CString& string)
{
	return (TCHAR)ch + string; 
}
#endif

int CString::GetLength() const
{
	return GetData()->nDataLength; 
}

int CString::GetAllocLength() const
{
	return GetData()->nAllocLength; 
}

BOOL CString::IsEmpty() const
{
	return GetData()->nDataLength == 0; 
}

CString::operator LPCTSTR() const
{
	return m_pchData; 
}

int PASCAL CString::SafeStrlen(LPCTSTR lpsz)
{
	return (lpsz == NULL) ? 0 : lstrlen(lpsz); 
}

// CString support (windows specific)
int CString::Compare(LPCTSTR lpsz) const
{
	ATLASSERT(AfxIsValidString(lpsz)); 
	return _tcscmp(m_pchData, lpsz); 
}    // MBCS/Unicode aware

int CString::CompareNoCase(LPCTSTR lpsz) const
{
	ATLASSERT(AfxIsValidString(lpsz)); 
	return _tcsicmp(m_pchData, lpsz); 
}   // MBCS/Unicode aware

// CString::Collate is often slower than Compare but is MBSC/Unicode
//  aware as well as locale-sensitive with respect to sort order.
int CString::Collate(LPCTSTR lpsz) const
{ 
	ATLASSERT(AfxIsValidString(lpsz)); 
	return _tcscoll(m_pchData, lpsz); 
}  // locale sensitive

int CString::CollateNoCase(LPCTSTR lpsz) const
{ 
	ATLASSERT(AfxIsValidString(lpsz)); 
	return _tcsicoll(m_pchData, lpsz); 
}   // locale sensitive

TCHAR CString::GetAt(int nIndex) const
{
	ATLASSERT(nIndex >= 0);
	ATLASSERT(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}

TCHAR CString::operator[](int nIndex) const
{
	// same as GetAt
	ATLASSERT(nIndex >= 0);
	ATLASSERT(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}

bool AFXAPI operator==(const CString& s1, const CString& s2)
{
	return s1.Compare(s2) == 0; 
}

bool AFXAPI operator==(const CString& s1, LPCTSTR s2)
{ 
	return s1.Compare(s2) == 0; 
}

bool AFXAPI operator==(LPCTSTR s1, const CString& s2)
{
	return s2.Compare(s1) == 0; 
}

bool AFXAPI operator!=(const CString& s1, const CString& s2)
{
	return s1.Compare(s2) != 0; 
}

bool AFXAPI operator!=(const CString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) != 0; 
}

bool AFXAPI operator!=(LPCTSTR s1, const CString& s2)
{
	return s2.Compare(s1) != 0; 
}

bool AFXAPI operator<(const CString& s1, const CString& s2)
{
	return s1.Compare(s2) < 0; 
}

bool AFXAPI operator<(const CString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) < 0; 
}

bool AFXAPI operator<(LPCTSTR s1, const CString& s2)
{
	return s2.Compare(s1) > 0; 
}

bool AFXAPI operator>(const CString& s1, const CString& s2)
{
	return s1.Compare(s2) > 0; 
}

bool AFXAPI operator>(const CString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) > 0; 
}

bool AFXAPI operator>(LPCTSTR s1, const CString& s2)
{
	return s2.Compare(s1) < 0; 
}

bool AFXAPI operator<=(const CString& s1, const CString& s2)
{
	return s1.Compare(s2) <= 0; 
}

bool AFXAPI operator<=(const CString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) <= 0; 
}

bool AFXAPI operator<=(LPCTSTR s1, const CString& s2)
{
	return s2.Compare(s1) >= 0; 
}

bool AFXAPI operator>=(const CString& s1, const CString& s2)
{
	return s1.Compare(s2) >= 0; 
}

bool AFXAPI operator>=(const CString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) >= 0; 
}

bool AFXAPI operator>=(LPCTSTR s1, const CString& s2)
{
	return s2.Compare(s1) <= 0; 
}

//winstr.cpp
#ifdef _UNICODE
#define CHAR_FUDGE 1    // one TCHAR unused is good enough
#else
#define CHAR_FUDGE 2    // two BYTES unused for case of DBC last char
#endif

BOOL CString::LoadString(UINT nID)
{
	// try fixed buffer first (to avoid wasting space in the heap)
	TCHAR szTemp[256];
	int nLen = AfxLoadString(nID, szTemp, _countof(szTemp));
	if (_countof(szTemp) - nLen > CHAR_FUDGE)
	{
		*this = szTemp;
		return nLen > 0;
	}
	
	// try buffer size of 512, then larger size until entire string is retrieved
	int nSize = 256;
	do
	{
		nSize += 256;
		nLen = AfxLoadString(nID, GetBuffer(nSize-1), nSize);
	} while (nSize - nLen <= CHAR_FUDGE);
	ReleaseBuffer();
	
	return nLen > 0;
}

#ifndef _AFXDLL
int AFXAPI AfxLoadString(UINT nID, LPTSTR lpszBuf, UINT nMaxBuf)
{
	ATLASSERT(AfxIsValidAddress(lpszBuf, nMaxBuf*sizeof(TCHAR)));
	int nLen = ::LoadString(_Module.m_hInstResource, nID, lpszBuf, nMaxBuf);
	if (nLen == 0)
		lpszBuf[0] = '\0';
	return nLen;
}
#endif

/////////////////////////////////////////////////////////////////////////////

BOOL AFXAPI AfxExtractSubString(CString& rString, LPCTSTR lpszFullString,
								int iSubString, TCHAR chSep)
{
	if (lpszFullString == NULL)
		return FALSE;
	
	while (iSubString--)
	{
		lpszFullString = _tcschr(lpszFullString, chSep);
		if (lpszFullString == NULL)
		{
			rString.Empty();        // return empty string as well
			return FALSE;
		}
		lpszFullString++;       // point past the separator
	}
	LPCTSTR lpchEnd = _tcschr(lpszFullString, chSep);
	int nLen = (lpchEnd == NULL) ?
		lstrlen(lpszFullString) : (int)(lpchEnd - lpszFullString);
	ATLASSERT(nLen >= 0);
	memcpy(rString.GetBufferSetLength(nLen), lpszFullString, nLen*sizeof(TCHAR));
	return TRUE;
}

//strex.cpp
CString::CString(TCHAR ch, int nLength)
{
	Init();
	if (nLength >= 1)
	{
		AllocBuffer(nLength);
#ifdef _UNICODE
		for (int i = 0; i < nLength; i++)
			m_pchData[i] = ch;
#else
		memset(m_pchData, ch, nLength);
#endif
	}
}

CString::CString(LPCTSTR lpch, int nLength)
{
	Init();
	if (nLength != 0)
	{
		ATLASSERT(AfxIsValidAddress(lpch, nLength, FALSE));
		AllocBuffer(nLength);
		memcpy(m_pchData, lpch, nLength*sizeof(TCHAR));
	}
}

/////////////////////////////////////////////////////////////////////////////
// Special conversion constructors

#ifdef _UNICODE
CString::CString(LPCSTR lpsz, int nLength)
{
	Init();
	if (nLength != 0)
	{
		AllocBuffer(nLength);
		int n = ::MultiByteToWideChar(CP_ACP, 0, lpsz, nLength, m_pchData, nLength+1);
		ReleaseBuffer(n >= 0 ? n : -1);
	}
}
#else //_UNICODE
CString::CString(LPCWSTR lpsz, int nLength)
{
	Init();
	if (nLength != 0)
	{
		AllocBuffer(nLength*2);
		int n = ::WideCharToMultiByte(CP_ACP, 0, lpsz, nLength, m_pchData,
			(nLength*2)+1, NULL, NULL);
		ReleaseBuffer(n >= 0 ? n : -1);
	}
}
#endif //!_UNICODE

//////////////////////////////////////////////////////////////////////////////
// Assignment operators

const CString& CString::operator=(TCHAR ch)
{
	AssignCopy(1, &ch);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////
// less common string expressions

CString AFXAPI operator+(const CString& string1, TCHAR ch)
{
	CString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData, 1, &ch);
	return s;
}

CString AFXAPI operator+(TCHAR ch, const CString& string)
{
	CString s;
	s.ConcatCopy(1, &ch, string.GetData()->nDataLength, string.m_pchData);
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// Advanced manipulation

int CString::Delete(int nIndex, int nCount /* = 1 */)
{
	if (nIndex < 0)
		nIndex = 0;
	int nNewLength = GetData()->nDataLength;
	if (nCount > 0 && nIndex < nNewLength)
	{
		CopyBeforeWrite();
		int nBytesToCopy = nNewLength - (nIndex + nCount) + 1;
		
		memcpy(m_pchData + nIndex,
			m_pchData + nIndex + nCount, nBytesToCopy * sizeof(TCHAR));
		GetData()->nDataLength = nNewLength - nCount;
	}
	
	return nNewLength;
}

int CString::Insert(int nIndex, TCHAR ch)
{
	CopyBeforeWrite();
	
	if (nIndex < 0)
		nIndex = 0;
	
	int nNewLength = GetData()->nDataLength;
	if (nIndex > nNewLength)
		nIndex = nNewLength;
	nNewLength++;
	
	if (GetData()->nAllocLength < nNewLength)
	{
		CStringData* pOldData = GetData();
		LPTSTR pstr = m_pchData;
		AllocBuffer(nNewLength);
		memcpy(m_pchData, pstr, (pOldData->nDataLength+1)*sizeof(TCHAR));
		CString::Release(pOldData);
	}
	
	// move existing bytes down
	memcpy(m_pchData + nIndex + 1,
		m_pchData + nIndex, (nNewLength-nIndex)*sizeof(TCHAR));
	m_pchData[nIndex] = ch;
	GetData()->nDataLength = nNewLength;
	
	return nNewLength;
}

int CString::Insert(int nIndex, LPCTSTR pstr)
{
	if (nIndex < 0)
		nIndex = 0;
	
	int nInsertLength = SafeStrlen(pstr);
	int nNewLength = GetData()->nDataLength;
	if (nInsertLength > 0)
	{
		CopyBeforeWrite();
		if (nIndex > nNewLength)
			nIndex = nNewLength;
		nNewLength += nInsertLength;
		
		if (GetData()->nAllocLength < nNewLength)
		{
			CStringData* pOldData = GetData();
			LPTSTR pstr = m_pchData;
			AllocBuffer(nNewLength);
			memcpy(m_pchData, pstr, (pOldData->nDataLength+1)*sizeof(TCHAR));
			CString::Release(pOldData);
		}
		
		// move existing bytes down
		memcpy(m_pchData + nIndex + nInsertLength,
			m_pchData + nIndex,
			(nNewLength-nIndex-nInsertLength+1)*sizeof(TCHAR));
		memcpy(m_pchData + nIndex,
			pstr, nInsertLength*sizeof(TCHAR));
		GetData()->nDataLength = nNewLength;
	}
	
	return nNewLength;
}

int CString::Replace(TCHAR chOld, TCHAR chNew)
{
	int nCount = 0;
	
	// short-circuit the nop case
	if (chOld != chNew)
	{
		// otherwise modify each character that matches in the string
		CopyBeforeWrite();
		LPTSTR psz = m_pchData;
		LPTSTR pszEnd = psz + GetData()->nDataLength;
		while (psz < pszEnd)
		{
			// replace instances of the specified character only
			if (*psz == chOld)
			{
				*psz = chNew;
				nCount++;
			}
			psz = _tcsinc(psz);
		}
	}
	return nCount;
}

int CString::Replace(LPCTSTR lpszOld, LPCTSTR lpszNew)
{
	// can't have empty or NULL lpszOld
	
	int nSourceLen = SafeStrlen(lpszOld);
	if (nSourceLen == 0)
		return 0;
	int nReplacementLen = SafeStrlen(lpszNew);
	
	// loop once to figure out the size of the result string
	int nCount = 0;
	LPTSTR lpszStart = m_pchData;
	LPTSTR lpszEnd = m_pchData + GetData()->nDataLength;
	LPTSTR lpszTarget;
	while (lpszStart < lpszEnd)
	{
		while ((lpszTarget = _tcsstr(lpszStart, lpszOld)) != NULL)
		{
			nCount++;
			lpszStart = lpszTarget + nSourceLen;
		}
		lpszStart += lstrlen(lpszStart) + 1;
	}
	
	// if any changes were made, make them
	if (nCount > 0)
	{
		CopyBeforeWrite();
		
		// if the buffer is too small, just
		//   allocate a new buffer (slow but sure)
		int nOldLength = GetData()->nDataLength;
		int nNewLength =  nOldLength + (nReplacementLen-nSourceLen)*nCount;
		if (GetData()->nAllocLength < nNewLength || GetData()->nRefs > 1)
		{
			CStringData* pOldData = GetData();
			LPTSTR pstr = m_pchData;
			AllocBuffer(nNewLength);
			memcpy(m_pchData, pstr, pOldData->nDataLength*sizeof(TCHAR));
			CString::Release(pOldData);
		}
		// else, we just do it in-place
		lpszStart = m_pchData;
		lpszEnd = m_pchData + GetData()->nDataLength;
		
		// loop again to actually do the work
		while (lpszStart < lpszEnd)
		{
			while ( (lpszTarget = _tcsstr(lpszStart, lpszOld)) != NULL)
			{
				int nBalance = nOldLength - (lpszTarget - m_pchData + nSourceLen);
				memmove(lpszTarget + nReplacementLen, lpszTarget + nSourceLen,
					nBalance * sizeof(TCHAR));
				memcpy(lpszTarget, lpszNew, nReplacementLen*sizeof(TCHAR));
				lpszStart = lpszTarget + nReplacementLen;
				lpszStart[nBalance] = '\0';
				nOldLength += (nReplacementLen - nSourceLen);
			}
			lpszStart += lstrlen(lpszStart) + 1;
		}
		ATLASSERT(m_pchData[nNewLength] == '\0');
		GetData()->nDataLength = nNewLength;
	}
	
	return nCount;
}

int CString::Remove(TCHAR chRemove)
{
	CopyBeforeWrite();
	
	LPTSTR pstrSource = m_pchData;
	LPTSTR pstrDest = m_pchData;
	LPTSTR pstrEnd = m_pchData + GetData()->nDataLength;
	
	while (pstrSource < pstrEnd)
	{
		if (*pstrSource != chRemove)
		{
			*pstrDest = *pstrSource;
			pstrDest = _tcsinc(pstrDest);
		}
		pstrSource = _tcsinc(pstrSource);
	}
	*pstrDest = '\0';
	int nCount = pstrSource - pstrDest;
	GetData()->nDataLength -= nCount;
	
	return nCount;
}

//////////////////////////////////////////////////////////////////////////////
// Very simple sub-string extraction

CString CString::Mid(int nFirst) const
{
	return Mid(nFirst, GetData()->nDataLength - nFirst);
}

CString CString::Mid(int nFirst, int nCount) const
{
	// out-of-bounds requests return sensible things
	if (nFirst < 0)
		nFirst = 0;
	if (nCount < 0)
		nCount = 0;
	
	if (nFirst + nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength - nFirst;
	if (nFirst > GetData()->nDataLength)
		nCount = 0;
	
	ATLASSERT(nFirst >= 0);
	ATLASSERT(nFirst + nCount <= GetData()->nDataLength);
	
	// optimize case of returning entire string
	if (nFirst == 0 && nFirst + nCount == GetData()->nDataLength)
		return *this;
	
	CString dest;
	AllocCopy(dest, nCount, nFirst, 0);
	return dest;
}

CString CString::Right(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	if (nCount >= GetData()->nDataLength)
		return *this;
	
	CString dest;
	AllocCopy(dest, nCount, GetData()->nDataLength-nCount, 0);
	return dest;
}

CString CString::Left(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	if (nCount >= GetData()->nDataLength)
		return *this;
	
	CString dest;
	AllocCopy(dest, nCount, 0, 0);
	return dest;
}

// strspn equivalent
CString CString::SpanIncluding(LPCTSTR lpszCharSet) const
{
	ATLASSERT(AfxIsValidString(lpszCharSet));
	return Left(_tcsspn(m_pchData, lpszCharSet));
}

// strcspn equivalent
CString CString::SpanExcluding(LPCTSTR lpszCharSet) const
{
	ATLASSERT(AfxIsValidString(lpszCharSet));
	return Left(_tcscspn(m_pchData, lpszCharSet));
}

//////////////////////////////////////////////////////////////////////////////
// Finding

int CString::ReverseFind(TCHAR ch) const
{
	// find last single character
	LPTSTR lpsz = _tcsrchr(m_pchData, (_TUCHAR) ch);
	
	// return -1 if not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

// find a sub-string (like strstr)
int CString::Find(LPCTSTR lpszSub) const
{
	return Find(lpszSub, 0);
}

int CString::Find(LPCTSTR lpszSub, int nStart) const
{
	ATLASSERT(AfxIsValidString(lpszSub));
	
	int nLength = GetData()->nDataLength;
	if (nStart > nLength)
		return -1;
	
	// find first matching substring
	LPTSTR lpsz = _tcsstr(m_pchData + nStart, lpszSub);
	
	// return -1 for not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}


/////////////////////////////////////////////////////////////////////////////
// CString formatting

#define TCHAR_ARG   TCHAR
#define WCHAR_ARG   WCHAR
#define CHAR_ARG    char

#ifdef _X86_
#define DOUBLE_ARG  _AFX_DOUBLE
#else
#define DOUBLE_ARG  double
#endif

#define FORCE_ANSI      0x10000
#define FORCE_UNICODE   0x20000
#define FORCE_INT64     0x40000

void CString::FormatV(LPCTSTR lpszFormat, va_list argList)
{
	ATLASSERT(AfxIsValidString(lpszFormat));
	
	va_list argListSave = argList;
	
	// make a guess at the maximum length of the resulting string
	int nMaxLen = 0;
	for (LPCTSTR lpsz = lpszFormat; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
	{
		// handle '%' character, but watch out for '%%'
		if (*lpsz != '%' || *(lpsz = _tcsinc(lpsz)) == '%')
		{
			nMaxLen += _tclen(lpsz);
			continue;
		}
		
		int nItemLen = 0;
		
		// handle '%' character with format
		int nWidth = 0;
		for (; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
		{
			// check for valid flags
			if (*lpsz == '#')
				nMaxLen += 2;   // for '0x'
			else if (*lpsz == '*')
				nWidth = va_arg(argList, int);
			else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' ||
				*lpsz == ' ')
				;
			else // hit non-flag character
				break;
		}
		// get width and skip it
		if (nWidth == 0)
		{
			// width indicated by
			nWidth = _ttoi(lpsz);
			for (; *lpsz != '\0' && _istdigit(*lpsz); lpsz = _tcsinc(lpsz))
				;
		}
		ATLASSERT(nWidth >= 0);
		
		int nPrecision = 0;
		if (*lpsz == '.')
		{
			// skip past '.' separator (width.precision)
			lpsz = _tcsinc(lpsz);
			
			// get precision and skip it
			if (*lpsz == '*')
			{
				nPrecision = va_arg(argList, int);
				lpsz = _tcsinc(lpsz);
			}
			else
			{
				nPrecision = _ttoi(lpsz);
				for (; *lpsz != '\0' && _istdigit(*lpsz); lpsz = _tcsinc(lpsz))
					;
			}
			ATLASSERT(nPrecision >= 0);
		}
		
		// should be on type modifier or specifier
		int nModifier = 0;
		if (_tcsncmp(lpsz, _T("I64"), 3) == 0)
		{
			lpsz += 3;
			nModifier = FORCE_INT64;
#if !defined(_X86_) && !defined(_ALPHA_)
			// __int64 is only available on X86 and ALPHA platforms
			ATLASSERT(FALSE);
#endif
		}
		else
		{
			switch (*lpsz)
			{
				// modifiers that affect size
			case 'h':
				nModifier = FORCE_ANSI;
				lpsz = _tcsinc(lpsz);
				break;
			case 'l':
				nModifier = FORCE_UNICODE;
				lpsz = _tcsinc(lpsz);
				break;
				
				// modifiers that do not affect size
			case 'F':
			case 'N':
			case 'L':
				lpsz = _tcsinc(lpsz);
				break;
			}
		}
		
		// now should be on specifier
		switch (*lpsz | nModifier)
		{
			// single characters
		case 'c':
		case 'C':
			nItemLen = 2;
			va_arg(argList, TCHAR_ARG);
			break;
		case 'c'|FORCE_ANSI:
		case 'C'|FORCE_ANSI:
			nItemLen = 2;
			va_arg(argList, CHAR_ARG);
			break;
		case 'c'|FORCE_UNICODE:
		case 'C'|FORCE_UNICODE:
			nItemLen = 2;
			va_arg(argList, WCHAR_ARG);
			break;
			
			// strings
		case 's':
			{
				LPCTSTR pstrNextArg = va_arg(argList, LPCTSTR);
				if (pstrNextArg == NULL)
					nItemLen = 6;  // "(null)"
				else
				{
					nItemLen = lstrlen(pstrNextArg);
					nItemLen = max(1, nItemLen);
				}
			}
			break;
			
		case 'S':
			{
#ifndef _UNICODE
				LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
				if (pstrNextArg == NULL)
					nItemLen = 6;  // "(null)"
				else
				{
					nItemLen = wcslen(pstrNextArg);
					nItemLen = max(1, nItemLen);
				}
#else
				LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
				if (pstrNextArg == NULL)
					nItemLen = 6; // "(null)"
				else
				{
					nItemLen = lstrlenA(pstrNextArg);
					nItemLen = max(1, nItemLen);
				}
#endif
			}
			break;
			
		case 's'|FORCE_ANSI:
		case 'S'|FORCE_ANSI:
			{
				LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
				if (pstrNextArg == NULL)
					nItemLen = 6; // "(null)"
				else
				{
					nItemLen = lstrlenA(pstrNextArg);
					nItemLen = max(1, nItemLen);
				}
			}
			break;
			
		case 's'|FORCE_UNICODE:
		case 'S'|FORCE_UNICODE:
			{
				LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
				if (pstrNextArg == NULL)
					nItemLen = 6; // "(null)"
				else
				{
					nItemLen = wcslen(pstrNextArg);
					nItemLen = max(1, nItemLen);
				}
			}
			break;
		}
		
		// adjust nItemLen for strings
		if (nItemLen != 0)
		{
			if (nPrecision != 0)
				nItemLen = min(nItemLen, nPrecision);
			nItemLen = max(nItemLen, nWidth);
		}
		else
		{
			switch (*lpsz)
			{
				// integers
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				if (nModifier & FORCE_INT64)
					va_arg(argList, __int64);
				else
					va_arg(argList, int);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;
				
			case 'e':
			case 'g':
			case 'G':
				va_arg(argList, DOUBLE_ARG);
				nItemLen = 128;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;
				
			case 'f':
				va_arg(argList, DOUBLE_ARG);
				nItemLen = 128; // width isn't truncated
				// 312 == strlen("-1+(309 zeroes).")
				// 309 zeroes == max precision of a double
				nItemLen = max(nItemLen, 312+nPrecision);
				break;
				
			case 'p':
				va_arg(argList, void*);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;
				
				// no output
			case 'n':
				va_arg(argList, int*);
				break;
				
			default:
				ATLASSERT(FALSE);  // unknown formatting option
			}
		}
		
		// adjust nMaxLen for output nItemLen
		nMaxLen += nItemLen;
	}
	
	GetBuffer(nMaxLen);
	VERIFY(_vstprintf(m_pchData, lpszFormat, argListSave) <= GetAllocLength());
	ReleaseBuffer();
	
	va_end(argListSave);
}

// formatting (using wsprintf style formatting)
void AFX_CDECL CString::Format(LPCTSTR lpszFormat, ...)
{
	ATLASSERT(AfxIsValidString(lpszFormat));
	
	va_list argList;
	va_start(argList, lpszFormat);
	FormatV(lpszFormat, argList);
	va_end(argList);
}

void AFX_CDECL CString::Format(UINT nFormatID, ...)
{
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);
	
	va_list argList;
	va_start(argList, nFormatID);
	FormatV(strFormat, argList);
	va_end(argList);
}

// formatting (using FormatMessage style formatting)
void AFX_CDECL CString::FormatMessage(LPCTSTR lpszFormat, ...)
{
	// format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, lpszFormat);
	LPTSTR lpszTemp;
	
	if (::FormatMessage(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		lpszFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		lpszTemp == NULL)
	{
		throw;
	}
	
	// assign lpszTemp into the resulting string and free the temporary
	*this = lpszTemp;
	LocalFree(lpszTemp);
	va_end(argList);
}

void AFX_CDECL CString::FormatMessage(UINT nFormatID, ...)
{
	// get format string from string table
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);
	
	// format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, nFormatID);
	LPTSTR lpszTemp;
	if (::FormatMessage(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		strFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		lpszTemp == NULL)
	{
		throw;
	}
	
	// assign lpszTemp into the resulting string and free lpszTemp
	*this = lpszTemp;
	LocalFree(lpszTemp);
	va_end(argList);
}

void CString::TrimRight(LPCTSTR lpszTargetList)
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)
	
	CopyBeforeWrite();
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;
	
	while (*lpsz != '\0')
	{
		if (_tcschr(lpszTargetList, *lpsz) != NULL)
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		lpsz = _tcsinc(lpsz);
	}
	
	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void CString::TrimRight(TCHAR chTarget)
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)
	
	CopyBeforeWrite();
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;
	
	while (*lpsz != '\0')
	{
		if (*lpsz == chTarget)
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		lpsz = _tcsinc(lpsz);
	}
	
	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void CString::TrimRight()
{
	// find beginning of trailing spaces by starting at beginning (DBCS aware)
	
	CopyBeforeWrite();
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;
	
	while (*lpsz != '\0')
	{
		if (_istspace(*lpsz))
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		lpsz = _tcsinc(lpsz);
	}
	
	if (lpszLast != NULL)
	{
		// truncate at trailing space start
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void CString::TrimLeft(LPCTSTR lpszTargets)
{
	// if we're not trimming anything, we're not doing any work
	if (SafeStrlen(lpszTargets) == 0)
		return;
	
	CopyBeforeWrite();
	LPCTSTR lpsz = m_pchData;
	
	while (*lpsz != '\0')
	{
		if (_tcschr(lpszTargets, *lpsz) == NULL)
			break;
		lpsz = _tcsinc(lpsz);
	}
	
	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(TCHAR));
		GetData()->nDataLength = nDataLength;
	}
}

void CString::TrimLeft(TCHAR chTarget)
{
	// find first non-matching character
	
	CopyBeforeWrite();
	LPCTSTR lpsz = m_pchData;
	
	while (chTarget == *lpsz)
		lpsz = _tcsinc(lpsz);
	
	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(TCHAR));
		GetData()->nDataLength = nDataLength;
	}
}

void CString::TrimLeft()
{
	// find first non-space character
	
	CopyBeforeWrite();
	LPCTSTR lpsz = m_pchData;
	
	while (_istspace(*lpsz))
		lpsz = _tcsinc(lpsz);
	
	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(TCHAR));
		GetData()->nDataLength = nDataLength;
	}
}

//strcore.cpp
CString::CString(const CString& stringSrc)
{
	ATLASSERT(stringSrc.GetData()->nRefs != 0);
	if (stringSrc.GetData()->nRefs >= 0)
	{
		ATLASSERT(stringSrc.GetData() != _afxDataNil);
		m_pchData = stringSrc.m_pchData;
		InterlockedIncrement(&GetData()->nRefs);
	}
	else
	{
		Init();
		*this = stringSrc.m_pchData;
	}
}

void CString::AllocBuffer(int nLen)
// always allocate one extra character for '\0' termination
{
	ATLASSERT(nLen >= 0);
	ATLASSERT(nLen <= INT_MAX-1);    // max size (enough room for 1 extra)
	
	if (nLen == 0)
		Init();
	else
	{
		CStringData* pData;
		pData = (CStringData*)
			new BYTE[sizeof(CStringData) + (nLen+1)*sizeof(TCHAR)];
		pData->nAllocLength = nLen;
		pData->nRefs = 1;
		pData->data()[nLen] = '\0';
		pData->nDataLength = nLen;
		m_pchData = pData->data();
	}
}

void FASTCALL CString::FreeData(CStringData* pData)
{
	delete[] (BYTE*)pData;
}

void CString::Release()
{
	if (GetData() != _afxDataNil)
	{
		ATLASSERT(GetData()->nRefs != 0);
		if (InterlockedDecrement(&GetData()->nRefs) <= 0)
			FreeData(GetData());
		Init();
	}
}

void PASCAL CString::Release(CStringData* pData)
{
	if (pData != _afxDataNil)
	{
		ATLASSERT(pData->nRefs != 0);
		if (InterlockedDecrement(&pData->nRefs) <= 0)
			FreeData(pData);
	}
}

void CString::Empty()
{
	if (GetData()->nDataLength == 0)
		return;
	if (GetData()->nRefs >= 0)
		Release();
	else
		*this = &afxChNil;
	ATLASSERT(GetData()->nDataLength == 0);
	ATLASSERT(GetData()->nRefs < 0 || GetData()->nAllocLength == 0);
}

void CString::CopyBeforeWrite()
{
	if (GetData()->nRefs > 1)
	{
		CStringData* pData = GetData();
		Release();
		AllocBuffer(pData->nDataLength);
		memcpy(m_pchData, pData->data(), (pData->nDataLength+1)*sizeof(TCHAR));
	}
	ATLASSERT(GetData()->nRefs <= 1);
}

void CString::AllocBeforeWrite(int nLen)
{
	if (GetData()->nRefs > 1 || nLen > GetData()->nAllocLength)
	{
		Release();
		AllocBuffer(nLen);
	}
	ATLASSERT(GetData()->nRefs <= 1);
}

CString::~CString()
//  free any attached data
{
	if (GetData() != _afxDataNil)
	{
		if (InterlockedDecrement(&GetData()->nRefs) <= 0)
			FreeData(GetData());
	}
}

//////////////////////////////////////////////////////////////////////////////
// Helpers for the rest of the implementation

void CString::AllocCopy(CString& dest, int nCopyLen, int nCopyIndex,
						int nExtraLen) const
{
	// will clone the data attached to this string
	// allocating 'nExtraLen' characters
	// Places results in uninitialized string 'dest'
	// Will copy the part or all of original data to start of new string
	
	int nNewLen = nCopyLen + nExtraLen;
	if (nNewLen == 0)
	{
		dest.Init();
	}
	else
	{
		dest.AllocBuffer(nNewLen);
		memcpy(dest.m_pchData, m_pchData+nCopyIndex, nCopyLen*sizeof(TCHAR));
	}
}

//////////////////////////////////////////////////////////////////////////////
// More sophisticated construction

CString::CString(LPCTSTR lpsz)
{
	Init();
	if (lpsz != NULL && HIWORD(lpsz) == NULL)
	{
		UINT nID = LOWORD((DWORD)lpsz);
		if (!LoadString(nID))
			ATLTRACE("Warning: implicit LoadString(%u) failed\n", nID);
	}
	else
	{
		int nLen = SafeStrlen(lpsz);
		if (nLen != 0)
		{
			AllocBuffer(nLen);
			memcpy(m_pchData, lpsz, nLen*sizeof(TCHAR));
		}
	}
}

int AFX_CDECL _wcstombsz(char* mbstr, const wchar_t* wcstr, size_t count)
{
	if (count == 0 && mbstr != NULL)
		return 0;
	
	int result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1,
		mbstr, count, NULL, NULL);
	ATLASSERT(mbstr == NULL || result <= (int)count);
	if (result > 0)
		mbstr[result-1] = 0;
	return result;
}

int AFX_CDECL _mbstowcsz(wchar_t* wcstr, const char* mbstr, size_t count)
{
	if (count == 0 && wcstr != NULL)
		return 0;
	
	int result = ::MultiByteToWideChar(CP_ACP, 0, mbstr, -1,
		wcstr, count);
	ATLASSERT(wcstr == NULL || result <= (int)count);
	if (result > 0)
		wcstr[result-1] = 0;
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// Special conversion constructors

#ifdef _UNICODE
CString::CString(LPCSTR lpsz)
{
	Init();
	int nSrcLen = lpsz != NULL ? lstrlenA(lpsz) : 0;
	if (nSrcLen != 0)
	{
		AllocBuffer(nSrcLen);
		_mbstowcsz(m_pchData, lpsz, nSrcLen+1);
		ReleaseBuffer();
	}
}
#else //_UNICODE
CString::CString(LPCWSTR lpsz)
{
	Init();
	int nSrcLen = lpsz != NULL ? wcslen(lpsz) : 0;
	if (nSrcLen != 0)
	{
		AllocBuffer(nSrcLen*2);
		_wcstombsz(m_pchData, lpsz, (nSrcLen*2)+1);
		ReleaseBuffer();
	}
}
#endif //!_UNICODE

void CString::AssignCopy(int nSrcLen, LPCTSTR lpszSrcData)
{
	AllocBeforeWrite(nSrcLen);
	memcpy(m_pchData, lpszSrcData, nSrcLen*sizeof(TCHAR));
	GetData()->nDataLength = nSrcLen;
	m_pchData[nSrcLen] = '\0';
}

const CString& CString::operator=(const CString& stringSrc)
{
	if (m_pchData != stringSrc.m_pchData)
	{
		if ((GetData()->nRefs < 0 && GetData() != _afxDataNil) ||
			stringSrc.GetData()->nRefs < 0)
		{
			// actual copy necessary since one of the strings is locked
			AssignCopy(stringSrc.GetData()->nDataLength, stringSrc.m_pchData);
		}
		else
		{
			// can just copy references around
			Release();
			ATLASSERT(stringSrc.GetData() != _afxDataNil);
			m_pchData = stringSrc.m_pchData;
			InterlockedIncrement(&GetData()->nRefs);
		}
	}
	return *this;
}

const CString& CString::operator=(LPCTSTR lpsz)
{
	ATLASSERT(lpsz == NULL || AfxIsValidString(lpsz));
	AssignCopy(SafeStrlen(lpsz), lpsz);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Special conversion assignment

#ifdef _UNICODE
const CString& CString::operator=(LPCSTR lpsz)
{
	int nSrcLen = lpsz != NULL ? lstrlenA(lpsz) : 0;
	AllocBeforeWrite(nSrcLen);
	_mbstowcsz(m_pchData, lpsz, nSrcLen+1);
	ReleaseBuffer();
	return *this;
}
#else //!_UNICODE
const CString& CString::operator=(LPCWSTR lpsz)
{
	int nSrcLen = lpsz != NULL ? wcslen(lpsz) : 0;
	AllocBeforeWrite(nSrcLen*2);
	_wcstombsz(m_pchData, lpsz, (nSrcLen*2)+1);
	ReleaseBuffer();
	return *this;
}
#endif  //!_UNICODE

//////////////////////////////////////////////////////////////////////////////
// concatenation

// NOTE: "operator+" is done as friend functions for simplicity
//      There are three variants:
//          CString + CString
// and for ? = TCHAR, LPCTSTR
//          CString + ?
//          ? + CString

void CString::ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data,
						 int nSrc2Len, LPCTSTR lpszSrc2Data)
{
	// -- master concatenation routine
	// Concatenate two sources
	// -- assume that 'this' is a new CString object
	
	int nNewLen = nSrc1Len + nSrc2Len;
	if (nNewLen != 0)
	{
		AllocBuffer(nNewLen);
		memcpy(m_pchData, lpszSrc1Data, nSrc1Len*sizeof(TCHAR));
		memcpy(m_pchData+nSrc1Len, lpszSrc2Data, nSrc2Len*sizeof(TCHAR));
	}
}

CString AFXAPI operator+(const CString& string1, const CString& string2)
{
	CString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData,
		string2.GetData()->nDataLength, string2.m_pchData);
	return s;
}

CString AFXAPI operator+(const CString& string, LPCTSTR lpsz)
{
	ATLASSERT(lpsz == NULL || AfxIsValidString(lpsz));
	CString s;
	s.ConcatCopy(string.GetData()->nDataLength, string.m_pchData,
		CString::SafeStrlen(lpsz), lpsz);
	return s;
}

CString AFXAPI operator+(LPCTSTR lpsz, const CString& string)
{
	ATLASSERT(lpsz == NULL || AfxIsValidString(lpsz));
	CString s;
	s.ConcatCopy(CString::SafeStrlen(lpsz), lpsz, string.GetData()->nDataLength,
		string.m_pchData);
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// concatenate in place

void CString::ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData)
{
	//  -- the main routine for += operators
	
	// concatenating an empty string is a no-op!
	if (nSrcLen == 0)
		return;
	
	// if the buffer is too small, or we have a width mis-match, just
	//   allocate a new buffer (slow but sure)
	if (GetData()->nRefs > 1 || GetData()->nDataLength + nSrcLen > GetData()->nAllocLength)
	{
		// we have to grow the buffer, use the ConcatCopy routine
		CStringData* pOldData = GetData();
		ConcatCopy(GetData()->nDataLength, m_pchData, nSrcLen, lpszSrcData);
		ATLASSERT(pOldData != NULL);
		CString::Release(pOldData);
	}
	else
	{
		// fast concatenation when buffer big enough
		memcpy(m_pchData+GetData()->nDataLength, lpszSrcData, nSrcLen*sizeof(TCHAR));
		GetData()->nDataLength += nSrcLen;
		ATLASSERT(GetData()->nDataLength <= GetData()->nAllocLength);
		m_pchData[GetData()->nDataLength] = '\0';
	}
}

const CString& CString::operator+=(LPCTSTR lpsz)
{
	ATLASSERT(lpsz == NULL || AfxIsValidString(lpsz));
	ConcatInPlace(SafeStrlen(lpsz), lpsz);
	return *this;
}

const CString& CString::operator+=(TCHAR ch)
{
	ConcatInPlace(1, &ch);
	return *this;
}

const CString& CString::operator+=(const CString& string)
{
	ConcatInPlace(string.GetData()->nDataLength, string.m_pchData);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Advanced direct buffer access

LPTSTR CString::GetBuffer(int nMinBufLength)
{
	ATLASSERT(nMinBufLength >= 0);
	
	if (GetData()->nRefs > 1 || nMinBufLength > GetData()->nAllocLength)
	{
#ifdef _DEBUG
		// give a warning in case locked string becomes unlocked
		if (GetData() != _afxDataNil && GetData()->nRefs < 0)
			ATLTRACE("Warning: GetBuffer on locked CString creates unlocked CString!\n");
#endif
		// we have to grow the buffer
		CStringData* pOldData = GetData();
		int nOldLen = GetData()->nDataLength;   // AllocBuffer will tromp it
		if (nMinBufLength < nOldLen)
			nMinBufLength = nOldLen;
		AllocBuffer(nMinBufLength);
		memcpy(m_pchData, pOldData->data(), (nOldLen+1)*sizeof(TCHAR));
		GetData()->nDataLength = nOldLen;
		CString::Release(pOldData);
	}
	ATLASSERT(GetData()->nRefs <= 1);
	
	// return a pointer to the character storage for this string
	ATLASSERT(m_pchData != NULL);
	return m_pchData;
}

void CString::ReleaseBuffer(int nNewLength)
{
	CopyBeforeWrite();  // just in case GetBuffer was not called
	
	if (nNewLength == -1)
		nNewLength = lstrlen(m_pchData); // zero terminated
	
	ATLASSERT(nNewLength <= GetData()->nAllocLength);
	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';
}

LPTSTR CString::GetBufferSetLength(int nNewLength)
{
	ATLASSERT(nNewLength >= 0);
	
	GetBuffer(nNewLength);
	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';
	return m_pchData;
}

void CString::FreeExtra()
{
	ATLASSERT(GetData()->nDataLength <= GetData()->nAllocLength);
	if (GetData()->nDataLength != GetData()->nAllocLength)
	{
		CStringData* pOldData = GetData();
		AllocBuffer(GetData()->nDataLength);
		memcpy(m_pchData, pOldData->data(), pOldData->nDataLength*sizeof(TCHAR));
		ATLASSERT(m_pchData[GetData()->nDataLength] == '\0');
		CString::Release(pOldData);
	}
	ATLASSERT(GetData() != NULL);
}

LPTSTR CString::LockBuffer()
{
	LPTSTR lpsz = GetBuffer(0);
	GetData()->nRefs = -1;
	return lpsz;
}

void CString::UnlockBuffer()
{
	ATLASSERT(GetData()->nRefs == -1);
	if (GetData() != _afxDataNil)
		GetData()->nRefs = 1;
}

///////////////////////////////////////////////////////////////////////////////
// Commonly used routines (rarely used routines in STREX.CPP)

int CString::Find(TCHAR ch) const
{
	return Find(ch, 0);
}

int CString::Find(TCHAR ch, int nStart) const
{
	int nLength = GetData()->nDataLength;
	if (nStart >= nLength)
		return -1;
	
	// find first single character
	LPTSTR lpsz = _tcschr(m_pchData + nStart, (_TUCHAR)ch);
	
	// return -1 if not found and index otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

int CString::FindOneOf(LPCTSTR lpszCharSet) const
{
	ATLASSERT(AfxIsValidString(lpszCharSet));
	LPTSTR lpsz = _tcspbrk(m_pchData, lpszCharSet);
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

void CString::MakeUpper()
{
	CopyBeforeWrite();
	_tcsupr(m_pchData);
}

void CString::MakeLower()
{
	CopyBeforeWrite();
	_tcslwr(m_pchData);
}

void CString::MakeReverse()
{
	CopyBeforeWrite();
	_tcsrev(m_pchData);
}

void CString::SetAt(int nIndex, TCHAR ch)
{
	ATLASSERT(nIndex >= 0);
	ATLASSERT(nIndex < GetData()->nDataLength);
	
	CopyBeforeWrite();
	m_pchData[nIndex] = ch;
}

#ifndef _UNICODE
void CString::AnsiToOem()
{
	CopyBeforeWrite();
	::AnsiToOem(m_pchData, m_pchData);
}
void CString::OemToAnsi()
{
	CopyBeforeWrite();
	::OemToAnsi(m_pchData, m_pchData);
}
#endif

//oledisp1.cpp
BSTR CString::AllocSysString() const
{
#if defined(_UNICODE) || defined(OLE2ANSI)
	BSTR bstr = ::SysAllocStringLen(m_pchData, GetData()->nDataLength);
	if (bstr == NULL)
		throw;
#else
	int nLen = MultiByteToWideChar(CP_ACP, 0, m_pchData,
		GetData()->nDataLength, NULL, NULL);
	BSTR bstr = ::SysAllocStringLen(NULL, nLen);
	if (bstr == NULL)
		throw;
	MultiByteToWideChar(CP_ACP, 0, m_pchData, GetData()->nDataLength,
		bstr, nLen);
#endif
	
	return bstr;
}

BSTR CString::SetSysString(BSTR* pbstr) const
{
	ATLASSERT(AfxIsValidAddress(pbstr, sizeof(BSTR)));
	
#if defined(_UNICODE) || defined(OLE2ANSI)
	if (!::SysReAllocStringLen(pbstr, m_pchData, GetData()->nDataLength))
		throw;
#else
	int nLen = MultiByteToWideChar(CP_ACP, 0, m_pchData,
		GetData()->nDataLength, NULL, NULL);
	if (!::SysReAllocStringLen(pbstr, NULL, nLen))
		throw;
	MultiByteToWideChar(CP_ACP, 0, m_pchData, GetData()->nDataLength,
		*pbstr, nLen);
#endif
	
	ATLASSERT(*pbstr != NULL);
	return *pbstr;
}
