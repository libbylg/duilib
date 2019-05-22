#ifndef __UIRENDER_H__
#define __UIRENDER_H__


#include "Core/UIDefine.h"


namespace DUILIB
{
    /////////////////////////////////////////////////////////////////////////////////////
    //
    struct DUILIB_API TFONTINFO_UI
    {
        HFONT hFont;
        CStringUI sFontName;
        int iSize;
        bool bBold;
        bool bUnderline;
        bool bItalic;
        TEXTMETRIC tm;
    };

    struct DUILIB_API TIMAGEINFO_UI
    {
        HBITMAP     hBitmap;
        LPBYTE      pBits;
        LPBYTE      pSrcBits;
        int         nX;
        int         nY;
        bool        bAlpha;
        bool        bUseHSL;
        CStringUI   sResType;
        DWORD       dwMask;
    };

    struct DUILIB_API TDRAWINFO_UI
    {
        TDRAWINFO_UI();
        TDRAWINFO_UI(LPCTSTR lpsz);
        void Clear();
        CStringUI sDrawString;
        CStringUI sImageName;
        bool bLoaded;
        const TIMAGEINFO_UI* pImageInfo;
        RECT rcDestOffset;
        RECT rcBmpPart;
        RECT rcScale9;
        BYTE uFade;
        bool bHole;
        bool bTiledX;
        bool bTiledY;
    };

    struct DUILIB_API TPERCENTINFO_UI
    {
        double left;
        double top;
        double right;
        double bottom;
    };

    struct DUILIB_API TRESINFO_UI
    {
        DWORD m_dwDefaultDisabledColor;
        DWORD m_dwDefaultFontColor;
        DWORD m_dwDefaultLinkFontColor;
        DWORD m_dwDefaultLinkHoverFontColor;
        DWORD m_dwDefaultSelectedBkColor;
        TFONTINFO_UI m_DefaultFontInfo;
        CStringPtrMapUI m_CustomFonts;
        CStringPtrMapUI m_ImageHash;
        CStringPtrMapUI m_AttrHash;
        CStringPtrMapUI m_MultiLanguageHash;
    };

    class CPaintManagerUI;
    class CControlUI;

    class DUILIB_API CRenderClip
    {
    public:
        ~CRenderClip();
        RECT rcItem;
        HDC hDC;
        HRGN hRgn;
        HRGN hOldRgn;

        static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);
        static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
        static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
        static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
    };

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class DUILIB_API CRenderEngine
    {
    public:
        static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
        static HBITMAP CreateARGB32Bitmap(HDC hDC, int cx, int cy, COLORREF** pBits);
        static void AdjustImage(bool bUseHSL, struct TIMAGEINFO_UI* imageInfo, short H, short S, short L);
        static struct TIMAGEINFO_UI* LoadImage(STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0);
        static void FreeImage(TIMAGEINFO_UI* bitmap, bool bDelete = true);
        static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
            const RECT& rcBmpPart, const RECT& rcScale9, bool alphaChannel, BYTE uFade = 255,
            bool hole = false, bool xtiled = false, bool ytiled = false);
        static bool DrawImage(HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint,
            struct TDRAWINFO_UI& drawInfo);
        static void DrawColor(HDC hDC, const RECT& rc, DWORD color);
        static void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);

        // 以下函数中的颜色参数alpha值无效
        static void DrawLine(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor, int nStyle = PS_SOLID);
        static void DrawRect(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor, int nStyle = PS_SOLID);
        static void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor, int nStyle = PS_SOLID);
        static void DrawText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, \
            DWORD dwTextColor, int iFont, UINT uStyle);
        static void DrawHtmlText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText,
            DWORD dwTextColor, RECT* pLinks, CStringUI* sLinks, int& nLinkRects, int iDefaultFont, UINT uStyle);
        static HBITMAP GenerateBitmap(CPaintManagerUI* pManager, RECT rc, CControlUI* pStopControl = NULL, DWORD dwFilterColor = 0);
        static HBITMAP GenerateBitmap(CPaintManagerUI* pManager, CControlUI* pControl, RECT rc, DWORD dwFilterColor = 0);
        static SIZE GetTextSize(HDC hDC, CPaintManagerUI* pManager, LPCTSTR pstrText, int iFont, UINT uStyle);
    };

} // namespace DUILIB

#endif // __UIRENDER_H__
