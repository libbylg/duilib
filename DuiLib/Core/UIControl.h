#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#include "Core/UIDefine.h"
#include "Core/UIRender.h"
#include "Utils/UIDelegate.h"

namespace DUILIB
{

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class CControlUI;
    class CManagerUI;
    struct TDRAWINFO_UI;

    typedef CControlUI* (CALLBACK* LPFINDCONTROLPROC_UI)(CControlUI*, LPVOID);

    // Structure for notifications from the system
    // to the control implementation.
    struct DUILIB_API TEVENT_UI
    {
        int             Type;
        CControlUI* pSender;
        DWORD           dwTimestamp;
        POINT           ptMouse;
        TCHAR           chKey;
        WORD            wKeyState;
        WPARAM          wParam;
        LPARAM          lParam;
    };



    class DUILIB_API CControlUI
    {
    public:
        CControlUI();
        virtual void Delete();

    protected:
        virtual ~CControlUI();

    public:
        virtual CStringUI GetName() const;
        virtual void SetName(LPCTSTR pstrName);
        virtual LPCTSTR GetClass() const;
        virtual LPVOID GetInterface(LPCTSTR pstrName);
        virtual UINT GetControlFlags() const;
        virtual HWND GetNativeWindow() const;

        virtual BOOL Activate();
        virtual CManagerUI* GetManager() const;
        virtual void SetManager(CManagerUI* pManager, CControlUI* pParent, BOOL bInit = TRUE);
        virtual CControlUI* GetParent() const;
        virtual CControlUI* GetCover() const;
        virtual void SetCover(CControlUI* pControl);

        // 文本相关
        virtual CStringUI GetText() const;
        virtual void SetText(LPCTSTR pstrText);

        // 图形相关
        DWORD GetBkColor() const;
        void SetBkColor(DWORD dwBackColor);
        DWORD GetBkColor2() const;
        void SetBkColor2(DWORD dwBackColor);
        DWORD GetBkColor3() const;
        void SetBkColor3(DWORD dwBackColor);
        LPCTSTR GetBkImage();
        void SetBkImage(LPCTSTR pStrImage);
        DWORD GetFocusBorderColor() const;
        void SetFocusBorderColor(DWORD dwBorderColor);
        BOOL IsColorHSL() const;
        void SetColorHSL(BOOL bColorHSL);
        SIZE GetBorderRound() const;
        void SetBorderRound(SIZE cxyRound);
        BOOL DrawImage(HDC hDC, TDRAWINFO_UI& drawInfo);

        //边框相关
        DWORD GetBorderColor() const;
        void SetBorderColor(DWORD dwBorderColor);
        RECT GetBorderSize() const;
        void SetBorderSize(RECT rc);
        void SetBorderSize(int iSize);
        int GetBorderStyle() const;
        void SetBorderStyle(int nStyle);

        // 位置相关
        virtual const RECT& GetPos() const;
        virtual RECT GetRelativePos() const; // 相对(父控件)位置
        virtual RECT GetClientPos() const; // 客户区域（除去scrollbar和inset）
        // 只有控件为float的时候，外部调用SetPos和Move才是有效的，位置参数是相对父控件的位置
        virtual void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        virtual void Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
        virtual int GetWidth() const;
        virtual int GetHeight() const;
        virtual int GetX() const;
        virtual int GetY() const;
        virtual RECT GetPadding() const;
        virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
        virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
        virtual void SetFixedXY(SIZE szXY);      // 仅float为TRUE时有效
        virtual struct TPERCENTINFO_UI GetFloatPercent() const;
        virtual void SetFloatPercent(struct TPERCENTINFO_UI piFloatPercent);
        virtual int GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
        virtual void SetFixedWidth(int cx);      // 预设的参考值
        virtual int GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
        virtual void SetFixedHeight(int cy);     // 预设的参考值
        virtual int GetMinWidth() const;
        virtual void SetMinWidth(int cx);
        virtual int GetMaxWidth() const;
        virtual void SetMaxWidth(int cx);
        virtual int GetMinHeight() const;
        virtual void SetMinHeight(int cy);
        virtual int GetMaxHeight() const;
        virtual void SetMaxHeight(int cy);

        // 鼠标提示
        virtual CStringUI GetToolTip() const;
        virtual void SetToolTip(LPCTSTR pstrText);
        virtual void SetToolTipWidth(int nWidth);
        virtual int	  GetToolTipWidth(void);	// 多行ToolTip单行最长宽度

        // 快捷键
        virtual TCHAR GetShortcut() const;
        virtual void SetShortcut(TCHAR ch);

        // 菜单
        virtual BOOL IsContextMenuUsed() const;
        virtual void SetContextMenuUsed(BOOL bMenuUsed);

