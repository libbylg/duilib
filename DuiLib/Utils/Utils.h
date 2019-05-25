#ifndef __UTILS_H__
#define __UTILS_H__

#include "DUILIB.h"

namespace DUILIB
{
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUILIB_API STRINGorID
	{
	public:
		STRINGorID(LPCTSTR lpString);
		STRINGorID(unsigned int nID);

		LPCTSTR m_lpstr;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
    class CStringUI;
	class DUILIB_API CPointUI : public tagPOINT
	{
	public:
		CPointUI();
		CPointUI(const POINT& src);
		CPointUI(long x, long y);
		CPointUI(LPARAM lParam);
        CPointUI(LPCTSTR pstrValue);
        CStringUI ToString();
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUILIB_API CSizeUI : public tagSIZE
	{
	public:
		CSizeUI();
		CSizeUI(const SIZE& src);
		CSizeUI(const RECT rc);
		CSizeUI(long cx, long cy);
        CSizeUI(LPCTSTR pstrValue);
        CStringUI ToString();
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUILIB_API CRectUI : public tagRECT
	{
	public:
		CRectUI();
		CRectUI(const RECT& src);
		CRectUI(long iLeft, long iTop, long iRight, long iBottom);
        CRectUI(LPCTSTR pstrValue);
        CStringUI ToString();

		int GetWidth() const;
		int GetHeight() const;
		void Empty();
		bool IsNull() const;
		void Join(const RECT& rc);
		void ResetOffset();
		void Normalize();
		void Offset(int cx, int cy);
		void Inflate(int cx, int cy);
		void Deflate(int cx, int cy);
		void Union(CRectUI& rc);
	};

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CStringUI
    {
    public:
        enum { MAX_LOCAL_STRING_LEN = 63 };

        CStringUI();
        CStringUI(const TCHAR ch);
        CStringUI(const CStringUI& src);
        CStringUI(LPCTSTR lpsz, int nLen = -1);
        ~CStringUI();
        CStringUI ToString();

        void Empty();
        int GetLength() const;
        bool IsEmpty() const;
        TCHAR GetAt(int nIndex) const;
        void Append(LPCTSTR pstr);
        void Assign(LPCTSTR pstr, int nLength = -1);
        LPCTSTR GetData() const;

        void SetAt(int nIndex, TCHAR ch);
        operator LPCTSTR() const;

        TCHAR operator[] (int nIndex) const;
        const CStringUI& operator=(const CStringUI& src);
        const CStringUI& operator=(const TCHAR ch);
        const CStringUI& operator=(LPCTSTR pstr);
#ifdef _UNICODE
        const CStringUI& operator=(LPCSTR lpStr);
        const CStringUI& operator+=(LPCSTR lpStr);
#else
        const CStringUI& operator=(LPCWSTR lpwStr);
        const CStringUI& operator+=(LPCWSTR lpwStr);
#endif
        CStringUI operator+(const CStringUI& src) const;
        CStringUI operator+(LPCTSTR pstr) const;
        const CStringUI& operator+=(const CStringUI& src);
        const CStringUI& operator+=(LPCTSTR pstr);
        const CStringUI& operator+=(const TCHAR ch);

        bool operator == (LPCTSTR str) const;
        bool operator != (LPCTSTR str) const;
        bool operator <= (LPCTSTR str) const;
        bool operator <  (LPCTSTR str) const;
        bool operator >= (LPCTSTR str) const;
        bool operator >  (LPCTSTR str) const;

        int Compare(LPCTSTR pstr) const;
        int CompareNoCase(LPCTSTR pstr) const;

        void MakeUpper();
        void MakeLower();

        CStringUI Left(int nLength) const;
        CStringUI Mid(int iPos, int nLength = -1) const;
        CStringUI Right(int nLength) const;

        int Find(TCHAR ch, int iPos = 0) const;
        int Find(LPCTSTR pstr, int iPos = 0) const;
        int ReverseFind(TCHAR ch) const;
        int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

        int __cdecl Format(LPCTSTR pstrFormat, ...);
        int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

    protected:
        LPTSTR m_pstr;
        TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
    };

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUILIB_API CPtrArrayUI
	{
	public:
		CPtrArrayUI(int iPreallocSize = 0);
		CPtrArrayUI(const CPtrArrayUI& src);
		~CPtrArrayUI();

		void Empty();
		void Resize(int iSize);
		bool IsEmpty() const;
		int Find(LPVOID iIndex) const;
		bool Add(LPVOID pData);
		bool SetAt(int iIndex, LPVOID pData);
		bool InsertAt(int iIndex, LPVOID pData);
		bool Remove(int iIndex, int iCount = 1);
		int GetSize() const;
		LPVOID* GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPVOID* m_ppVoid;
		int m_nCount;
		int m_nAllocated;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUILIB_API CValArrayUI
	{
	public:
		CValArrayUI(int iElementSize, int iPreallocSize = 0);
		~CValArrayUI();

		void Empty();
		bool IsEmpty() const;
		bool Add(LPCVOID pData);
		bool Remove(int iIndex,  int iCount = 1);
		int GetSize() const;
		LPVOID GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPBYTE m_pVoid;
		int m_iElementSize;
		int m_nCount;
		int m_nAllocated;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

    struct TITEM;
	class DUILIB_API CStringPtrMapUI
	{
	public:
		CStringPtrMapUI(int nSize = 83);
		~CStringPtrMapUI();

		void Resize(int nSize = 83);
		LPVOID Find(LPCTSTR key, bool optimize = true) const;
		bool Insert(LPCTSTR key, LPVOID pData);
		LPVOID Set(LPCTSTR key, LPVOID pData);
		bool Remove(LPCTSTR key);
		void RemoveAll();
		int GetSize() const;
		LPCTSTR GetAt(int iIndex) const;
		LPCTSTR operator[] (int nIndex) const;

	protected:
		TITEM** m_aT;
		int m_nBuckets;
		int m_nCount;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUILIB_API CWaitCursorUI
	{
	public:
		CWaitCursorUI();
		~CWaitCursorUI();

	protected:
		HCURSOR m_hOrigCursor;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CVariantUI : public VARIANT
	{
	public:
		CVariantUI() 
		{ 
			VariantInit(this); 
		}
		CVariantUI(int i)
		{
			VariantInit(this);
			this->vt = VT_I4;
			this->intVal = i;
		}
		CVariantUI(float f)
		{
			VariantInit(this);
			this->vt = VT_R4;
			this->fltVal = f;
		}
		CVariantUI(LPOLESTR s)
		{
			VariantInit(this);
			this->vt = VT_BSTR;
			this->bstrVal = s;
		}
		CVariantUI(IDispatch *disp)
		{
			VariantInit(this);
			this->vt = VT_DISPATCH;
			this->pdispVal = disp;
		}

		~CVariantUI() 
		{ 
			VariantClear(this); 
		}
	};

}// namespace DUILIB

#endif // __UTILS_H__