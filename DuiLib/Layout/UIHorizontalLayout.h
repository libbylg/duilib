#ifndef __UIHORIZONTALLAYOUT_H__
#define __UIHORIZONTALLAYOUT_H__

#include "Core/UIContainer.h"

namespace DUILIB
{
	class DUILIB_API CHorizontalLayoutUI : public CContainerUI
	{
	public:
		CHorizontalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepWidth(int iWidth);
		int GetSepWidth() const;
		void SetSepImmMode(BOOL bImmediately);
		BOOL IsSepImmMode() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TEVENT_UI& event);

		void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
		void DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(BOOL bUseNew = FALSE) const;

	protected:
		int m_iSepWidth;
		UINT m_uButtonState;
		POINT m_ptLastMouse;
		RECT m_rcNewPos;
		BOOL m_bImmMode;
	};
}
#endif // __UIHORIZONTALLAYOUT_H__
