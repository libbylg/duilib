#ifndef __UITILELAYOUT_H__
#define __UITILELAYOUT_H__

#include "Core/UIContainer.h"

namespace DUILIB
{
	class DUILIB_API CTileLayoutUI : public CContainerUI
	{
	public:
		CTileLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);

		int GetFixedColumns() const;
		void SetFixedColumns(int iColums);
		int GetChildVPadding() const;
		void SetChildVPadding(int iPadding);

		SIZE GetItemSize() const;
		void SetItemSize(SIZE szSize);
		int GetColumns() const;
		int GetRows() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		SIZE m_szItem;
		int m_nColumns;
		int m_nRows;

		int m_nColumnsFixed;
		int m_iChildVPadding;
		BOOL m_bIgnoreItemPadding;
	};
}
#endif // __UITILELAYOUT_H__
