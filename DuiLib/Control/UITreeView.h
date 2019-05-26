#ifndef __UITREEVIEW_H__
#define __UITREEVIEW_H__

#include "Control/UIList.h"
#include "Core/UIManager.h"

namespace DUILIB
{
	class CTreeViewUI;
	class CCheckBoxUI;
	class CLabelUI;
	class COptionUI;

	class DUILIB_API CTreeNodeUI : public CListContainerElementUI
	{
	public:
		CTreeNodeUI(CTreeNodeUI* _ParentNode = NULL);
		~CTreeNodeUI(void);

	public:
		LPCTSTR GetClass() const;
		LPVOID	GetInterface(LPCTSTR pstrName);
		void	DoEvent(TEVENT_UI& event);
		void	Invalidate();
		BOOL	Select(BOOL bSelect = TRUE, BOOL bTriggerEvent=TRUE);

		BOOL	Add(CControlUI* _pTreeNodeUI);
		BOOL	AddAt(CControlUI* pControl, int iIndex);

		void	SetVisibleTag(BOOL _IsVisible);
		BOOL	GetVisibleTag();
		void	SetItemText(LPCTSTR pstrValue);
		CStringUI	GetItemText();
		void	CheckBoxSelected(BOOL _Selected);
		BOOL	IsCheckBoxSelected() const;
		BOOL	IsHasChild() const;
		long	GetTreeLevel() const;
		BOOL	AddChildNode(CTreeNodeUI* _pTreeNodeUI);
		BOOL	RemoveAt(CTreeNodeUI* _pTreeNodeUI);
		void	SetParentNode(CTreeNodeUI* _pParentTreeNode);
		CTreeNodeUI* GetParentNode();
		long	GetCountChild();
		void	SetTreeView(CTreeViewUI* _CTreeViewUI);
		CTreeViewUI* GetTreeView();
		CTreeNodeUI* GetChildNode(int _nIndex);
		void	SetVisibleFolderBtn(BOOL _IsVisibled);
		BOOL	GetVisibleFolderBtn();
		void	SetVisibleCheckBtn(BOOL _IsVisibled);
		BOOL	GetVisibleCheckBtn();
		void	SetItemTextColor(DWORD _dwItemTextColor);
		DWORD	GetItemTextColor() const;
		void	SetItemHotTextColor(DWORD _dwItemHotTextColor);
		DWORD	GetItemHotTextColor() const;
		void	SetSelItemTextColor(DWORD _dwSelItemTextColor);
		DWORD	GetSelItemTextColor() const;
		void	SetSelItemHotTextColor(DWORD _dwSelHotItemTextColor);
		DWORD	GetSelItemHotTextColor() const;

		void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		CPtrArrayUI GetTreeNodes();

		int			 GetTreeIndex();
		int			 GetNodeIndex();

	private:
		CTreeNodeUI* GetLastNode();
		CTreeNodeUI* CalLocation(CTreeNodeUI* _pTreeNodeUI);
	public:
		CHorizontalLayoutUI*	GetTreeNodeHoriznotal() const {return pHoriz;};
		CCheckBoxUI*			GetFolderButton() const {return pFolderButton;};
		CLabelUI*				GetDottedLine() const {return pDottedLine;};
		CCheckBoxUI*			GetCheckBox() const {return pCheckBox;};
		COptionUI*				GetItemButton() const {return pItemButton;};

	private:
		long	m_iTreeLavel;
		BOOL	m_bIsVisable;
		BOOL	m_bIsCheckBox;
		DWORD	m_dwItemTextColor;
		DWORD	m_dwItemHotTextColor;
		DWORD	m_dwSelItemTextColor;
		DWORD	m_dwSelItemHotTextColor;

		CTreeViewUI*			pTreeView;
		CHorizontalLayoutUI*	pHoriz;
		CCheckBoxUI*			pFolderButton;
		CLabelUI*				pDottedLine;
		CCheckBoxUI*			pCheckBox;
		COptionUI*				pItemButton;

		CTreeNodeUI*			pParentTreeNode;

		CPtrArrayUI			mTreeNodes;
	};

	class DUILIB_API CTreeViewUI : public CListUI,public INotifyUI
	{
	public:
		CTreeViewUI(void);
		~CTreeViewUI(void);

	public:
		virtual LPCTSTR GetClass() const;
		virtual LPVOID	GetInterface(LPCTSTR pstrName);
        virtual BOOL Add(CControlUI* pControl);
        virtual BOOL AddAt(CControlUI* pControl, int iIndex);
        virtual BOOL Remove(CControlUI* pControl, BOOL bDoNotDestroy=FALSE);
        virtual BOOL RemoveAt(int iIndex, BOOL bDoNotDestroy=FALSE);
        virtual void RemoveAll();

        long AddAt(CTreeNodeUI* pControl, int iIndex);
        BOOL AddAt(CTreeNodeUI* pControl,CTreeNodeUI* _IndexNode);

		virtual BOOL OnCheckBoxChanged(void* param);
		virtual BOOL OnFolderChanged(void* param);
		virtual BOOL OnDBClickItem(void* param);
		virtual BOOL SetItemCheckBox(BOOL _Selected,CTreeNodeUI* _TreeNode = NULL);
		virtual void SetItemExpand(BOOL _Expanded,CTreeNodeUI* _TreeNode = NULL);
		virtual void Notify(TNOTIFY_UI& msg);
		virtual void SetVisibleFolderBtn(BOOL _IsVisibled);
		virtual BOOL GetVisibleFolderBtn();
		virtual void SetVisibleCheckBtn(BOOL _IsVisibled);
		virtual BOOL GetVisibleCheckBtn();
		virtual void SetItemMinWidth(UINT _ItemMinWidth);
		virtual UINT GetItemMinWidth();
		virtual void SetItemTextColor(DWORD _dwItemTextColor);
		virtual void SetItemHotTextColor(DWORD _dwItemHotTextColor);
		virtual void SetSelItemTextColor(DWORD _dwSelItemTextColor);
		virtual void SetSelItemHotTextColor(DWORD _dwSelHotItemTextColor);
		
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	private:
		UINT m_uItemMinWidth;
		BOOL m_bVisibleFolderBtn;
		BOOL m_bVisibleCheckBtn;
	};
}


#endif // __UITREEVIEW_H__
