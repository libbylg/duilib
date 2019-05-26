#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#include "Control/UILabel.h"

namespace DUILIB
{
	class CDateTimeWnd;

	/// 时间选择控件
	class DUILIB_API CDateTimeUI : public CLabelUI
	{
		friend class CDateTimeWnd;
	public:
		CDateTimeUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);

		void SetReadOnly(BOOL bReadOnly);
		BOOL IsReadOnly() const;

		void UpdateText();

        void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        void Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);

		void DoEvent(TEVENT_UI& event);

	protected:
		SYSTEMTIME m_sysTime;
		int        m_nDTUpdateFlag;
		BOOL       m_bReadOnly;

		CDateTimeWnd* m_pWindow;
	};
}
#endif // __UIDATETIME_H__