        // 用户属性
        virtual const CStringUI& GetUserData(); // 辅助函数，供用户使用
        virtual void SetUserData(LPCTSTR pstrText); // 辅助函数，供用户使用
        virtual UINT_PTR GetTag() const; // 辅助函数，供用户使用
        virtual void SetTag(UINT_PTR pTag); // 辅助函数，供用户使用

        // 一些重要的属性
        virtual BOOL IsVisible() const;
        virtual void SetVisible(BOOL bVisible = TRUE);
        virtual void SetInternVisible(BOOL bVisible = TRUE); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
        virtual BOOL IsEnabled() const;
        virtual void SetEnabled(BOOL bEnable = TRUE);
        virtual BOOL IsMouseEnabled() const;
        virtual void SetMouseEnabled(BOOL bEnable = TRUE);
        virtual BOOL IsKeyboardEnabled() const;
        virtual void SetKeyboardEnabled(BOOL bEnable = TRUE);
        virtual BOOL IsFocused() const;
        virtual void SetFocus();
        virtual BOOL IsFloat() const;
        virtual void SetFloat(BOOL bFloat = TRUE);

        // 自定义(未处理的)属性
        void AddCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
        LPCTSTR GetCustomAttribute(LPCTSTR pstrName) const;
        BOOL RemoveCustomAttribute(LPCTSTR pstrName);
        void RemoveAllCustomAttribute();

        virtual CControlUI* FindControl(LPFINDCONTROLPROC_UI Proc, LPVOID pData, UINT uFlags);

        void Invalidate();
        BOOL IsUpdateNeeded() const;
        void NeedUpdate();
        void NeedParentUpdate();
        DWORD GetAdjustColor(DWORD dwColor);

        virtual void Init();
        virtual void DoInit();

        virtual void Event(struct TEVENT_UI& event);
        virtual void DoEvent(struct TEVENT_UI& event);

        virtual CStringUI GetAttribute(LPCTSTR pstrName);
        virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        virtual CStringUI GetAttributeList(BOOL bIgnoreDefault = TRUE);
        virtual void SetAttributeList(LPCTSTR pstrList);

        virtual SIZE EstimateSize(SIZE szAvailable);

        virtual BOOL Paint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl = NULL); // 返回要不要继续绘制
        virtual BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
        virtual void PaintBkColor(HDC hDC);
        virtual void PaintBkImage(HDC hDC);
        virtual void PaintStatusImage(HDC hDC);
        virtual void PaintText(HDC hDC);
        virtual void PaintBorder(HDC hDC);

        virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);

        //虚拟窗口参数
        void SetVirtualWnd(LPCTSTR pstrValue);
        CStringUI GetVirtualWnd() const;

    public:
        CEventSource OnInit;
        CEventSource OnDestroy;
        CEventSource OnSize;
        CEventSource OnEvent;
        CEventSource OnNotify;
        CEventSource OnPaint;
        CEventSource OnPostPaint;

    protected:
        CManagerUI* m_pManager;
        CControlUI* m_pParent;
        CControlUI* m_pCover;
        CStringUI m_sVirtualWnd;
        CStringUI m_sName;
        BOOL m_bUpdateNeeded;
        BOOL m_bMenuUsed;
        BOOL m_bAsyncNotify;
        RECT m_rcItem;
        RECT m_rcPadding;
        SIZE m_cXY;
        SIZE m_cxyFixed;
        SIZE m_cxyMin;
        SIZE m_cxyMax;
        BOOL m_bVisible;
        BOOL m_bInternVisible;
        BOOL m_bEnabled;
        BOOL m_bMouseEnabled;
        BOOL m_bKeyboardEnabled;
        BOOL m_bFocused;
        BOOL m_bFloat;
        struct TPERCENTINFO_UI m_piFloatPercent;
        BOOL m_bSetPos; // 防止SetPos循环调用

        CStringUI m_sText;
        CStringUI m_sToolTip;
        TCHAR m_chShortcut;
        CStringUI m_sUserData;
        UINT_PTR m_pTag;

        DWORD m_dwBackColor;
        DWORD m_dwBackColor2;
        DWORD m_dwBackColor3;
        TDRAWINFO_UI m_diBk;
        TDRAWINFO_UI m_diFore;
        DWORD m_dwBorderColor;
        DWORD m_dwFocusBorderColor;
        BOOL m_bColorHSL;
        int m_nBorderStyle;
        int m_nTooltipWidth;
        SIZE m_cxyBorderRound;
        RECT m_rcPaint;
        RECT m_rcBorderSize;
        CStringPtrMapUI m_mCustomAttrHash;
    };

} // namespace DUILIB

#endif // __UICONTROL_H__
