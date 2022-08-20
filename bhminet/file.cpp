#include "stdafx.h"
#include "file.h"


CFile::operator HFILE() const
	{ return m_hFile; }
DWORD CFile::ReadHuge(void* lpBuffer, DWORD dwCount)
	{ return (DWORD)Read(lpBuffer, (UINT)dwCount); }
void CFile::WriteHuge(const void* lpBuffer, DWORD dwCount)
	{ Write(lpBuffer, (UINT)dwCount); }
DWORD CFile::SeekToEnd()
	{ return Seek(0, CFile::end); }
void CFile::SeekToBegin()
	{ Seek(0, CFile::begin); }

void CFile::SetFilePath(LPCTSTR lpszNewName)
{
	ASSERT_VALID(this);
	ATLASSERT(AfxIsValidString(lpszNewName));
	m_strFileName = lpszNewName;
}

CFile::CFile()
{
	m_hFile = (UINT) hFileNull;
	m_bCloseOnDelete = FALSE;
}

CFile::CFile(int hFile)
{
	m_hFile = hFile;
	m_bCloseOnDelete = FALSE;
}

CFile::CFile(LPCTSTR lpszFileName, UINT nOpenFlags)
{
	ATLASSERT(AfxIsValidString(lpszFileName));

	Open(lpszFileName, nOpenFlags);
}

CFile::~CFile()
{
	if (m_hFile != (UINT)hFileNull && m_bCloseOnDelete)
		Close();
}

CFile* CFile::Duplicate() const
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	CFile* pFile = new CFile(hFileNull);
	HANDLE hFile;
	if (!::DuplicateHandle(::GetCurrentProcess(), (HANDLE)m_hFile,
		::GetCurrentProcess(), &hFile, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		delete pFile;
		return NULL;
	}
	pFile->m_hFile = (UINT)hFile;
	ATLASSERT(pFile->m_hFile != (UINT)hFileNull);
	pFile->m_bCloseOnDelete = m_bCloseOnDelete;
	return pFile;
}

BOOL CFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags)
{
	ASSERT_VALID(this);
	ATLASSERT(AfxIsValidString(lpszFileName));
	ATLASSERT((nOpenFlags & typeText) == 0);   // text mode not supported

	// CFile objects are always binary and CreateFile does not need flag
	nOpenFlags &= ~(UINT)typeBinary;

	m_bCloseOnDelete = FALSE;
	m_hFile = (UINT)hFileNull;
	m_strFileName.Empty();

//	TCHAR szTemp[_MAX_PATH];
//	AfxFullPath(szTemp, lpszFileName);
//	m_strFileName = szTemp;

	ATLASSERT(sizeof(HANDLE) == sizeof(UINT));
	ATLASSERT(shareCompat == 0);

	// map read/write mode
	ATLASSERT((modeRead|modeWrite|modeReadWrite) == 3);
	DWORD dwAccess = 0;
	switch (nOpenFlags & 3)
	{
	case modeRead:
		dwAccess = GENERIC_READ;
		break;
	case modeWrite:
		dwAccess = GENERIC_WRITE;
		break;
	case modeReadWrite:
		dwAccess = GENERIC_READ|GENERIC_WRITE;
		break;
	default:
		ATLASSERT(FALSE);  // invalid share mode
	}

	// map share mode
	DWORD dwShareMode = 0;
	switch (nOpenFlags & 0x70)    // map compatibility mode to exclusive
	{
	default:
		ATLASSERT(FALSE);  // invalid share mode?
	case shareCompat:
	case shareExclusive:
		dwShareMode = 0;
		break;
	case shareDenyWrite:
		dwShareMode = FILE_SHARE_READ;
		break;
	case shareDenyRead:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case shareDenyNone:
		dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
		break;
	}

	// Note: typeText and typeBinary are used in derived classes only.

	// map modeNoInherit flag
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;

	// map creation flags
	DWORD dwCreateFlag;
	if (nOpenFlags & modeCreate)
	{
		if (nOpenFlags & modeNoTruncate)
			dwCreateFlag = OPEN_ALWAYS;
		else
			dwCreateFlag = CREATE_ALWAYS;
	}
	else
		dwCreateFlag = OPEN_EXISTING;

	// attempt file creation
	HANDLE hFile = ::CreateFile(lpszFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		throw;
		return FALSE;
	}
	m_hFile = (HFILE)hFile;
	m_bCloseOnDelete = TRUE;

	return TRUE;
}

