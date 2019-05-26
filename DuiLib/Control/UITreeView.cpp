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
	// ��������: CTreeNodeUI
	// ��������: 
	// ������Ϣ: CTreeNodeUI * _ParentNode
	// ����˵��: 
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
	// ��������: ~CTreeNodeUI
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CTreeNodeUI::~CTreeNodeUI( void )
	{

	}

	//************************************
	// ��������: GetClass
	// ��������: LPCTSTR
	// ����˵��: 
	//************************************
	LPCTSTR CTreeNodeUI::GetClass() const
	{
		return DUI_CTR_TREENODE;
	}

	//************************************
	// ��������: GetInterface
	// ��������: LPVOID
	// ������Ϣ: LPCTSTR pstrName
	// ����˵��: 
	//************************************
	LPVOID CTreeNodeUI::GetInterface( LPCTSTR pstrName )
	{
		if( _tcscmp(pstrName, DUI_CTR_TREENODE) == 0 ) return static_cast<CTreeNodeUI*>(this);
		return CListContainerElementUI::GetInterface(pstrName);
	}
	
	//************************************
	// ��������: DoEvent
	// ��������: void
	// ������Ϣ: TEVENT_UI & event
	// ����˵��:
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
	// ��������: Invalidate
	// ��������: void
	// ����˵��: 
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
	// ��������: Select
	// ��������: BOOL
	// ������Ϣ: BOOL bSelect
	// ����˵��: 
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
	// ��������: Add
	// ��������: BOOL
	// ������Ϣ: CControlUI * _pTreeNodeUI
	// ����˵��: ͨ���ڵ������ӽڵ�
	//************************************
	BOOL CTreeNodeUI::Add( CControlUI* _pTreeNodeUI )
	{
		if (_tcsicmp(_pTreeNodeUI->GetClass(), DUI_CTR_TREENODE) == 0)
			return AddChildNode((CTreeNodeUI*)_pTreeNodeUI);

		return CListContainerElementUI::Add(_pTreeNodeUI);
	}

	//************************************
	// ��������: AddAt
	// ��������: BOOL
	// ������Ϣ: CControlUI * pControl
	// ������Ϣ: int iIndex				�ò�������Ե�ǰ�ڵ��µ��ֵ������������б���ͼ����
	// ����˵��: 
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
	// ��������: SetVisibleTag
	// ��������: void
	// ������Ϣ: BOOL _IsVisible
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetVisibleTag( BOOL _IsVisible )
	{
		m_bIsVisable = _IsVisible;
	}

	//************************************
	// ��������: GetVisibleTag
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeNodeUI::GetVisibleTag()
	{
		return m_bIsVisable;
	}

	//************************************
	// ��������: SetItemText
	// ��������: void
	// ������Ϣ: LPCTSTR pstrValue
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetItemText( LPCTSTR pstrValue )
	{
		pItemButton->SetText(pstrValue);
	}

	//************************************
	// ��������: GetItemText
	// ��������: UiLib::CStringUI
	// ����˵��: 
	//************************************
	CStringUI CTreeNodeUI::GetItemText()
	{
		return pItemButton->GetText();
	}

	//************************************
	// ��������: CheckBoxSelected
	// ��������: void
	// ������Ϣ: BOOL _Selected
	// ����˵��: 
	//************************************
	void CTreeNodeUI::CheckBoxSelected( BOOL _Selected )
	{
		pCheckBox->Selected(_Selected);
	}

	//************************************
	// ��������: IsCheckBoxSelected
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeNodeUI::IsCheckBoxSelected() const
	{
		return pCheckBox->IsSelected();
	}

	//************************************
	// ��������: IsHasChild
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeNodeUI::IsHasChild() const
	{
		return !mTreeNodes.IsEmpty();
	}
	
	//************************************
	// ��������: AddChildNode
	// ��������: BOOL
	// ������Ϣ: CTreeNodeUI * _pTreeNodeUI
	// ����˵��: 
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
	// ��������: RemoveAt
	// ��������: BOOL
	// ������Ϣ: CTreeNodeUI * _pTreeNodeUI
	// ����˵��: 
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
	// ��������: SetParentNode
	// ��������: void
	// ������Ϣ: CTreeNodeUI * _pParentTreeNode
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetParentNode( CTreeNodeUI* _pParentTreeNode )
	{
		pParentTreeNode = _pParentTreeNode;
	}

	//************************************
	// ��������: GetParentNode
	// ��������: CTreeNodeUI*
	// ����˵��: 
	//************************************
	CTreeNodeUI* CTreeNodeUI::GetParentNode()
	{
		return pParentTreeNode;
	}

	//************************************
	// ��������: GetCountChild
	// ��������: long
	// ����˵��: 
	//************************************
	long CTreeNodeUI::GetCountChild()
	{
		return mTreeNodes.GetSize();
	}

	//************************************
	// ��������: SetTreeView
	// ��������: void
	// ������Ϣ: CTreeViewUI * _CTreeViewUI
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetTreeView( CTreeViewUI* _CTreeViewUI )
	{
		pTreeView = _CTreeViewUI;
	}

	//************************************
	// ��������: GetTreeView
	// ��������: CTreeViewUI*
	// ����˵��: 
	//************************************
	CTreeViewUI* CTreeNodeUI::GetTreeView()
	{
		return pTreeView;
	}

	//************************************
	// ��������: SetAttribute
	// ��������: void
	// ������Ϣ: LPCTSTR pstrName
	// ������Ϣ: LPCTSTR pstrValue
	// ����˵��: 
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
	// ��������: GetTreeNodes
	// ��������: UiLib::CPtrArrayUI
	// ����˵��: 
	//************************************
	CPtrArrayUI CTreeNodeUI::GetTreeNodes()
	{
		return mTreeNodes;
	}

	//************************************
	// ��������: GetChildNode
	// ��������: CTreeNodeUI*
	// ������Ϣ: int _nIndex
	// ����˵��: 
	//************************************
	CTreeNodeUI* CTreeNodeUI::GetChildNode( int _nIndex )
	{
		return static_cast<CTreeNodeUI*>(mTreeNodes.GetAt(_nIndex));
	}

	//************************************
	// ��������: SetVisibleFolderBtn
	// ��������: void
	// ������Ϣ: BOOL _IsVisibled
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetVisibleFolderBtn( BOOL _IsVisibled )
	{
		pFolderButton->SetVisible(_IsVisibled);
	}

	//************************************
	// ��������: GetVisibleFolderBtn
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeNodeUI::GetVisibleFolderBtn()
	{
		return pFolderButton->IsVisible();
	}

	//************************************
	// ��������: SetVisibleCheckBtn
	// ��������: void
	// ������Ϣ: BOOL _IsVisibled
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetVisibleCheckBtn( BOOL _IsVisibled )
	{
		pCheckBox->SetVisible(_IsVisibled);
	}

	//************************************
	// ��������: GetVisibleCheckBtn
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeNodeUI::GetVisibleCheckBtn()
	{
		return pCheckBox->IsVisible();
	}
	
	//************************************
	// ��������: GetNodeIndex
	// ��������: int
	// ����˵��: ȡ��ȫ������ͼ������
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
	// ��������: GetNodeIndex
	// ��������: int
	// ����˵��: ȡ��������ֵܽڵ�ĵ�ǰ����
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
	// ��������: GetLastNode
	// ��������: CTreeNodeUI*
	// ����˵��:
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
	// ��������: CalLocation
	// ��������: CTreeNodeUI*
	// ������Ϣ: CTreeNodeUI * _pTreeNodeUI
	// ����˵��: ��������
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
	// ��������: SetTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwTextColor
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetItemTextColor( DWORD _dwItemTextColor )
	{
		m_dwItemTextColor	= _dwItemTextColor;
		pItemButton->SetTextColor(m_dwItemTextColor);
	}

	//************************************
	// ��������: GetTextColor
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CTreeNodeUI::GetItemTextColor() const
	{
		return m_dwItemTextColor;
	}

	//************************************
	// ��������: SetTextHotColor
	// ��������: void
	// ������Ϣ: DWORD _dwTextHotColor
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetItemHotTextColor( DWORD _dwItemHotTextColor )
	{
		m_dwItemHotTextColor = _dwItemHotTextColor;
		Invalidate();
	}

	//************************************
	// ��������: GetTextHotColor
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CTreeNodeUI::GetItemHotTextColor() const
	{
		return m_dwItemHotTextColor;
	}

	//************************************
	// ��������: SetSelItemTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwSelItemTextColor
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetSelItemTextColor( DWORD _dwSelItemTextColor )
	{
		m_dwSelItemTextColor = _dwSelItemTextColor;
		Invalidate();
	}

	//************************************
	// ��������: GetSelItemTextColor
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CTreeNodeUI::GetSelItemTextColor() const
	{
		return m_dwSelItemTextColor;
	}

	//************************************
	// ��������: SetSelHotItemTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwSelHotItemTextColor
	// ����˵��: 
	//************************************
	void CTreeNodeUI::SetSelItemHotTextColor( DWORD _dwSelHotItemTextColor )
	{
		m_dwSelItemHotTextColor = _dwSelHotItemTextColor;
		Invalidate();
	}

	//************************************
	// ��������: GetSelHotItemTextColor
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CTreeNodeUI::GetSelItemHotTextColor() const
	{
		return m_dwSelItemHotTextColor;
	}

	/*****************************************************************************/
	/*****************************************************************************/
	/*****************************************************************************/
	
	//************************************
	// ��������: CTreeViewUI
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CTreeViewUI::CTreeViewUI( void ) : m_bVisibleFolderBtn(TRUE),m_bVisibleCheckBtn(FALSE),m_uItemMinWidth(0)
	{
		this->GetHeader()->SetVisible(FALSE);
	}
	
	//************************************
	// ��������: ~CTreeViewUI
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CTreeViewUI::~CTreeViewUI( void )
	{
		
	}

	//************************************
	// ��������: GetClass
	// ��������: LPCTSTR
	// ����˵��: 
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
	// ��������: Notify
	// ��������: void
	// ������Ϣ: TNOTIFY_UI & msg
	// ����˵��: 
	//************************************
	void CTreeViewUI::Notify( TNOTIFY_UI& msg )
	{
		
	}
	
	//************************************
	// ��������: OnCheckBoxChanged
	// ��������: BOOL
	// ������Ϣ: void * param
	// ����˵��: 
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
	// ��������: OnFolderChanged
	// ��������: BOOL
	// ������Ϣ: void * param
	// ����˵��: 
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
	// ��������: OnDBClickItem
	// ��������: BOOL
	// ������Ϣ: void * param
	// ����˵��:
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
	// ��������: SetItemCheckBox
	// ��������: BOOL
	// ������Ϣ: BOOL _Selected
	// ������Ϣ: CTreeNodeUI * _TreeNode
	// ����˵��: 
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
	// ��������: SetItemExpand
	// ��������: void
	// ������Ϣ: BOOL _Expanded
	// ������Ϣ: CTreeNodeUI * _TreeNode
	// ����˵��: 
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
	// ��������: SetVisibleFolderBtn
	// ��������: void
	// ������Ϣ: BOOL _IsVisibled
	// ����˵��: 
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
	// ��������: GetVisibleFolderBtn
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeViewUI::GetVisibleFolderBtn()
	{
		return m_bVisibleFolderBtn;
	}

	//************************************
	// ��������: SetVisibleCheckBtn
	// ��������: void
	// ������Ϣ: BOOL _IsVisibled
	// ����˵��: 
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
	// ��������: GetVisibleCheckBtn
	// ��������: BOOL
	// ����˵��: 
	//************************************
	BOOL CTreeViewUI::GetVisibleCheckBtn()
	{
		return m_bVisibleCheckBtn;
	}

	//************************************
	// ��������: SetItemMinWidth
	// ��������: void
	// ������Ϣ: UINT _ItemMinWidth
	// ����˵��: 
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
	// ��������: GetItemMinWidth
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CTreeViewUI::GetItemMinWidth()
	{
		return m_uItemMinWidth;
	}
	
	//************************************
	// ��������: SetItemTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwItemTextColor
	// ����˵��: 
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
	// ��������: SetItemHotTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwItemHotTextColor
	// ����˵��: 
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
	// ��������: SetSelItemTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwSelItemTextColor
	// ����˵��: 
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
	// ��������: SetSelItemHotTextColor
	// ��������: void
	// ������Ϣ: DWORD _dwSelHotItemTextColor
	// ����˵��: 
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
	// ��������: SetAttribute
	// ��������: void
	// ������Ϣ: LPCTSTR pstrName
	// ������Ϣ: LPCTSTR pstrValue
	// ����˵��: 
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