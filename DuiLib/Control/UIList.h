#ifndef __UILIST_H__
#define __UILIST_H__

#include "Layout/UIVerticalLayout.h"
#include "Layout/UIHorizontalLayout.h"

#include "Core/UIRender.h"
#include "Core/UIControl.h"

namespace DUILIB
{
    /////////////////////////////////////////////////////////////////////////////////////
    //

    typedef int (CALLBACK* PULVCompareFunc)(UINT_PTR, UINT_PTR, UINT_PTR);

    class CListHeaderUI;

#define UILIST_MAX_COLUMNS 64

    typedef struct tagTListInfoUI
    {
        int nColumns;
        RECT rcColumn[UILIST_MAX_COLUMNS];
        UINT uFixedHeight;
        int nFont;
        UINT uTextStyle;
        RECT rcTextPadding;
        DWORD dwTextColor;
        DWORD dwBkColor;
        TDRAWINFO_UI diBk;
        BOOL bAlternateBk;
        DWORD dwSelectedTextColor;
        DWORD dwSelectedBkColor;
        TDRAWINFO_UI diSelected;
        DWORD dwHotTextColor;
        DWORD dwHotBkColor;
        TDRAWINFO_UI diHot;
        DWORD dwDisabledTextColor;
        DWORD dwDisabledBkColor;
        TDRAWINFO_UI diDisabled;
        int iHLineSize;
        DWORD dwHLineColor;
        int iVLineSize;
        DWORD dwVLineColor;
        BOOL bShowHtml;
        BOOL bMultiExpandable;
    } TListInfoUI;


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class IListCallbackUI
    {
    public:
        virtual LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem) = 0;
    };

    class IListOwnerUI
    {
    public:
        virtual TListInfoUI* GetListInfo() = 0;
        virtual int GetCurSel() const = 0;
        virtual BOOL SelectItem(int iIndex, BOOL bTakeFocus = FALSE, BOOL bTriggerEvent = TRUE) = 0;
        virtual void DoEvent(TEVENT_UI& event) = 0;
        virtual BOOL ExpandItem(int iIndex, BOOL bExpand = TRUE) = 0;
        virtual int GetExpandedItem() const = 0;
    };

    class IListUI : public IListOwnerUI
    {
    public:
        virtual CListHeaderUI* GetHeader() const = 0;
        virtual CContainerUI* GetList() const = 0;
        virtual IListCallbackUI* GetTextCallback() const = 0;
        virtual void SetTextCallback(IListCallbackUI* pCallback) = 0;
    };

    class IListItemUI
    {
    public:
        virtual int GetIndex() const = 0;
        virtual void SetIndex(int iIndex) = 0;
        virtual int GetDrawIndex() const = 0;
        virtual void SetDrawIndex(int iIndex) = 0;
        virtual IListOwnerUI* GetOwner() = 0;
        virtual void SetOwner(CControlUI* pOwner) = 0;
        virtual BOOL IsSelected() const = 0;
        virtual BOOL Select(BOOL bSelect = TRUE, BOOL bTriggerEvent = TRUE) = 0;
        virtual BOOL IsExpanded() const = 0;
        virtual BOOL Expand(BOOL bExpand = TRUE) = 0;
        virtual void DrawItemText(HDC hDC, const RECT& rcItem) = 0;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class CListBodyUI;
    class CListHeaderUI;

    class DUILIB_API CListUI : public CVerticalLayoutUI, public IListUI
    {
    public:
        CListUI();

        LPCTSTR GetClass() const;
        UINT GetControlFlags() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        BOOL GetScrollSelect();
        void SetScrollSelect(BOOL bScrollSelect);
        int GetCurSel() const;
        BOOL SelectItem(int iIndex, BOOL bTakeFocus = FALSE, BOOL bTriggerEvent = TRUE);

        CControlUI* GetItemAt(int iIndex) const;
        int GetItemIndex(CControlUI* pControl) const;
        BOOL SetItemIndex(CControlUI* pControl, int iIndex);
        BOOL SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
        int GetCount() const;
        BOOL Add(CControlUI* pControl);
        BOOL AddAt(CControlUI* pControl, int iIndex);
        BOOL Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
        BOOL RemoveAt(int iIndex, BOOL bDoNotDestroy = FALSE);
        void RemoveAll();

        void EnsureVisible(int iIndex);
        void Scroll(int dx, int dy);

        int GetChildPadding() const;
        void SetChildPadding(int iPadding);

        CListHeaderUI* GetHeader() const;
        CContainerUI* GetList() const;
        TListInfoUI* GetListInfo();

        UINT GetItemFixedHeight();
        void SetItemFixedHeight(UINT nHeight);
        int GetItemFont(int index);
        void SetItemFont(int index);
        UINT GetItemTextStyle();
        void SetItemTextStyle(UINT uStyle);
        RECT GetItemTextPadding() const;
        void SetItemTextPadding(RECT rc);
        DWORD GetItemTextColor() const;
        void SetItemTextColor(DWORD dwTextColor);
        DWORD GetItemBkColor() const;
        void SetItemBkColor(DWORD dwBkColor);
        LPCTSTR GetItemBkImage() const;
        void SetItemBkImage(LPCTSTR pStrImage);
        BOOL IsAlternateBk() const;
        void SetAlternateBk(BOOL bAlternateBk);
        DWORD GetSelectedItemTextColor() const;
        void SetSelectedItemTextColor(DWORD dwTextColor);
        DWORD GetSelectedItemBkColor() const;
        void SetSelectedItemBkColor(DWORD dwBkColor);
        LPCTSTR GetSelectedItemImage() const;
        void SetSelectedItemImage(LPCTSTR pStrImage);
        DWORD GetHotItemTextColor() const;
        void SetHotItemTextColor(DWORD dwTextColor);
        DWORD GetHotItemBkColor() const;
        void SetHotItemBkColor(DWORD dwBkColor);
        LPCTSTR GetHotItemImage() const;
        void SetHotItemImage(LPCTSTR pStrImage);
        DWORD GetDisabledItemTextColor() const;
        void SetDisabledItemTextColor(DWORD dwTextColor);
        DWORD GetDisabledItemBkColor() const;
        void SetDisabledItemBkColor(DWORD dwBkColor);
        LPCTSTR GetDisabledItemImage() const;
        void SetDisabledItemImage(LPCTSTR pStrImage);
        int GetItemHLineSize() const;
        void SetItemHLineSize(int iSize);
        DWORD GetItemHLineColor() const;
        void SetItemHLineColor(DWORD dwLineColor);
        int GetItemVLineSize() const;
        void SetItemVLineSize(int iSize);
        DWORD GetItemVLineColor() const;
        void SetItemVLineColor(DWORD dwLineColor);
        BOOL IsItemShowHtml();
        void SetItemShowHtml(BOOL bShowHtml = TRUE);

        void SetMultiExpanding(BOOL bMultiExpandable);
        int GetExpandedItem() const;
        BOOL ExpandItem(int iIndex, BOOL bExpand = TRUE);

        void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        void Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
        void DoEvent(TEVENT_UI& event);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        IListCallbackUI* GetTextCallback() const;
        void SetTextCallback(IListCallbackUI* pCallback);

        SIZE GetScrollPos() const;
        SIZE GetScrollRange() const;
        void SetScrollPos(SIZE szPos);
        void LineUp();
        void LineDown();
        void PageUp();
        void PageDown();
        void HomeUp();
        void EndDown();
        void LineLeft();
        void LineRight();
        void PageLeft();
        void PageRight();
        void HomeLeft();
        void EndRight();
        void EnableScrollBar(BOOL bEnableVertical = TRUE, BOOL bEnableHorizontal = FALSE);
        virtual CScrollUI* GetVerticalScrollBar() const;
        virtual CScrollUI* GetHorizontalScrollBar() const;
        BOOL SortItems(PULVCompareFunc pfnCompare, UINT_PTR dwData);

    protected:
        BOOL m_bScrollSelect;
        int m_iCurSel;
        int m_iExpandedItem;
        IListCallbackUI* m_pCallback;
        CListBodyUI* m_pList;
        CListHeaderUI* m_pHeader;
        TListInfoUI m_ListInfo;
    };

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListHeaderUI : public CHorizontalLayoutUI
    {
    public:
        CListHeaderUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        SIZE EstimateSize(SIZE szAvailable);
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListHeaderItemUI : public CControlUI
    {
    public:
        CListHeaderItemUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);
        UINT GetControlFlags() const;

        void SetEnabled(BOOL bEnable = TRUE);

        BOOL IsDragable() const;
        void SetDragable(BOOL bDragable);
        DWORD GetSepWidth() const;
        void SetSepWidth(int iWidth);
        DWORD GetTextStyle() const;
        void SetTextStyle(UINT uStyle);
        DWORD GetTextColor() const;
        void SetTextColor(DWORD dwTextColor);
        DWORD GetSepColor() const;
        void SetSepColor(DWORD dwSepColor);
        void SetTextPadding(RECT rc);
        RECT GetTextPadding() const;
        void SetFont(int index);
        BOOL IsShowHtml();
        void SetShowHtml(BOOL bShowHtml = TRUE);
        LPCTSTR GetNormalImage() const;
        void SetNormalImage(LPCTSTR pStrImage);
        LPCTSTR GetHotImage() const;
        void SetHotImage(LPCTSTR pStrImage);
        LPCTSTR GetPushedImage() const;
        void SetPushedImage(LPCTSTR pStrImage);
        LPCTSTR GetFocusedImage() const;
        void SetFocusedImage(LPCTSTR pStrImage);
        LPCTSTR GetSepImage() const;
        void SetSepImage(LPCTSTR pStrImage);

        void DoEvent(TEVENT_UI& event);
        SIZE EstimateSize(SIZE szAvailable);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        RECT GetThumbRect() const;

        void PaintText(HDC hDC);
        void PaintStatusImage(HDC hDC);

    protected:
        POINT ptLastMouse;
        BOOL m_bDragable;
        UINT m_uButtonState;
        int m_iSepWidth;
        DWORD m_dwTextColor;
        DWORD m_dwSepColor;
        int m_iFont;
        UINT m_uTextStyle;
        BOOL m_bShowHtml;
        RECT m_rcTextPadding;
        TDRAWINFO_UI m_diNormal;
        TDRAWINFO_UI m_diHot;
        TDRAWINFO_UI m_diPushed;
        TDRAWINFO_UI m_diFocused;
        TDRAWINFO_UI m_diSep;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListElementUI : public CControlUI, public IListItemUI
    {
    public:
        CListElementUI();

        LPCTSTR GetClass() const;
        UINT GetControlFlags() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        void SetEnabled(BOOL bEnable = TRUE);

        int GetIndex() const;
        void SetIndex(int iIndex);
        int GetDrawIndex() const;
        void SetDrawIndex(int iIndex);

        IListOwnerUI* GetOwner();
        void SetOwner(CControlUI* pOwner);
        void SetVisible(BOOL bVisible = TRUE);

        BOOL IsSelected() const;
        BOOL Select(BOOL bSelect = TRUE, BOOL bTriggerEvent = TRUE);
        BOOL IsExpanded() const;
        BOOL Expand(BOOL bExpand = TRUE);

        void Invalidate(); // 直接CControl::Invalidate会导致滚动条刷新，重写减少刷新区域
        BOOL Activate();

        void DoEvent(TEVENT_UI& event);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        void DrawItemBk(HDC hDC, const RECT& rcItem);

    protected:
        int m_iIndex;
        int m_iDrawIndex;
        BOOL m_bSelected;
        UINT m_uButtonState;
        IListOwnerUI* m_pOwner;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListLabelElementUI : public CListElementUI
    {
    public:
        CListLabelElementUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        void SetOwner(CControlUI* pOwner);

        void SetFixedWidth(int cx);
        void SetFixedHeight(int cy);
        void SetText(LPCTSTR pstrText);

        void DoEvent(TEVENT_UI& event);
        SIZE EstimateSize(SIZE szAvailable);
        BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

        void DrawItemText(HDC hDC, const RECT& rcItem);

    protected:
        SIZE    m_cxyFixedLast;
        BOOL    m_bNeedEstimateSize;

        SIZE    m_szAvailableLast;
        UINT    m_uFixedHeightLast;
        int     m_nFontLast;
        UINT    m_uTextStyleLast;
        RECT    m_rcTextPaddingLast;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListTextElementUI : public CListLabelElementUI
    {
    public:
        CListTextElementUI();
        ~CListTextElementUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);
        UINT GetControlFlags() const;

        LPCTSTR GetText(int iIndex) const;
        void SetText(int iIndex, LPCTSTR pstrText);

        void SetOwner(CControlUI* pOwner);
        CStringUI* GetLinkContent(int iIndex);

        void DoEvent(TEVENT_UI& event);
        SIZE EstimateSize(SIZE szAvailable);

        void DrawItemText(HDC hDC, const RECT& rcItem);

    protected:
        enum { MAX_LINK = 8 };
        int m_nLinks;
        RECT m_rcLinks[MAX_LINK];
        CStringUI m_sLinks[MAX_LINK];
        int m_nHoverLink;
        IListUI* m_pOwner;
        CPtrArrayUI m_aTexts;

        CStringUI m_sTextLast;
    };

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListContainerElementUI : public CContainerUI, public IListItemUI
    {
    public:
        CListContainerElementUI();

        LPCTSTR GetClass() const;
        UINT GetControlFlags() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        int GetIndex() const;
        void SetIndex(int iIndex);
        int GetDrawIndex() const;
        void SetDrawIndex(int iIndex);

        IListOwnerUI* GetOwner();
        void SetOwner(CControlUI* pOwner);
        void SetVisible(BOOL bVisible = TRUE);
        void SetEnabled(BOOL bEnable = TRUE);

        BOOL IsSelected() const;
        BOOL Select(BOOL bSelect = TRUE, BOOL bTriggerEvent = TRUE);
        BOOL IsExpandable() const;
        void SetExpandable(BOOL bExpandable);
        BOOL IsExpanded() const;
        BOOL Expand(BOOL bExpand = TRUE);

        void Invalidate(); // 直接CControl::Invalidate会导致滚动条刷新，重写减少刷新区域
        BOOL Activate();

        void DoEvent(TEVENT_UI& event);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

        void DrawItemText(HDC hDC, const RECT& rcItem);
        void DrawItemBk(HDC hDC, const RECT& rcItem);

        SIZE EstimateSize(SIZE szAvailable);

    protected:
        int m_iIndex;
        int m_iDrawIndex;
        BOOL m_bSelected;
        BOOL m_bExpandable;
        BOOL m_bExpand;
        UINT m_uButtonState;
        IListOwnerUI* m_pOwner;
    };

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CListHBoxElementUI : public CListContainerElementUI
    {
    public:
        CListHBoxElementUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
    };

} // namespace DUILIB

#endif // __UILIST_H__