UINT CFile::Read(void* lpBuf, UINT nCount)
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	if (nCount == 0)
		return 0;   // avoid Win32 "null-read"

	ATLASSERT(lpBuf != NULL);
	ATLASSERT(AfxIsValidAddress(lpBuf, nCount));

	DWORD dwRead;
	if (!::ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL))
		throw;

	return (UINT)dwRead;
}

void CFile::Write(const void* lpBuf, UINT nCount)
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	if (nCount == 0)
		return;     // avoid Win32 "null-write" option

	ATLASSERT(lpBuf != NULL);
	ATLASSERT(AfxIsValidAddress(lpBuf, nCount, FALSE));

	DWORD nWritten;
	if (!::WriteFile((HANDLE)m_hFile, lpBuf, nCount, &nWritten, NULL))
		throw;

	// Win32s will not return an error all the time (usually DISK_FULL)
	if (nWritten != nCount)
		throw;
}

LONG CFile::Seek(LONG lOff, UINT nFrom)
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);
	ATLASSERT(nFrom == begin || nFrom == end || nFrom == current);
	ATLASSERT(begin == FILE_BEGIN && end == FILE_END && current == FILE_CURRENT);

	DWORD dwNew = ::SetFilePointer((HANDLE)m_hFile, lOff, NULL, (DWORD)nFrom);
	if (dwNew  == (DWORD)-1)
		throw;

	return dwNew;
}

DWORD CFile::GetPosition() const
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	DWORD dwPos = ::SetFilePointer((HANDLE)m_hFile, 0, NULL, FILE_CURRENT);
	if (dwPos  == (DWORD)-1)
		throw;

	return dwPos;
}

void CFile::Flush()
{
	ASSERT_VALID(this);

	if (m_hFile == (UINT)hFileNull)
		return;

	if (!::FlushFileBuffers((HANDLE)m_hFile))
		throw;
}

void CFile::Close()
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	BOOL bError = FALSE;
	if (m_hFile != (UINT)hFileNull)
		bError = !::CloseHandle((HANDLE)m_hFile);

	m_hFile = (UINT) hFileNull;
	m_bCloseOnDelete = FALSE;
	m_strFileName.Empty();

	if (bError)
		throw;
}

void CFile::Abort()
{
	ASSERT_VALID(this);
	if (m_hFile != (UINT)hFileNull)
	{
		// close but ignore errors
		::CloseHandle((HANDLE)m_hFile);
		m_hFile = (UINT)hFileNull;
	}
	m_strFileName.Empty();
}

void CFile::LockRange(DWORD dwPos, DWORD dwCount)
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	if (!::LockFile((HANDLE)m_hFile, dwPos, 0, dwCount, 0))
		throw;
}

void CFile::UnlockRange(DWORD dwPos, DWORD dwCount)
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	if (!::UnlockFile((HANDLE)m_hFile, dwPos, 0, dwCount, 0))
		throw;
}

void CFile::SetLength(DWORD dwNewLen)
{
	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	Seek((LONG)dwNewLen, (UINT)begin);

	if (!::SetEndOfFile((HANDLE)m_hFile))
		throw;
}

DWORD CFile::GetLength() const
{
	ASSERT_VALID(this);

	DWORD dwLen, dwCur;

	// Seek is a non const operation
	CFile* pFile = (CFile*)this;
	dwCur = pFile->Seek(0L, current);
	dwLen = pFile->SeekToEnd();
	VERIFY(dwCur == (DWORD)pFile->Seek(dwCur, begin));

	return dwLen;
}

// CFile does not support direct buffering (CMemFile does)
UINT CFile::GetBufferPtr(UINT nCommand, UINT /*nCount*/,
	void** /*ppBufStart*/, void** /*ppBufMax*/)
{
	ATLASSERT(nCommand == bufferCheck);
//	UNUSED(nCommand);    // not used in retail build

	return 0;   // no support
}

void PASCAL CFile::Rename(LPCTSTR lpszOldName, LPCTSTR lpszNewName)
{
	if (!::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName))
		throw;
}

void PASCAL CFile::Remove(LPCTSTR lpszFileName)
{
	if (!::DeleteFile((LPTSTR)lpszFileName))
		throw;
}
