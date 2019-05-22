#ifndef __CWndShadow_H_
#define __CWndShadow_H_

#include "Utils/Utils.h"

namespace DUILIB
{
    struct TIMAGEINFO_UI;

    class DUILIB_API CWndShadow
    {
    public:
        CWndShadow(void);
    public:
        virtual ~CWndShadow(void);

    protected:

        // Instance handle, used to register window class and create window 
        static HINSTANCE s_hInstance;

        // Parent HWND and CWndShadow object pares, in order to find CWndShadow in ParentProc()
        static DUILIB::CValArrayUI s_ShadowArray;

        // 
        typedef BOOL(WINAPI* pfnUpdateLayeredWindow)(HWND hWnd, HDC hdcDst, POINT* pptDst,
            SIZE* psize, HDC hdcSrc, POINT* pptSrc, COLORREF crKey,
            BLENDFUNCTION* pblend, DWORD dwFlags);
        static pfnUpdateLayeredWindow s_UpdateLayeredWindow;

        HWND m_hWnd;

        WNDPROC m_OriParentProc;	// Original WndProc of parent window

        enum ShadowStatus
        {
            SS_ENABLED = 1,	// Shadow is enabled, if not, the following one is always false
            SS_VISABLE = 1 << 1,	// Shadow window is visible
            SS_PARENTVISIBLE = 1 << 2	// Parent window is visible, if not, the above one is always false
        };
        BYTE m_Status;

        unsigned char m_nDarkness;	// Darkness, transparency of blurred area
        unsigned char m_nSharpness;	// Sharpness, width of blurred border of shadow window
        signed char m_nSize;	// Shadow window size, relative to parent window size

        // The X and Y offsets of shadow window,
        // relative to the parent window, at center of both windows (not top-left corner), signed
        signed char m_nxOffset;
        signed char m_nyOffset;

        // Restore last parent window size, used to determine the update strategy when parent window is resized
        LPARAM m_WndSize;

        // Set this to true if the shadow should not be update until next WM_PAINT is received
        bool m_bUpdate;

        COLORREF m_Color;	// Color of shadow

        struct TIMAGEINFO_UI* m_pImageInfo;
        RECT m_rcCorner;
        RECT m_rcHoleOffset;

    public:
        static bool Initialize(HINSTANCE hInstance);

        HWND GetHWND() const;
        operator HWND() const;
        void Create(HWND hParentWnd);

        // 使用图片只需要调用这个方法(rcHoleOffset作用是修复圆角显示空白的bug)
        bool SetImage(LPCTSTR image, RECT rcCorner, RECT rcHoleOffset);

        // 使用颜色可以使用如下几个方法
        bool SetSize(int NewSize = 0);
        bool SetSharpness(unsigned int NewSharpness = 5);
        bool SetDarkness(unsigned int NewDarkness = 200);
        bool SetPosition(int NewXOffset = 5, int NewYOffset = 5);
        bool SetColor(COLORREF NewColor = 0);

    protected:
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        static CWndShadow* FindShadowWindow(HWND hWnd);
        static int GetShadowWindowIndex(HWND hWnd);

        // Redraw, resize and move the shadow
        // called when window resized or shadow properties changed, but not only moved without resizing
        void Update(HWND hParent);

        // Fill in the shadow window alpha blend bitmap with shadow image pixels
        void MakeShadow(UINT32* pShadBits, HWND hParent, RECT* rcParent);


        // Helper to calculate the alpha-premultiled value for a pixel
        inline DWORD PreMultiply(COLORREF cl, unsigned char nAlpha)
        {
            // It's strange that the byte order of RGB in 32b BMP is reverse to in COLORREF
            return (GetRValue(cl) * (DWORD)nAlpha / 255) << 16 |
                (GetGValue(cl) * (DWORD)nAlpha / 255) << 8 |
                (GetBValue(cl) * (DWORD)nAlpha / 255);
        }
    };

}

#endif//__CWndShadow_H_


