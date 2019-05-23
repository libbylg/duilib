#ifndef __UIVERTICALLAYOUT_H__
#define __UIVERTICALLAYOUT_H__


#include "Core/UIContainer.h"


namespace DUILIB
{
	class DUILIB_API CVerticalLayoutUI : public CContainerUI
	{
	public:
		CVerticalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepHeight(int iHeight);
		int GetSepHeight() const;
		void SetSepImmMode(bool bImmediately);
		bool IsSepImmMode() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TEVENT_UI& event);

		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(bool bUseNew = false) const;

	protected:
		int m_iSepHeight;
		UINT m_uButtonState;
		POINT m_ptLastMouse;
		RECT m_rcNewPos;
		bool m_bImmMode;
	};
}
#endif // __UIVERTICALLAYOUT_H__
