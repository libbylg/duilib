#ifndef __UICOMBO_H__
#define __UICOMBO_H__

#include "Control/UIList.h"
#include "Core/UIContainer.h"

namespace DUILIB
{
    /////////////////////////////////////////////////////////////////////////////////////
    //

    class CComboWnd;

    class DUILIB_API CComboUI : public CContainerUI, public IListOwnerUI
    {
        friend class CComboWnd;
    public:
        CComboUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        void DoInit();
        UINT GetControlFlags() const;

        CStringUI GetText() const;
        void SetEnabled(BOOL bEnable = TRUE);

        CStringUI GetDropBoxAttributeList();
        void SetDropBoxAttributeList(LPCTSTR pstrList);
        SIZE GetDropBoxSize() const;
        void SetDropBoxSize(SIZE szDropBox);

        int GetCurSel() const;
        BOOL GetSelectCloseFlag();
        void SetSelectCloseFlag(BOOL flag);
        BOOL SelectItem(int iIndex, BOOL bTakeFocus = FALSE, BOOL bTriggerEvent = TRUE);
        BOOL ExpandItem(int iIndex, BOOL bExpand = TRUE);
        int GetExpandedItem() const;

        BOOL SetItemIndex(CControlUI* pControl, int iNewIndex);
        BOOL SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
        BOOL Add(CControlUI* pControl);
        BOOL AddAt(CControlUI* pControl, int iIndex);
        BOOL Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
        BOOL RemoveAt(int iIndex, BOOL bDoNotDestroy = FALSE);
        void RemoveAll();

        BOOL Activate();

        BOOL GetShowText() const;
        void SetShowText(BOOL flag);
        RECT GetTextPadding() const;
        void SetTextPadding(RECT rc);
        LPCTSTR GetNormalImage() const;
        void SetNormalImage(LPCTSTR pStrImage);
        LPCTSTR GetHotImage() const;
        void SetHotImage(LPCTSTR pStrImage);
        LPCTSTR GetPushedImage() const;
        void SetPushedImage(LPCTSTR pStrImage);
        LPCTSTR GetFocusedImage() const;
        void SetFocusedImage(LPCTSTR pStrImage);
        LPCTSTR GetDisabledImage() const;
        void SetDisabledImage(LPCTSTR pStrImage);

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

        SIZE EstimateSize(SIZE szAvailable);
        void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        void Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
        void DoEvent(TEVENT_UI& event);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
        void PaintText(HDC hDC);
        void PaintStatusImage(HDC hDC);

    protected:
        CComboWnd* m_pWindow;

        int m_iCurSel;
        BOOL m_bShowText;
        BOOL m_bSelectCloseFlag;
        RECT m_rcTextPadding;
        CStringUI m_sDropBoxAttributes;
        SIZE m_szDropBox;
        UINT m_uButtonState;

        TDRAWINFO_UI m_diNormal;
        TDRAWINFO_UI m_diHot;
        TDRAWINFO_UI m_diPushed;
        TDRAWINFO_UI m_diFocused;
        TDRAWINFO_UI m_diDisabled;

        TListInfoUI m_ListInfo;
    };

} // namespace DUILIB

#endif // __UICOMBO_H__
