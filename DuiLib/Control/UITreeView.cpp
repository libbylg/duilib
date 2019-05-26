#include "Control/UITreeView.h"
#include "Control/UICheckBox.h"
#include "Control/UILabel.h"
#include "Control/UIOption.h"

#include "Core/UIManager.h"
#include "Core/UIScroll.h"

#pragma warning( disable: 4251 )
namespace DUILIB
{
	//************************************
	// 函数名称: CTreeNodeUI
	// 返回类型: 
	// 参数信息: CTreeNodeUI * _ParentNode
	// 函数说明: 
	//************************************
	CTreeNodeUI::CTreeNodeUI( CTreeNodeUI* _ParentNode /*= NULL*/ )
	{
		m_dwItemTextColor		= 0x00000000;
		m_dwItemHotTextColor	= 0;
		m_dwSelItemTextColor	= 0;
		m_dwSelItemHotTextColor	= 0;

		pTreeView		= NULL;
		m_bIsVisable	= TRUE;
		m_bIsCheckBox	= FALSE;
		pParentTreeNode	= NULL;

		pHoriz			= new CHorizontalLayoutUI();
		pFolderButton	= new CCheckBoxUI();
		pDottedLine		= new CLabelUI();
		pCheckBox		= new CCheckBoxUI();
		pItemButton		= new COptionUI();

		this->SetFixedHeight(18);
		this->SetFixedWidth(250);
		pFolderButton->SetFixedWidth(GetFixedHeight());
		pDottedLine->SetFixedWidth(2);
		pCheckBox->SetFixedWidth(GetFixedHeight());
		pItemButton->SetAttribute(_T("align"),_T("left"));

		pDottedLine->SetVisible(FALSE);
		pCheckBox->SetVisible(FALSE);
		pItemButton->SetMouseEnabled(FALSE);

		if(_ParentNode)
		{
			if (_tcsicmp(_ParentNode->GetClass(), DUI_CTR_TREENODE) != 0)
				return;

			pDottedLine->SetVisible(_ParentNode->IsVisible());
			pDottedLine->SetFixedWidth(_ParentNode->GetDottedLine()->GetFixedWidth()+16);
			this->SetParentNode(_ParentNode);
		}

		pHoriz->Add(pDottedLine);
		pHoriz->Add(pFolderButton);
		pHoriz->Add(pCheckBox);
		pHoriz->Add(pItemButton);
		Add(pHoriz);
	}
	
	//************************************
	// 函数名称: ~CTreeNodeUI
	// 返回类型: 
	// 参数信息: void
	// 函数说明: 
	//************************************
	CTreeNodeUI::~CTreeNodeUI( void )
	{

	}

	//************************************
	// 函数名称: GetClass
	// 返回类型: LPCTSTR
	// 函数说明: 
	//************************************
	LPCTSTR CTreeNodeUI::GetClass() const
	{
		return DUI_CTR_TREENODE;
	}

	//************************************
	// 函数名称: GetInterface
	// 返回类型: LPVOID
	// 参数信息: LPCTSTR pstrName
	// 函数说明: 
	//************************************
	LPVOID CTreeNodeUI::GetInterface( LPCTSTR pstrName )
	{
		if( _tcscmp(pstrName, DUI_CTR_TREENODE) == 0 ) return static_cast<CTreeNodeUI*>(this);
		return CListContainerElementUI::GetInterface(pstrName);
	}
	
