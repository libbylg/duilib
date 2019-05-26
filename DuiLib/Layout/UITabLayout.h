#ifndef __UITABLAYOUT_H__
#define __UITABLAYOUT_H__

#include "Core/UIContainer.h"

namespace DUILIB
{
	class DUILIB_API CTabLayoutUI : public CContainerUI
	{
	public:
		CTabLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		BOOL Add(CControlUI* pControl);
		BOOL AddAt(CControlUI* pControl, int iIndex);
		BOOL Remove(CControlUI* pControl, BOOL bDoNotDestroy=FALSE);
		void RemoveAll();
		int GetCurSel() const;
		BOOL SelectItem(int iIndex, BOOL bTriggerEvent=TRUE);
		BOOL SelectItem(CControlUI* pControl,  BOOL bTriggerEvent=TRUE);

		void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		int m_iCurSel;
	};
}
#endif // __UITABLAYOUT_H__
