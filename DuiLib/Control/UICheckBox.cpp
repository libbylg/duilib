#include "Control/UICheckBox.h"

namespace DUILIB
{
	LPCTSTR CCheckBoxUI::GetClass() const
	{
		return DUI_CTR_CHECKBOX;
	}

	LPVOID CCheckBoxUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_CHECKBOX) == 0 ) return static_cast<CCheckBoxUI*>(this);
		return COptionUI::GetInterface(pstrName);
	}

	void CCheckBoxUI::SetCheck(BOOL bCheck, BOOL bTriggerEvent)
	{
		Selected(bCheck, bTriggerEvent);
	}

	BOOL  CCheckBoxUI::GetCheck() const
	{
		return IsSelected();
	}
}
