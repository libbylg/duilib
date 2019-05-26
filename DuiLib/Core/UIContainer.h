#ifndef __UICONTAINER_H__
#define __UICONTAINER_H__

#include "Core/UIControl.h"

namespace DUILIB
{
    /////////////////////////////////////////////////////////////////////////////////////
    //


    class IContainerUI
    {
    public:
        virtual CControlUI* GetItemAt(int iIndex) const = 0;
        virtual int GetItemIndex(CControlUI* pControl) const = 0;
        virtual BOOL SetItemIndex(CControlUI* pControl, int iNewIndex) = 0;
        virtual BOOL SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex) = 0;
        virtual int GetCount() const = 0;
        virtual BOOL Add(CControlUI* pControl) = 0;
        virtual BOOL AddAt(CControlUI* pControl, int iIndex) = 0;
        virtual BOOL Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE) = 0;
        virtual BOOL RemoveAt(int iIndex, BOOL bDoNotDestroy = FALSE) = 0;
        virtual void RemoveAll() = 0;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //
    class CScrollUI;

    class DUILIB_API CContainerUI : public CControlUI, public IContainerUI
    {
    public:
        CContainerUI();
        virtual ~CContainerUI();

    public:
        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        CControlUI* GetItemAt(int iIndex) const;
        int GetItemIndex(CControlUI* pControl) const;
        BOOL SetItemIndex(CControlUI* pControl, int iNewIndex);
        BOOL SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
        int GetCount() const;
        BOOL Add(CControlUI* pControl);
        BOOL AddAt(CControlUI* pControl, int iIndex);
        BOOL Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
        BOOL RemoveAt(int iIndex, BOOL bDoNotDestroy = FALSE);
        void RemoveAll();

        void DoEvent(struct TEVENT_UI& event);
        void SetVisible(BOOL bVisible = TRUE);
        void SetInternVisible(BOOL bVisible = TRUE);
        void SetMouseEnabled(BOOL bEnable = TRUE);

        virtual RECT GetInset() const;
        virtual void SetInset(RECT rcInset); // 设置内边距，相当于设置客户区
        virtual int GetChildPadding() const;
        virtual void SetChildPadding(int iPadding);
        virtual UINT GetChildAlign() const;
        virtual void SetChildAlign(UINT iAlign);
        virtual UINT GetChildVAlign() const;
        virtual void SetChildVAlign(UINT iVAlign);
        virtual BOOL IsAutoDestroy() const;
        virtual void SetAutoDestroy(BOOL bAuto);
        virtual BOOL IsDelayedDestroy() const;
        virtual void SetDelayedDestroy(BOOL bDelayed);
        virtual BOOL IsMouseChildEnabled() const;
        virtual void SetMouseChildEnabled(BOOL bEnable = TRUE);

        virtual int FindSelectable(int iIndex, BOOL bForward = TRUE) const;

        RECT GetClientPos() const;
        void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        void Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
        BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        void SetManager(CManagerUI* pManager, CControlUI* pParent, BOOL bInit = TRUE);
        CControlUI* FindControl(LPFINDCONTROLPROC_UI Proc, LPVOID pData, UINT uFlags);

        BOOL SetSubControlText(LPCTSTR pstrSubControlName, LPCTSTR pstrText);
        BOOL SetSubControlFixedHeight(LPCTSTR pstrSubControlName, int cy);
        BOOL SetSubControlFixedWdith(LPCTSTR pstrSubControlName, int cx);
        BOOL SetSubControlUserData(LPCTSTR pstrSubControlName, LPCTSTR pstrText);

        CStringUI GetSubControlText(LPCTSTR pstrSubControlName);
        int GetSubControlFixedHeight(LPCTSTR pstrSubControlName);
        int GetSubControlFixedWdith(LPCTSTR pstrSubControlName);
        const CStringUI GetSubControlUserData(LPCTSTR pstrSubControlName);
        CControlUI* FindSubControl(LPCTSTR pstrSubControlName);

        virtual SIZE GetScrollPos() const;
        virtual SIZE GetScrollRange() const;
        virtual void SetScrollPos(SIZE szPos);
        virtual void LineUp();
        virtual void LineDown();
        virtual void PageUp();
        virtual void PageDown();
        virtual void HomeUp();
        virtual void EndDown();
        virtual void LineLeft();
        virtual void LineRight();
        virtual void PageLeft();
        virtual void PageRight();
        virtual void HomeLeft();
        virtual void EndRight();
        virtual void EnableScrollBar(BOOL bEnableVertical = TRUE, BOOL bEnableHorizontal = FALSE);
        virtual CScrollUI* GetVerticalScrollBar() const;
        virtual CScrollUI* GetHorizontalScrollBar() const;

    protected:
        virtual void SetFloatPos(int iIndex);
        virtual void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);

    protected:
        CPtrArrayUI m_items;
        RECT m_rcInset;
        int m_iChildPadding;
        UINT m_iChildAlign;
        UINT m_iChildVAlign;
        BOOL m_bAutoDestroy;
        BOOL m_bDelayedDestroy;
        BOOL m_bMouseChildEnabled;
        BOOL m_bScrollProcess; // 防止SetPos循环调用

        CScrollUI* m_pVerticalScrollBar;
        CScrollUI* m_pHorizontalScrollBar;
    };

} // namespace DUILIB

#endif // __UICONTAINER_H__
