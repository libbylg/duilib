#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include "Core/UIDefine.h"
#include "Core/UIRender.h"

namespace DUILIB
{
    /////////////////////////////////////////////////////////////////////////////////////
    //

    class CControlUI;




    /////////////////////////////////////////////////////////////////////////////////////
    //



    // MessageFilter interface
    class DUILIB_API IMessageFilterUI
    {
    public:
        virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) = 0;
    };

    class DUILIB_API ITranslateAccelerator
    {
    public:
        virtual LRESULT TranslateAccelerator(MSG* pMsg) = 0;
    };

    // Listener interface
    class DUILIB_API INotifyUI
    {
    public:
        virtual void Notify(struct TNOTIFY_UI& msg) = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////
    //
    typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);


    class DUILIB_API CManagerUI
    {
    public:
        CManagerUI();
        ~CManagerUI();

    public:
        void Init(HWND hWnd, LPCTSTR pstrName = NULL);
        BOOL IsUpdateNeeded() const;
        void NeedUpdate();
        void Invalidate();
        void Invalidate(RECT& rcItem);

        LPCTSTR GetName() const;
        HDC     GetPaintDC() const;
        HBITMAP GetPaintOffscreenBitmap();
        HWND    GetPaintWindow() const;
        HWND    GetTooltipWindow() const;
        int     GetTooltipWindowWidth() const;
        void    SetTooltipWindowWidth(int iWidth);
        int     GetHoverTime() const;
        void    SetHoverTime(int iTime);

        POINT   GetMousePos() const;
        SIZE    GetClientSize() const;
        SIZE    GetInitSize();
        void    SetInitSize(int cx, int cy);
        RECT&   GetSizeBox();
        void    SetSizeBox(RECT& rcSizeBox);
        RECT&   GetCaptionRect();
        void    SetCaptionRect(RECT& rcCaption);
        SIZE    GetRoundCorner() const;
        void    SetRoundCorner(int cx, int cy);
        SIZE    GetMinInfo() const;
        void    SetMinInfo(int cx, int cy);
        SIZE    GetMaxInfo() const;
        void    SetMaxInfo(int cx, int cy);
        BOOL    IsShowUpdateRect() const;
        void    SetShowUpdateRect(BOOL show);
        BOOL    IsNoActivate();
        void    SetNoActivate(BOOL bNoActivate);

        BYTE    GetOpacity() const;
        void    SetOpacity(BYTE nOpacity);

        BOOL    IsLayered();
        void    SetLayered(BOOL bLayered);
        RECT&   GetLayeredInset();
        void    SetLayeredInset(RECT& rcLayeredInset);
        BYTE    GetLayeredOpacity();
        void    SetLayeredOpacity(BYTE nOpacity);
        LPCTSTR GetLayeredImage();
        void    SetLayeredImage(LPCTSTR pstrImage);

        static HINSTANCE        GetInstance();
        static void             SetInstance(HINSTANCE hInst);
        static CStringUI        GetInstancePath();
        static CStringUI        GetCurrentPath();
        static void             SetCurrentPath(LPCTSTR pStrPath);

        static HINSTANCE        GetResourceDll();
        static const CStringUI& GetResourcePath();
        static const CStringUI& GetResourceZip();
        static BOOL             IsCachedResourceZip();
        static HANDLE           GetResourceZipHandle();
        static void             SetResourceDll(HINSTANCE hInst);
        static void             SetResourcePath(LPCTSTR pStrPath);
        static void             SetResourceZip(LPVOID pVoid, unsigned int len);
        static void             SetResourceZip(LPCTSTR pstrZip, BOOL bCachedResourceZip = FALSE);
        static BOOL             GetHSL(short* H, short* S, short* L);
        static void             SetHSL(BOOL bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
        static void             ReloadSkin();

        static CManagerUI*      GetManager(LPCTSTR pstrName);
        static CPtrArrayUI*     GetPaintManagers();
        static BOOL             LoadPlugin(LPCTSTR pstrModuleName);
        static CPtrArrayUI*     GetPlugins();

        BOOL            IsForceUseSharedRes() const;
        void            SetForceUseSharedRes(BOOL bForce);

        //  »± °…Ë÷√
        DWORD           GetDefaultDisabledColor() const;
        void            SetDefaultDisabledColor(DWORD dwColor, BOOL bShared = FALSE);
        DWORD           GetDefaultFontColor() const;
        void            SetDefaultFontColor(DWORD dwColor, BOOL bShared = FALSE);
        DWORD           GetDefaultLinkFontColor() const;
        void            SetDefaultLinkFontColor(DWORD dwColor, BOOL bShared = FALSE);
        DWORD           GetDefaultLinkHoverFontColor() const;
        void            SetDefaultLinkHoverFontColor(DWORD dwColor, BOOL bShared = FALSE);
        DWORD           GetDefaultSelectedBkColor() const;
        void            SetDefaultSelectedBkColor(DWORD dwColor, BOOL bShared = FALSE);

        //  
        TFONTINFO_UI*   GetDefaultFontInfo();
        void            SetDefaultFont(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bShared = FALSE);
        DWORD           GetCustomFontCount(BOOL bShared = FALSE) const;
        HFONT           AddFont(int id, LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bShared = FALSE);
        HFONT           GetFont(int id);
        HFONT           GetFont(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic);
        int             GetFontIndex(HFONT hFont, BOOL bShared = FALSE);
        int             GetFontIndex(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bShared = FALSE);
        void            RemoveFont(HFONT hFont, BOOL bShared = FALSE);
        void            RemoveFont(int id, BOOL bShared = FALSE);
        void            RemoveAllFonts(BOOL bShared = FALSE);
        TFONTINFO_UI*   GetFontInfo(int id);
        TFONTINFO_UI*   GetFontInfo(HFONT hFont);

        const TIMAGEINFO_UI*    GetImage(LPCTSTR bitmap);
        const TIMAGEINFO_UI*    GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, BOOL bUseHSL = FALSE);
        const TIMAGEINFO_UI*    AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, BOOL bUseHSL = FALSE, BOOL bShared = FALSE);
        const TIMAGEINFO_UI*    AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, BOOL bAlpha, BOOL bShared = FALSE);
        void                    RemoveImage(LPCTSTR bitmap, BOOL bShared = FALSE);
        void                    RemoveAllImages(BOOL bShared = FALSE);
        static void             ReloadSharedImages();
        void                    ReloadImages();

        void        AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList, BOOL bShared = FALSE);
        LPCTSTR     GetDefaultAttributeList(LPCTSTR pStrControlName) const;
        BOOL        RemoveDefaultAttributeList(LPCTSTR pStrControlName, BOOL bShared = FALSE);
        void        RemoveAllDefaultAttributeList(BOOL bShared = FALSE);

        void        AddWindowCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
        LPCTSTR     GetWindowCustomAttribute(LPCTSTR pstrName) const;
        BOOL        RemoveWindowCustomAttribute(LPCTSTR pstrName);
        void        RemoveAllWindowCustomAttribute();

        CStringUI   GetWindowAttribute(LPCTSTR pstrName);
        void        SetWindowAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        CStringUI   GetWindowAttributeList(BOOL bIgnoreDefault = TRUE);
        void        SetWindowAttributeList(LPCTSTR pstrList);
        BOOL        RemoveWindowAttribute(LPCTSTR pstrName);

        CStringUI   GetWindowXML();

        static void     AddMultiLanguageString(int id, LPCTSTR pStrMultiLanguage);
        static LPCTSTR  GetMultiLanguageString(int id);
        static BOOL     RemoveMultiLanguageString(int id);
        static void     RemoveAllMultiLanguageString();
        static void     ProcessMultiLanguageTokens(CStringUI& pStrMultiLanguage);

        BOOL AttachDialog(CControlUI* pControl);
        BOOL InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
        BOOL RenameControl(CControlUI* pControl, LPCTSTR pstrName);
        void ReapObjects(CControlUI* pControl);

        BOOL            AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
        CPtrArrayUI*    GetOptionGroup(LPCTSTR pStrGroupName);
        void            RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
        void            RemoveAllOptionGroups();

        CControlUI*     GetFocus() const;
        void            SetFocus(CControlUI* pControl, BOOL bFocusWnd = TRUE);
        void            SetFocusNeeded(CControlUI* pControl);

        BOOL    SetNextTabControl(BOOL bForward = TRUE);

        BOOL    SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
        BOOL    KillTimer(CControlUI* pControl, UINT nTimerID);
        void    KillTimer(CControlUI* pControl);
        void    RemoveAllTimers();

        void    SetCapture();
        void    ReleaseCapture();
        BOOL    IsCaptured();

        BOOL    IsPainting();
        void    SetPainting(BOOL bIsPainting);

        BOOL AddNotifier(INotifyUI* pControl);
        BOOL RemoveNotifier(INotifyUI* pControl);
        void SendNotify(struct TNOTIFY_UI& Msg, BOOL bAsync = FALSE, BOOL bEnableRepeat = TRUE);
        void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bAsync = FALSE, BOOL bEnableRepeat = TRUE);

        BOOL AddPreMessageFilter(IMessageFilterUI* pFilter);
        BOOL RemovePreMessageFilter(IMessageFilterUI* pFilter);

        BOOL AddMessageFilter(IMessageFilterUI* pFilter);
        BOOL RemoveMessageFilter(IMessageFilterUI* pFilter);

        int GetPostPaintCount() const;
        BOOL AddPostPaint(CControlUI* pControl);
        BOOL RemovePostPaint(CControlUI* pControl);
        BOOL SetPostPaintIndex(CControlUI* pControl, int iIndex);

        int GetNativeWindowCount() const;
        RECT GetNativeWindowRect(HWND hChildWnd);
        BOOL AddNativeWindow(CControlUI* pControl, HWND hChildWnd);
        BOOL RemoveNativeWindow(HWND hChildWnd);

        void AddDelayedCleanup(CControlUI* pControl);
        void AddMouseLeaveNeeded(CControlUI* pControl);
        BOOL RemoveMouseLeaveNeeded(CControlUI* pControl);

        BOOL AddTranslateAccelerator(ITranslateAccelerator* pTranslateAccelerator);
        BOOL RemoveTranslateAccelerator(ITranslateAccelerator* pTranslateAccelerator);
        BOOL TranslateAccelerator(LPMSG pMsg);

        CControlUI* GetRoot() const;
        CControlUI* FindControl(POINT pt) const;
        CControlUI* FindControl(LPCTSTR pstrName) const;
        CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
        CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
        CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
        CPtrArrayUI* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);

        static void MessageLoop();
        static BOOL TranslateMessage(const LPMSG pMsg);
        static void Term();

        BOOL MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
        BOOL PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
        void UsedVirtualWnd(BOOL bUsed);

    private:
        CPtrArrayUI* GetFoundControls();
        static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);
        static CControlUI* CALLBACK __FindControlsFromUpdate(CControlUI* pThis, LPVOID pData);

        static void AdjustSharedImagesHSL();
        void AdjustImagesHSL();
        void PostAsyncNotify();

    private:
        CStringUI m_sName;
        HWND m_hWndPaint;
        HDC m_hDcPaint;
        HDC m_hDcOffscreen;
        HDC m_hDcBackground;
        HBITMAP m_hbmpOffscreen;
        COLORREF* m_pOffscreenBits;
        HBITMAP m_hbmpBackground;
        COLORREF* m_pBackgroundBits;
        int m_iTooltipWidth;
        int m_iLastTooltipWidth;
        HWND m_hwndTooltip;
        TOOLINFO m_ToolTip;
        int m_iHoverTime;
        BOOL m_bNoActivate;
        BOOL m_bShowUpdateRect;
        //
        CControlUI* m_pRoot;
        CControlUI* m_pFocus;
        CControlUI* m_pEventHover;
        CControlUI* m_pEventClick;
        CControlUI* m_pEventKey;
        CControlUI* m_pLastToolTip;
        //
        POINT m_ptLastMousePos;
        SIZE m_szMinWindow;
        SIZE m_szMaxWindow;
        SIZE m_szInitWindowSize;
        RECT m_rcSizeBox;
        SIZE m_szRoundCorner;
        RECT m_rcCaption;
        UINT m_uTimerID;
        BOOL m_bFirstLayout;
        BOOL m_bUpdateNeeded;
        BOOL m_bFocusNeeded;
        BOOL m_bOffscreenPaint;

        BYTE m_nOpacity;
        BOOL m_bLayered;
        RECT m_rcLayeredInset;
        BOOL m_bLayeredChanged;
        RECT m_rcLayeredUpdate;
        struct TDRAWINFO_UI m_diLayered;

        BOOL m_bMouseTracking;
        BOOL m_bMouseCapture;
        BOOL m_bIsPainting;
        BOOL m_bUsedVirtualWnd;
        BOOL m_bAsyncNotifyPosted;

        //
        CPtrArrayUI m_aNotifiers;
        CPtrArrayUI m_aTimers;
        CPtrArrayUI m_aPreMessageFilters;
        CPtrArrayUI m_aMessageFilters;
        CPtrArrayUI m_aPostPaintControls;
        CPtrArrayUI m_aNativeWindow;
        CPtrArrayUI m_aNativeWindowControl;
        CPtrArrayUI m_aDelayedCleanup;
        CPtrArrayUI m_aAsyncNotify;
        CPtrArrayUI m_aFoundControls;
        CPtrArrayUI m_aNeedMouseLeaveNeeded;
        CStringPtrMapUI m_mNameHash;
        CStringPtrMapUI m_mWindowAttrHash;
        CStringPtrMapUI m_mOptionGroup;

        //
        BOOL m_bForceUseSharedRes;
        struct TRESINFO_UI m_ResInfo;

        //
        static HINSTANCE m_hResourceInstance;
        static CStringUI m_pStrResourcePath;
        static CStringUI m_pStrResourceZip;
        static HANDLE m_hResourceZip;

        static BOOL m_bCachedResourceZip;
        static TRESINFO_UI m_SharedResInfo;
        static HINSTANCE m_hInstance;
        static BOOL m_bUseHSL;
        static short m_H;
        static short m_S;
        static short m_L;
        static CPtrArrayUI m_aPreMessages;
        static CPtrArrayUI m_aPlugins;

    public:
        CPtrArrayUI m_aTranslateAccelerator;
    };

} // namespace DUILIB

#endif // __UIMANAGER_H__
