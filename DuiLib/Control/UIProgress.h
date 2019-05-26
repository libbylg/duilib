#ifndef __UIPROGRESS_H__
#define __UIPROGRESS_H__

#include "Control/UILabel.h"

namespace DUILIB
{
	class DUILIB_API CProgressUI : public CLabelUI
	{
	public:
		CProgressUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		BOOL IsHorizontal();
		void SetHorizontal(BOOL bHorizontal = TRUE);
		int GetMinValue() const;
		void SetMinValue(int nMin);
		int GetMaxValue() const;
		void SetMaxValue(int nMax);
		int GetValue() const;
		void SetValue(int nValue);
		LPCTSTR GetForeImage() const;
		void SetForeImage(LPCTSTR pStrImage);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintStatusImage(HDC hDC);

	protected:
		BOOL m_bHorizontal;
		int m_nMax;
		int m_nMin;
		int m_nValue;

		TDRAWINFO_UI m_diFore;
	};

} // namespace DUILIB

#endif // __UIPROGRESS_H__
