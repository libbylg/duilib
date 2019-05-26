#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "Control/UIProgress.h"

namespace DUILIB
{
	class DUILIB_API CSliderUI : public CProgressUI
	{
	public:
		CSliderUI();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetEnabled(BOOL bEnable = TRUE);

		int GetChangeStep();
		void SetChangeStep(int step);
		void SetThumbSize(SIZE szXY);
		RECT GetThumbRect() const;
		BOOL IsImmMode() const;
		void SetImmMode(BOOL bImmMode);
		LPCTSTR GetThumbImage() const;
		void SetThumbImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbHotImage() const;
		void SetThumbHotImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbPushedImage() const;
		void SetThumbPushedImage(LPCTSTR pStrImage);

		void DoEvent(TEVENT_UI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintStatusImage(HDC hDC);

	protected:
		SIZE m_szThumb;
		UINT m_uButtonState;
		int m_nStep;
		BOOL m_bImmMode;

		TDRAWINFO_UI m_diThumb;
		TDRAWINFO_UI m_diThumbHot;
		TDRAWINFO_UI m_diThumbPushed;
	};
}

#endif // __UISLIDER_H__