	//************************************
	// 函数名称: DoEvent
	// 返回类型: void
	// 参数信息: TEVENT_UI & event
	// 函数说明:
	//************************************
	void CTreeNodeUI::DoEvent( TEVENT_UI& event )
	{
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pOwner != NULL ) m_pOwner->DoEvent(event);
			else CContainerUI::DoEvent(event);
			return;
		}

		CListContainerElementUI::DoEvent(event);

		if( event.Type == UIEVENT_DBLCLICK )
		{
			if( IsEnabled() ) {
				m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMDBCLICK);
				Invalidate();
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSEENTER )
		{
			if( IsEnabled()) {
				if(m_bSelected && GetSelItemHotTextColor())
					pItemButton->SetTextColor(GetSelItemHotTextColor());
				else
					pItemButton->SetTextColor(GetItemHotTextColor());
			}
			else 
				pItemButton->SetTextColor(pItemButton->GetDisabledTextColor());

			//return;
		}
		if( event.Type == UIEVENT_MOUSELEAVE )
		{
			if( IsEnabled()) {
				if(m_bSelected && GetSelItemTextColor())
					pItemButton->SetTextColor(GetSelItemTextColor());
				else if(!m_bSelected)
					pItemButton->SetTextColor(GetItemTextColor());
			}
			else 
				pItemButton->SetTextColor(pItemButton->GetDisabledTextColor());

			//return;
		}
	}

	//************************************
	// 函数名称: Invalidate
	// 返回类型: void
	// 函数说明: 
	//************************************
	void CTreeNodeUI::Invalidate()
	{
		if( !IsVisible() )
			return;

		if( GetParent() ) {
			CContainerUI* pParentContainer = static_cast<CContainerUI*>(GetParent()->GetInterface(DUI_CTR_CONTAINER));
			if( pParentContainer ) {
				RECT rc = pParentContainer->GetPos();
				RECT rcInset = pParentContainer->GetInset();
				rc.left += rcInset.left;
				rc.top += rcInset.top;
				rc.right -= rcInset.right;
				rc.bottom -= rcInset.bottom;
				CScrollUI* pVerticalScrollBar = pParentContainer->GetVerticalScrollBar();
				if( pVerticalScrollBar && pVerticalScrollBar->IsVisible() ) rc.right -= pVerticalScrollBar->GetFixedWidth();
				CScrollUI* pHorizontalScrollBar = pParentContainer->GetHorizontalScrollBar();
				if( pHorizontalScrollBar && pHorizontalScrollBar->IsVisible() ) rc.bottom -= pHorizontalScrollBar->GetFixedHeight();

				RECT invalidateRc = m_rcItem;
				if( !::IntersectRect(&invalidateRc, &m_rcItem, &rc) ) 
					return;

				CControlUI* pParent = GetParent();
				RECT rcTemp;
				RECT rcParent;
				while( pParent = pParent->GetParent() )
				{
					rcTemp = invalidateRc;
					rcParent = pParent->GetPos();
					if( !::IntersectRect(&invalidateRc, &rcTemp, &rcParent) ) 
						return;
				}

				if( m_pManager != NULL ) m_pManager->Invalidate(invalidateRc);
			}
			else {
				CContainerUI::Invalidate();
			}
		}
		else {
			CContainerUI::Invalidate();
		}
	}
	
	//************************************
	// 函数名称: Select
	// 返回类型: BOOL
	// 参数信息: BOOL bSelect
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::Select( BOOL bSelect /*= TRUE*/,  BOOL bTriggerEvent)
	{
		BOOL nRet = CListContainerElementUI::Select(bSelect, bTriggerEvent);
		if(m_bSelected)
			pItemButton->SetTextColor(GetSelItemTextColor());
		else 
			pItemButton->SetTextColor(GetItemTextColor());

		return nRet;
	}

	//************************************
	// 函数名称: Add
	// 返回类型: BOOL
	// 参数信息: CControlUI * _pTreeNodeUI
	// 函数说明: 通过节点对象添加节点
	//************************************
	BOOL CTreeNodeUI::Add( CControlUI* _pTreeNodeUI )
	{
		if (_tcsicmp(_pTreeNodeUI->GetClass(), DUI_CTR_TREENODE) == 0)
			return AddChildNode((CTreeNodeUI*)_pTreeNodeUI);

		return CListContainerElementUI::Add(_pTreeNodeUI);
	}

	//************************************
	// 函数名称: AddAt
	// 返回类型: BOOL
	// 参数信息: CControlUI * pControl
	// 参数信息: int iIndex				该参数仅针对当前节点下的兄弟索引，并非列表视图索引
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::AddAt( CControlUI* pControl, int iIndex )
	{
		if(NULL == static_cast<CTreeNodeUI*>(pControl->GetInterface(DUI_CTR_TREENODE)))
			return FALSE;

		CTreeNodeUI* pIndexNode = static_cast<CTreeNodeUI*>(mTreeNodes.GetAt(iIndex));
		if(!pIndexNode){
			if(!mTreeNodes.Add(pControl))
				return FALSE;
		}
		else if(pIndexNode && !mTreeNodes.InsertAt(iIndex,pControl))
			return FALSE;

		if(!pIndexNode && pTreeView && pTreeView->GetItemAt(GetTreeIndex()+1))
			pIndexNode = static_cast<CTreeNodeUI*>(pTreeView->GetItemAt(GetTreeIndex()+1)->GetInterface(DUI_CTR_TREENODE));

		pControl = CalLocation((CTreeNodeUI*)pControl);

		if(pTreeView && pIndexNode)
			return pTreeView->AddAt((CTreeNodeUI*)pControl,pIndexNode);
		else 
			return pTreeView->Add((CTreeNodeUI*)pControl);

		return TRUE;
	}

	//************************************
	// 函数名称: SetVisibleTag
	// 返回类型: void
	// 参数信息: BOOL _IsVisible
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetVisibleTag( BOOL _IsVisible )
	{
		m_bIsVisable = _IsVisible;
	}

	//************************************
	// 函数名称: GetVisibleTag
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::GetVisibleTag()
	{
		return m_bIsVisable;
	}

	//************************************
	// 函数名称: SetItemText
	// 返回类型: void
	// 参数信息: LPCTSTR pstrValue
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetItemText( LPCTSTR pstrValue )
	{
		pItemButton->SetText(pstrValue);
	}

	//************************************
	// 函数名称: GetItemText
	// 返回类型: UiLib::CStringUI
	// 函数说明: 
	//************************************
	CStringUI CTreeNodeUI::GetItemText()
	{
		return pItemButton->GetText();
	}

	//************************************
	// 函数名称: CheckBoxSelected
	// 返回类型: void
	// 参数信息: BOOL _Selected
	// 函数说明: 
	//************************************
	void CTreeNodeUI::CheckBoxSelected( BOOL _Selected )
	{
		pCheckBox->Selected(_Selected);
	}

	//************************************
	// 函数名称: IsCheckBoxSelected
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::IsCheckBoxSelected() const
	{
		return pCheckBox->IsSelected();
	}

	//************************************
	// 函数名称: IsHasChild
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::IsHasChild() const
	{
		return !mTreeNodes.IsEmpty();
	}
	
	//************************************
	// 函数名称: AddChildNode
	// 返回类型: BOOL
	// 参数信息: CTreeNodeUI * _pTreeNodeUI
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::AddChildNode( CTreeNodeUI* _pTreeNodeUI )
	{
		if (!_pTreeNodeUI)
			return FALSE;

		if (_tcsicmp(_pTreeNodeUI->GetClass(), DUI_CTR_TREENODE) != 0)
			return FALSE;

		_pTreeNodeUI = CalLocation(_pTreeNodeUI);

		BOOL nRet = TRUE;

		if(pTreeView){
			CTreeNodeUI* pNode = static_cast<CTreeNodeUI*>(mTreeNodes.GetAt(mTreeNodes.GetSize()-1));
			if(!pNode || !pNode->GetLastNode())
				nRet = pTreeView->AddAt(_pTreeNodeUI,GetTreeIndex()+1) >= 0;
			else nRet = pTreeView->AddAt(_pTreeNodeUI,pNode->GetLastNode()->GetTreeIndex()+1) >= 0;
		}

		if(nRet)
			mTreeNodes.Add(_pTreeNodeUI);

		return nRet;
	}

	//************************************
	// 函数名称: RemoveAt
	// 返回类型: BOOL
	// 参数信息: CTreeNodeUI * _pTreeNodeUI
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::RemoveAt( CTreeNodeUI* _pTreeNodeUI )
	{
		int nIndex = mTreeNodes.Find(_pTreeNodeUI);
		CTreeNodeUI* pNode = static_cast<CTreeNodeUI*>(mTreeNodes.GetAt(nIndex));
		if(pNode && pNode == _pTreeNodeUI)
		{
			while(pNode->IsHasChild())
				pNode->RemoveAt(static_cast<CTreeNodeUI*>(pNode->mTreeNodes.GetAt(0)));

			mTreeNodes.Remove(nIndex);

			if(pTreeView)
				pTreeView->Remove(_pTreeNodeUI);

			return TRUE;
		}
		return FALSE;
	}

	//************************************
	// 函数名称: SetParentNode
	// 返回类型: void
	// 参数信息: CTreeNodeUI * _pParentTreeNode
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetParentNode( CTreeNodeUI* _pParentTreeNode )
	{
		pParentTreeNode = _pParentTreeNode;
	}

	//************************************
	// 函数名称: GetParentNode
	// 返回类型: CTreeNodeUI*
	// 函数说明: 
	//************************************
	CTreeNodeUI* CTreeNodeUI::GetParentNode()
	{
		return pParentTreeNode;
	}

	//************************************
	// 函数名称: GetCountChild
	// 返回类型: long
	// 函数说明: 
	//************************************
	long CTreeNodeUI::GetCountChild()
	{
		return mTreeNodes.GetSize();
	}

	//************************************
	// 函数名称: SetTreeView
	// 返回类型: void
	// 参数信息: CTreeViewUI * _CTreeViewUI
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetTreeView( CTreeViewUI* _CTreeViewUI )
	{
		pTreeView = _CTreeViewUI;
	}

	//************************************
	// 函数名称: GetTreeView
	// 返回类型: CTreeViewUI*
	// 函数说明: 
	//************************************
	CTreeViewUI* CTreeNodeUI::GetTreeView()
	{
		return pTreeView;
	}

	//************************************
	// 函数名称: SetAttribute
	// 返回类型: void
	// 参数信息: LPCTSTR pstrName
	// 参数信息: LPCTSTR pstrValue
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if(_tcscmp(pstrName, _T("text")) == 0 )
			pItemButton->SetText(pstrValue);
		else if(_tcscmp(pstrName, _T("horizattr")) == 0 )
			pHoriz->SetAttributeList(pstrValue);
		else if(_tcscmp(pstrName, _T("dotlineattr")) == 0 )
			pDottedLine->SetAttributeList(pstrValue);
		else if(_tcscmp(pstrName, _T("folderattr")) == 0 )
			pFolderButton->SetAttributeList(pstrValue);
		else if(_tcscmp(pstrName, _T("checkboxattr")) == 0 )
			pCheckBox->SetAttributeList(pstrValue);
		else if(_tcscmp(pstrName, _T("itemattr")) == 0 )
			pItemButton->SetAttributeList(pstrValue);
		else if(_tcscmp(pstrName, _T("itemtextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetItemTextColor(clrColor);
		}
		else if(_tcscmp(pstrName, _T("itemhottextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetItemHotTextColor(clrColor);
		}
		else if(_tcscmp(pstrName, _T("selitemtextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetSelItemTextColor(clrColor);
		}
		else if(_tcscmp(pstrName, _T("selitemhottextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetSelItemHotTextColor(clrColor);
		}
		else CListContainerElementUI::SetAttribute(pstrName,pstrValue);
	}

	//************************************
	// 函数名称: GetTreeNodes
	// 返回类型: UiLib::CPtrArrayUI
	// 函数说明: 
	//************************************
	CPtrArrayUI CTreeNodeUI::GetTreeNodes()
	{
		return mTreeNodes;
	}

	//************************************
	// 函数名称: GetChildNode
	// 返回类型: CTreeNodeUI*
	// 参数信息: int _nIndex
	// 函数说明: 
	//************************************
	CTreeNodeUI* CTreeNodeUI::GetChildNode( int _nIndex )
	{
		return static_cast<CTreeNodeUI*>(mTreeNodes.GetAt(_nIndex));
	}

	//************************************
	// 函数名称: SetVisibleFolderBtn
	// 返回类型: void
	// 参数信息: BOOL _IsVisibled
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetVisibleFolderBtn( BOOL _IsVisibled )
	{
		pFolderButton->SetVisible(_IsVisibled);
	}

	//************************************
	// 函数名称: GetVisibleFolderBtn
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::GetVisibleFolderBtn()
	{
		return pFolderButton->IsVisible();
	}

	//************************************
	// 函数名称: SetVisibleCheckBtn
	// 返回类型: void
	// 参数信息: BOOL _IsVisibled
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetVisibleCheckBtn( BOOL _IsVisibled )
	{
		pCheckBox->SetVisible(_IsVisibled);
	}

	//************************************
	// 函数名称: GetVisibleCheckBtn
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeNodeUI::GetVisibleCheckBtn()
	{
		return pCheckBox->IsVisible();
	}
	
	//************************************
	// 函数名称: GetNodeIndex
	// 返回类型: int
	// 函数说明: 取得全局树视图的索引
	//************************************
	int CTreeNodeUI::GetTreeIndex()
	{
		if(!pTreeView)
			return -1;

		for(int nIndex = 0;nIndex < pTreeView->GetCount();nIndex++){
			if(this == pTreeView->GetItemAt(nIndex))
				return nIndex;
		}

		return -1;
	}
	
	//************************************
	// 函数名称: GetNodeIndex
	// 返回类型: int
	// 函数说明: 取得相对于兄弟节点的当前索引
	//************************************
	int CTreeNodeUI::GetNodeIndex()
	{
		if(!GetParentNode() && !pTreeView)
			return -1;

		if(!GetParentNode() && pTreeView)
			return GetTreeIndex();

		return GetParentNode()->GetTreeNodes().Find(this);
	}

	//************************************
	// 函数名称: GetLastNode
	// 返回类型: CTreeNodeUI*
	// 函数说明:
	//************************************
	CTreeNodeUI* CTreeNodeUI::GetLastNode( )
	{
		if(!IsHasChild())
			return this;

		CTreeNodeUI* nRetNode = NULL;

		for(int nIndex = 0;nIndex < GetTreeNodes().GetSize();nIndex++){
			CTreeNodeUI* pNode = static_cast<CTreeNodeUI*>(GetTreeNodes().GetAt(nIndex));
			if(!pNode)
				continue;

			CStringUI aa = pNode->GetItemText();

			if(pNode->IsHasChild())
				nRetNode = pNode->GetLastNode();
			else 
				nRetNode = pNode;
		}
		
		return nRetNode;
	}
	
	//************************************
	// 函数名称: CalLocation
	// 返回类型: CTreeNodeUI*
	// 参数信息: CTreeNodeUI * _pTreeNodeUI
	// 函数说明: 缩进计算
	//************************************
	CTreeNodeUI* CTreeNodeUI::CalLocation( CTreeNodeUI* _pTreeNodeUI )
	{
		_pTreeNodeUI->GetDottedLine()->SetVisible(TRUE);
		_pTreeNodeUI->GetDottedLine()->SetFixedWidth(pDottedLine->GetFixedWidth()+16);
		_pTreeNodeUI->SetParentNode(this);
		_pTreeNodeUI->GetItemButton()->SetGroup(pItemButton->GetGroup());
		_pTreeNodeUI->SetTreeView(pTreeView);

		return _pTreeNodeUI;
	}

	//************************************
	// 函数名称: SetTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwTextColor
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetItemTextColor( DWORD _dwItemTextColor )
	{
		m_dwItemTextColor	= _dwItemTextColor;
		pItemButton->SetTextColor(m_dwItemTextColor);
	}

	//************************************
	// 函数名称: GetTextColor
	// 返回类型: DWORD
	// 函数说明: 
	//************************************
	DWORD CTreeNodeUI::GetItemTextColor() const
	{
		return m_dwItemTextColor;
	}

	//************************************
	// 函数名称: SetTextHotColor
	// 返回类型: void
	// 参数信息: DWORD _dwTextHotColor
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetItemHotTextColor( DWORD _dwItemHotTextColor )
	{
		m_dwItemHotTextColor = _dwItemHotTextColor;
		Invalidate();
	}

	//************************************
	// 函数名称: GetTextHotColor
	// 返回类型: DWORD
	// 函数说明: 
	//************************************
	DWORD CTreeNodeUI::GetItemHotTextColor() const
	{
		return m_dwItemHotTextColor;
	}

	//************************************
	// 函数名称: SetSelItemTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwSelItemTextColor
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetSelItemTextColor( DWORD _dwSelItemTextColor )
	{
		m_dwSelItemTextColor = _dwSelItemTextColor;
		Invalidate();
	}

	//************************************
	// 函数名称: GetSelItemTextColor
	// 返回类型: DWORD
	// 函数说明: 
	//************************************
	DWORD CTreeNodeUI::GetSelItemTextColor() const
	{
		return m_dwSelItemTextColor;
	}

	//************************************
	// 函数名称: SetSelHotItemTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwSelHotItemTextColor
	// 函数说明: 
	//************************************
	void CTreeNodeUI::SetSelItemHotTextColor( DWORD _dwSelHotItemTextColor )
	{
		m_dwSelItemHotTextColor = _dwSelHotItemTextColor;
		Invalidate();
	}

	//************************************
	// 函数名称: GetSelHotItemTextColor
	// 返回类型: DWORD
	// 函数说明: 
	//************************************
	DWORD CTreeNodeUI::GetSelItemHotTextColor() const
	{
		return m_dwSelItemHotTextColor;
	}

	/*****************************************************************************/
	/*****************************************************************************/
	/*****************************************************************************/
	
	//************************************
	// 函数名称: CTreeViewUI
	// 返回类型: 
	// 参数信息: void
	// 函数说明: 
	//************************************
	CTreeViewUI::CTreeViewUI( void ) : m_bVisibleFolderBtn(TRUE),m_bVisibleCheckBtn(FALSE),m_uItemMinWidth(0)
	{
		this->GetHeader()->SetVisible(FALSE);
	}
	
	//************************************
	// 函数名称: ~CTreeViewUI
	// 返回类型: 
	// 参数信息: void
	// 函数说明: 
	//************************************
	CTreeViewUI::~CTreeViewUI( void )
	{
		
	}

	//************************************
	// 函数名称: GetClass
	// 返回类型: LPCTSTR
	// 函数说明: 
	//************************************
	LPCTSTR CTreeViewUI::GetClass() const
	{
		return DUI_CTR_TREEVIEW;
	}

	LPVOID CTreeViewUI::GetInterface( LPCTSTR pstrName )
	{
		if( _tcscmp(pstrName, DUI_CTR_TREEVIEW) == 0 ) return static_cast<CTreeViewUI*>(this);
		return CListUI::GetInterface(pstrName);
	}

	BOOL CTreeViewUI::Add(CControlUI* pControl)
	{
		if (!pControl) return FALSE;

        CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(pControl->GetInterface(DUI_CTR_TREENODE));
        if (pTreeNode == NULL) return FALSE;

		pTreeNode->OnNotify += MakeDelegate(this,&CTreeViewUI::OnDBClickItem);
		pTreeNode->GetFolderButton()->OnNotify += MakeDelegate(this,&CTreeViewUI::OnFolderChanged);
		pTreeNode->GetCheckBox()->OnNotify += MakeDelegate(this,&CTreeViewUI::OnCheckBoxChanged);

		pTreeNode->SetVisibleFolderBtn(m_bVisibleFolderBtn);
		pTreeNode->SetVisibleCheckBtn(m_bVisibleCheckBtn);
		if(m_uItemMinWidth > 0)	pTreeNode->SetMinWidth(m_uItemMinWidth);

		CListUI::Add(pTreeNode);

		if(pTreeNode->GetCountChild() > 0)
		{
			int nCount = pTreeNode->GetCountChild();
			for(int nIndex = 0;nIndex < nCount;nIndex++)
			{
				CTreeNodeUI* pNode = pTreeNode->GetChildNode(nIndex);
				if(pNode) Add(pNode);
			}
		}

		pTreeNode->SetTreeView(this);
		return TRUE;
	}

    BOOL CTreeViewUI::AddAt(CControlUI* pControl, int iIndex)
    {
        if (!pControl) return FALSE;

        CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(pControl->GetInterface(DUI_CTR_TREENODE));
        if (pTreeNode == NULL) return FALSE;
        return AddAt(pTreeNode, iIndex) >= 0;
    }

	BOOL CTreeViewUI::Remove(CControlUI* pControl, BOOL bDoNotDestroy)
	{
        if (!pControl) return FALSE;

        CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(pControl->GetInterface(DUI_CTR_TREENODE));
        if (pTreeNode == NULL) return CListUI::Remove(pControl, bDoNotDestroy);

		if(pTreeNode->GetCountChild() > 0)
		{
			int nCount = pTreeNode->GetCountChild();
			for(int nIndex = 0;nIndex < nCount;nIndex++)
			{
				CTreeNodeUI* pNode = pTreeNode->GetChildNode(nIndex);
				if(pNode){
					pTreeNode->Remove(pNode, TRUE);
				}
			}
		}
		return CListUI::Remove(pControl, bDoNotDestroy);
	}

	BOOL CTreeViewUI::RemoveAt( int iIndex, BOOL bDoNotDestroy )
	{
        CControlUI* pControl = GetItemAt(iIndex);
        if (pControl == NULL) return FALSE;

        CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(pControl->GetInterface(DUI_CTR_TREENODE));
        if (pTreeNode == NULL) return CListUI::Remove(pControl, bDoNotDestroy);

		return Remove(pTreeNode);
	}

	void CTreeViewUI::RemoveAll()
	{
		CListUI::RemoveAll();
	}

    long CTreeViewUI::AddAt(CTreeNodeUI* pControl, int iIndex)
    {
        if (!pControl) return -1;

        CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(pControl->GetInterface(DUI_CTR_TREENODE));
        if (pTreeNode == NULL) return -1;

        CTreeNodeUI* pParent = static_cast<CTreeNodeUI*>(GetItemAt(iIndex));
        if(!pParent) return -1;

        pTreeNode->OnNotify += MakeDelegate(this,&CTreeViewUI::OnDBClickItem);
        pTreeNode->GetFolderButton()->OnNotify += MakeDelegate(this,&CTreeViewUI::OnFolderChanged);
        pTreeNode->GetCheckBox()->OnNotify += MakeDelegate(this,&CTreeViewUI::OnCheckBoxChanged);

        pTreeNode->SetVisibleFolderBtn(m_bVisibleFolderBtn);
        pTreeNode->SetVisibleCheckBtn(m_bVisibleCheckBtn);

        if(m_uItemMinWidth > 0) pTreeNode->SetMinWidth(m_uItemMinWidth);

        CListUI::AddAt(pTreeNode,iIndex);

        if(pTreeNode->GetCountChild() > 0)
        {
            int nCount = pTreeNode->GetCountChild();
            for(int nIndex = 0;nIndex < nCount;nIndex++)
            {
                CTreeNodeUI* pNode = pTreeNode->GetChildNode(nIndex);
                if(pNode)
                    return AddAt(pNode,iIndex+1);
            }
        }
        else
            return iIndex+1;

        return -1;
    }

	BOOL CTreeViewUI::AddAt( CTreeNodeUI* pControl,CTreeNodeUI* _IndexNode )
	{
		if(!_IndexNode && !pControl)
			return FALSE;

		int nItemIndex = -1;

		for(int nIndex = 0;nIndex < GetCount();nIndex++){
			if(_IndexNode == GetItemAt(nIndex)){
				nItemIndex = nIndex;
				break;
			}
		}

		if(nItemIndex == -1)
			return FALSE;

		return AddAt(pControl,nItemIndex) >= 0;
	}

	//************************************
	// 函数名称: Notify
	// 返回类型: void
	// 参数信息: TNOTIFY_UI & msg
	// 函数说明: 
	//************************************
	void CTreeViewUI::Notify( TNOTIFY_UI& msg )
	{
		
	}
	
	//************************************
	// 函数名称: OnCheckBoxChanged
	// 返回类型: BOOL
	// 参数信息: void * param
	// 函数说明: 
	//************************************
	BOOL CTreeViewUI::OnCheckBoxChanged( void* param )
	{
		TNOTIFY_UI* pMsg = (TNOTIFY_UI*)param;
		if(pMsg->sType == DUI_MSGTYPE_SELECTCHANGED)
		{
			CCheckBoxUI* pCheckBox = (CCheckBoxUI*)pMsg->pSender;
			CTreeNodeUI* pItem = (CTreeNodeUI*)pCheckBox->GetParent()->GetParent();
			SetItemCheckBox(pCheckBox->GetCheck(),pItem);
			return TRUE;
		}
		return TRUE;
	}
	
	//************************************
	// 函数名称: OnFolderChanged
	// 返回类型: BOOL
	// 参数信息: void * param
	// 函数说明: 
	//************************************
	BOOL CTreeViewUI::OnFolderChanged( void* param )
	{
		TNOTIFY_UI* pMsg = (TNOTIFY_UI*)param;
		if(pMsg->sType == DUI_MSGTYPE_SELECTCHANGED)
		{
			CCheckBoxUI* pFolder = (CCheckBoxUI*)pMsg->pSender;
			CTreeNodeUI* pItem = (CTreeNodeUI*)pFolder->GetParent()->GetParent();
			pItem->SetVisibleTag(!pFolder->GetCheck());
			SetItemExpand(!pFolder->GetCheck(),pItem);
			return TRUE;
		}
		return TRUE;
	}
	
	//************************************
	// 函数名称: OnDBClickItem
	// 返回类型: BOOL
	// 参数信息: void * param
	// 函数说明:
	//************************************
	BOOL CTreeViewUI::OnDBClickItem( void* param )
	{
		TNOTIFY_UI* pMsg = (TNOTIFY_UI*)param;
		if(pMsg->sType == DUI_MSGTYPE_ITEMDBCLICK)
		{
			CTreeNodeUI* pItem		= static_cast<CTreeNodeUI*>(pMsg->pSender);
			CCheckBoxUI* pFolder	= pItem->GetFolderButton();
			pFolder->Selected(!pFolder->IsSelected());
			pItem->SetVisibleTag(!pFolder->GetCheck());
			SetItemExpand(!pFolder->GetCheck(),pItem);
			return TRUE;
		}
		return FALSE;
	}

	//************************************
	// 函数名称: SetItemCheckBox
	// 返回类型: BOOL
	// 参数信息: BOOL _Selected
	// 参数信息: CTreeNodeUI * _TreeNode
	// 函数说明: 
	//************************************
	BOOL CTreeViewUI::SetItemCheckBox( BOOL _Selected,CTreeNodeUI* _TreeNode /*= NULL*/ )
	{
		if(_TreeNode)
		{
			if(_TreeNode->GetCountChild() > 0)
			{
				int nCount = _TreeNode->GetCountChild();
				for(int nIndex = 0;nIndex < nCount;nIndex++)
				{
					CTreeNodeUI* pItem = _TreeNode->GetChildNode(nIndex);
					pItem->GetCheckBox()->Selected(_Selected);
					if(pItem->GetCountChild())
						SetItemCheckBox(_Selected,pItem);
				}
			}
			return TRUE;
		}
		else
		{
			int nIndex = 0;
			int nCount = GetCount();
			while(nIndex < nCount)
			{
				CTreeNodeUI* pItem = (CTreeNodeUI*)GetItemAt(nIndex);
				pItem->GetCheckBox()->Selected(_Selected);
				if(pItem->GetCountChild())
					SetItemCheckBox(_Selected,pItem);

				nIndex++;
			}
			return TRUE;
		}
		return FALSE;
	}

	//************************************
	// 函数名称: SetItemExpand
	// 返回类型: void
	// 参数信息: BOOL _Expanded
	// 参数信息: CTreeNodeUI * _TreeNode
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetItemExpand( BOOL _Expanded,CTreeNodeUI* _TreeNode /*= NULL*/ )
	{
		if(_TreeNode)
		{
			if(_TreeNode->GetCountChild() > 0)
			{
				int nCount = _TreeNode->GetCountChild();
				for(int nIndex = 0;nIndex < nCount;nIndex++)
				{
					CTreeNodeUI* pItem = _TreeNode->GetChildNode(nIndex);
					pItem->SetVisible(_Expanded);

					if(pItem->GetCountChild() && !pItem->GetFolderButton()->IsSelected())
						SetItemExpand(_Expanded,pItem);
				}
			}
		}
		else
		{
			int nIndex = 0;
			int nCount = GetCount();
			while(nIndex < nCount)
			{
				CTreeNodeUI* pItem = (CTreeNodeUI*)GetItemAt(nIndex);

				pItem->SetVisible(_Expanded);

				if(pItem->GetCountChild() && !pItem->GetFolderButton()->IsSelected())
					SetItemExpand(_Expanded,pItem);

				nIndex++;
			}
		}
	}

	//************************************
	// 函数名称: SetVisibleFolderBtn
	// 返回类型: void
	// 参数信息: BOOL _IsVisibled
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetVisibleFolderBtn( BOOL _IsVisibled )
	{
		m_bVisibleFolderBtn = _IsVisibled;
		int nCount = this->GetCount();
		for(int nIndex = 0;nIndex < nCount;nIndex++)
		{
			CTreeNodeUI* pItem = static_cast<CTreeNodeUI*>(this->GetItemAt(nIndex));
			pItem->GetFolderButton()->SetVisible(m_bVisibleFolderBtn);
		}
	}

	//************************************
	// 函数名称: GetVisibleFolderBtn
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeViewUI::GetVisibleFolderBtn()
	{
		return m_bVisibleFolderBtn;
	}

	//************************************
	// 函数名称: SetVisibleCheckBtn
	// 返回类型: void
	// 参数信息: BOOL _IsVisibled
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetVisibleCheckBtn( BOOL _IsVisibled )
	{
		m_bVisibleCheckBtn = _IsVisibled;
		int nCount = this->GetCount();
		for(int nIndex = 0;nIndex < nCount;nIndex++)
		{
			CTreeNodeUI* pItem = static_cast<CTreeNodeUI*>(this->GetItemAt(nIndex));
			pItem->GetCheckBox()->SetVisible(m_bVisibleCheckBtn);
		}
	}

	//************************************
	// 函数名称: GetVisibleCheckBtn
	// 返回类型: BOOL
	// 函数说明: 
	//************************************
	BOOL CTreeViewUI::GetVisibleCheckBtn()
	{
		return m_bVisibleCheckBtn;
	}

	//************************************
	// 函数名称: SetItemMinWidth
	// 返回类型: void
	// 参数信息: UINT _ItemMinWidth
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetItemMinWidth( UINT _ItemMinWidth )
	{
		m_uItemMinWidth = _ItemMinWidth;

		for(int nIndex = 0;nIndex < GetCount();nIndex++){
			CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(GetItemAt(nIndex));
			if(pTreeNode)
				pTreeNode->SetMinWidth(GetItemMinWidth());
		}
		Invalidate();
	}

	//************************************
	// 函数名称: GetItemMinWidth
	// 返回类型: UINT
	// 函数说明: 
	//************************************
	UINT CTreeViewUI::GetItemMinWidth()
	{
		return m_uItemMinWidth;
	}
	
	//************************************
	// 函数名称: SetItemTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwItemTextColor
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetItemTextColor( DWORD _dwItemTextColor )
	{
		for(int nIndex = 0;nIndex < GetCount();nIndex++){
			CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(GetItemAt(nIndex));
			if(pTreeNode)
				pTreeNode->SetItemTextColor(_dwItemTextColor);
		}
	}

	//************************************
	// 函数名称: SetItemHotTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwItemHotTextColor
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetItemHotTextColor( DWORD _dwItemHotTextColor )
	{
		for(int nIndex = 0;nIndex < GetCount();nIndex++){
			CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(GetItemAt(nIndex));
			if(pTreeNode)
				pTreeNode->SetItemHotTextColor(_dwItemHotTextColor);
		}
	}

	//************************************
	// 函数名称: SetSelItemTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwSelItemTextColor
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetSelItemTextColor( DWORD _dwSelItemTextColor )
	{
		for(int nIndex = 0;nIndex < GetCount();nIndex++){
			CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(GetItemAt(nIndex));
			if(pTreeNode)
				pTreeNode->SetSelItemTextColor(_dwSelItemTextColor);
		}
	}
		
	//************************************
	// 函数名称: SetSelItemHotTextColor
	// 返回类型: void
	// 参数信息: DWORD _dwSelHotItemTextColor
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetSelItemHotTextColor( DWORD _dwSelHotItemTextColor )
	{
		for(int nIndex = 0;nIndex < GetCount();nIndex++){
			CTreeNodeUI* pTreeNode = static_cast<CTreeNodeUI*>(GetItemAt(nIndex));
			if(pTreeNode)
				pTreeNode->SetSelItemHotTextColor(_dwSelHotItemTextColor);
		}
	}

	//************************************
	// 函数名称: SetAttribute
	// 返回类型: void
	// 参数信息: LPCTSTR pstrName
	// 参数信息: LPCTSTR pstrValue
	// 函数说明: 
	//************************************
	void CTreeViewUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if(_tcscmp(pstrName,_T("visiblefolderbtn")) == 0)
			SetVisibleFolderBtn(_tcscmp(pstrValue,_T("TRUE")) == 0);
		else if(_tcscmp(pstrName,_T("visiblecheckbtn")) == 0)
			SetVisibleCheckBtn(_tcscmp(pstrValue,_T("TRUE")) == 0);
		else if(_tcscmp(pstrName,_T("itemminwidth")) == 0)
			SetItemMinWidth(_ttoi(pstrValue));
		else if(_tcscmp(pstrName, _T("itemtextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetItemTextColor(clrColor);
		}
		else if(_tcscmp(pstrName, _T("itemhottextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetItemHotTextColor(clrColor);
		}
		else if(_tcscmp(pstrName, _T("selitemtextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetSelItemTextColor(clrColor);
		}
		else if(_tcscmp(pstrName, _T("selitemhottextcolor")) == 0 ){
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetSelItemHotTextColor(clrColor);
		}
		else CListUI::SetAttribute(pstrName,pstrValue);
	}

}