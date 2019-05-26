#ifndef __UIOPTION_H__
#define __UIOPTION_H__

#include "Control/UIButton.h"

namespace DUILIB
{
	class DUILIB_API COptionUI : public CButtonUI
	{
	public:
		COptionUI();
		~COptionUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetManager(CManagerUI* pManager, CControlUI* pParent, BOOL bInit = TRUE);

		BOOL Activate();
		void SetEnabled(BOOL bEnable = TRUE);

		LPCTSTR GetSelectedImage();
		void SetSelectedImage(LPCTSTR pStrImage);

		LPCTSTR GetSelectedHotImage();
		void SetSelectedHotImage(LPCTSTR pStrImage);

		void SetSelectedTextColor(DWORD dwTextColor);
		DWORD GetSelectedTextColor();

		void SetSelectedBkColor(DWORD dwBkColor);
		DWORD GetSelectBkColor();

		LPCTSTR GetForeImage();
		void SetForeImage(LPCTSTR pStrImage);

		LPCTSTR GetGroup() const;
		void SetGroup(LPCTSTR pStrGroupName = NULL);
		BOOL IsSelected() const;
		virtual void Selected(BOOL bSelected, BOOL bTriggerEvent=TRUE);

		SIZE EstimateSize(SIZE szAvailable);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);

	protected:
		BOOL			m_bSelected;
		CStringUI		m_sGroupName;

		DWORD			m_dwSelectedBkColor;
		DWORD			m_dwSelectedTextColor;

		TDRAWINFO_UI		m_diSelected;
		TDRAWINFO_UI		m_diSelectedHot;
		TDRAWINFO_UI		m_diFore;
	};

} // namespace DUILIB

#endif // __UIOPTION_H__