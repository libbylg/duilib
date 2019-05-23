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
        virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
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
        bool IsUpdateNeeded() const;
        void NeedUpdate();
        void Invalidate();
        void Invalidate(RECT& rcItem);

        LPCTSTR GetName() const;
        HDC GetPaintDC() const;
        HBITMAP GetPaintOffscreenBitmap();
        HWND GetPaintWindow() const;
        HWND GetTooltipWindow() const;
        int GetTooltipWindowWidth() const;
        void SetTooltipWindowWidth(int iWidth);
        int GetHoverTime() const;
        void SetHoverTime(int iTime);

        POINT GetMousePos() const;
        SIZE GetClientSize() const;
        SIZE GetInitSize();
        void SetInitSize(int cx, int cy);
        RECT& GetSizeBox();
        void SetSizeBox(RECT& rcSizeBox);
        RECT& GetCaptionRect();
        void SetCaptionRect(RECT& rcCaption);
        SIZE GetRoundCorner() const;
        void SetRoundCorner(int cx, int cy);
        SIZE GetMinInfo() const;
        void SetMinInfo(int cx, int cy);
        SIZE GetMaxInfo() const;
        void SetMaxInfo(int cx, int cy);
        bool IsShowUpdateRect() const;
        void SetShowUpdateRect(bool show);
        bool IsNoActivate();
        void SetNoActivate(bool bNoActivate);

        BYTE GetOpacity() const;
        void SetOpacity(BYTE nOpacity);

        bool IsLayered();
        void SetLayered(bool bLayered);
        RECT& GetLayeredInset();
        void SetLayeredInset(RECT& rcLayeredInset);
        BYTE GetLayeredOpacity();
        void SetLayeredOpacity(BYTE nOpacity);
        LPCTSTR GetLayeredImage();
        void SetLayeredImage(LPCTSTR pstrImage);

        static HINSTANCE GetInstance();
        static CStringUI GetInstancePath();
        static CStringUI GetCurrentPath();
        static HINSTANCE GetResourceDll();
        static const CStringUI& GetResourcePath();
        static const CStringUI& GetResourceZip();
        static bool IsCachedResourceZip();
        static HANDLE GetResourceZipHandle();
        static void SetInstance(HINSTANCE hInst);
        static void SetCurrentPath(LPCTSTR pStrPath);
        static void SetResourceDll(HINSTANCE hInst);
        static void SetResourcePath(LPCTSTR pStrPath);
        static void SetResourceZip(LPVOID pVoid, unsigned int len);
        static void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);
        static bool GetHSL(short* H, short* S, short* L);
        static void SetHSL(bool bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
        static void ReloadSkin();
        static CManagerUI* GetPaintManager(LPCTSTR pstrName);
        static CPtrArrayUI* GetPaintManagers();
        static bool LoadPlugin(LPCTSTR pstrModuleName);
        static CPtrArrayUI* GetPlugins();

        bool IsForceUseSharedRes() const;
        void SetForceUseSharedRes(bool bForce);

        DWORD GetDefaultDisabledColor() const;
        void SetDefaultDisabledColor(DWORD dwColor, bool bShared = false);
        DWORD GetDefaultFontColor() const;
        void SetDefaultFontColor(DWORD dwColor, bool bShared = false);
        DWORD GetDefaultLinkFontColor() const;
        void SetDefaultLinkFontColor(DWORD dwColor, bool bShared = false);
        DWORD GetDefaultLinkHoverFontColor() const;
        void SetDefaultLinkHoverFontColor(DWORD dwColor, bool bShared = false);
        DWORD GetDefaultSelectedBkColor() const;
        void SetDefaultSelectedBkColor(DWORD dwColor, bool bShared = false);

        TFONTINFO_UI* GetDefaultFontInfo();
        void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);
        DWORD GetCustomFontCount(bool bShared = false) const;
        HFONT AddFont(int id, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);
        HFONT GetFont(int id);
        HFONT GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
        int GetFontIndex(HFONT hFont, bool bShared = false);
        int GetFontIndex(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);
        void RemoveFont(HFONT hFont, bool bShared = false);
        void RemoveFont(int id, bool bShared = false);
        void RemoveAllFonts(bool bShared = false);
        TFONTINFO_UI* GetFontInfo(int id);
        TFONTINFO_UI* GetFontInfo(HFONT hFont);

        const TIMAGEINFO_UI* GetImage(LPCTSTR bitmap);
        const TIMAGEINFO_UI* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bUseHSL = false);
        const TIMAGEINFO_UI* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bUseHSL = false, bool bShared = false);
        const TIMAGEINFO_UI* AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha, bool bShared = false);
        void RemoveImage(LPCTSTR bitmap, bool bShared = false);
        void RemoveAllImages(bool bShared = false);
        static void ReloadSharedImages();
        void ReloadImages();

        void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList, bool bShared = false);
        LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;
        bool RemoveDefaultAttributeList(LPCTSTR pStrControlName, bool bShared = false);
        void RemoveAllDefaultAttributeList(bool bShared = false);

        void AddWindowCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
        LPCTSTR GetWindowCustomAttribute(LPCTSTR pstrName) const;
        bool RemoveWindowCustomAttribute(LPCTSTR pstrName);
        void RemoveAllWindowCustomAttribute();

        CStringUI GetWindowAttribute(LPCTSTR pstrName);
        void SetWindowAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        CStringUI GetWindowAttributeList(bool bIgnoreDefault = true);
        void SetWindowAttributeList(LPCTSTR pstrList);
        bool RemoveWindowAttribute(LPCTSTR pstrName);

        CStringUI GetWindowXML();

        static void AddMultiLanguageString(int id, LPCTSTR pStrMultiLanguage);
        static LPCTSTR GetMultiLanguageString(int id);
        static bool RemoveMultiLanguageString(int id);
        static void RemoveAllMultiLanguageString();
        static void ProcessMultiLanguageTokens(CStringUI& pStrMultiLanguage);

        bool AttachDialog(CControlUI* pControl);
        bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
        bool RenameControl(CControlUI* pControl, LPCTSTR pstrName);
        void ReapObjects(CControlUI* pControl);

        bool AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
        CPtrArrayUI* GetOptionGroup(LPCTSTR pStrGroupName);
        void RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
        void RemoveAllOptionGroups();

        CControlUI* GetFocus() const;
        void SetFocus(CControlUI* pControl, bool bFocusWnd = true);
        void SetFocusNeeded(CControlUI* pControl);

        bool SetNextTabControl(bool bForward = true);

        bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
        bool KillTimer(CControlUI* pControl, UINT nTimerID);
        void KillTimer(CControlUI* pControl);
        void RemoveAllTimers();

        void SetCapture();
        void ReleaseCapture();
        bool IsCaptured();

        bool IsPainting();
        void SetPainting(bool bIsPainting);

        bool AddNotifier(INotifyUI* pControl);
        bool RemoveNotifier(INotifyUI* pControl);
        void SendNotify(struct TNOTIFY_UI& Msg, bool bAsync = false, bool bEnableRepeat = true);
        void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false, bool bEnableRepeat = true);

        bool AddPreMessageFilter(IMessageFilterUI* pFilter);
        bool RemovePreMessageFilter(IMessageFilterUI* pFilter);

        bool AddMessageFilter(IMessageFilterUI* pFilter);
        bool RemoveMessageFilter(IMessageFilterUI* pFilter);

        int GetPostPaintCount() const;
        bool AddPostPaint(CControlUI* pControl);
        bool RemovePostPaint(CControlUI* pControl);
        bool SetPostPaintIndex(CControlUI* pControl, int iIndex);

        int GetNativeWindowCount() const;
        RECT GetNativeWindowRect(HWND hChildWnd);
        bool AddNativeWindow(CControlUI* pControl, HWND hChildWnd);
        bool RemoveNativeWindow(HWND hChildWnd);

        void AddDelayedCleanup(CControlUI* pControl);
        void AddMouseLeaveNeeded(CControlUI* pControl);
        bool RemoveMouseLeaveNeeded(CControlUI* pControl);

        bool AddTranslateAccelerator(ITranslateAccelerator* pTranslateAccelerator);
        bool RemoveTranslateAccelerator(ITranslateAccelerator* pTranslateAccelerator);
        bool TranslateAccelerator(LPMSG pMsg);

        CControlUI* GetRoot() const;
        CControlUI* FindControl(POINT pt) const;
        CControlUI* FindControl(LPCTSTR pstrName) const;
        CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
        CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
        CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
        CPtrArrayUI* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);

        static void MessageLoop();
        static bool TranslateMessage(const LPMSG pMsg);
        static void Term();

        bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
        bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
        void UsedVirtualWnd(bool bUsed);

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
        bool m_bNoActivate;
        bool m_bShowUpdateRect;
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
        bool m_bFirstLayout;
        bool m_bUpdateNeeded;
        bool m_bFocusNeeded;
        bool m_bOffscreenPaint;

        BYTE m_nOpacity;
        bool m_bLayered;
        RECT m_rcLayeredInset;
        bool m_bLayeredChanged;
        RECT m_rcLayeredUpdate;
        struct TDRAWINFO_UI m_diLayered;

        bool m_bMouseTracking;
        bool m_bMouseCapture;
        bool m_bIsPainting;
        bool m_bUsedVirtualWnd;
        bool m_bAsyncNotifyPosted;

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
        bool m_bForceUseSharedRes;
        struct TRESINFO_UI m_ResInfo;

        //
        static HINSTANCE m_hResourceInstance;
        static CStringUI m_pStrResourcePath;
        static CStringUI m_pStrResourceZip;
        static HANDLE m_hResourceZip;

        static bool m_bCachedResourceZip;
        static TRESINFO_UI m_SharedResInfo;
        static HINSTANCE m_hInstance;
        static bool m_bUseHSL;
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
