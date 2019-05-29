#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "Core/UIControl.h"

#define _USE_GDIPLUS 1

#ifdef _USE_GDIPLUS
#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )
using namespace Gdiplus;
class DUILIB_API  Gdiplus::RectF;
struct DUILIB_API Gdiplus::GdiplusStartupInput;
#endif


namespace DUILIB
{
    class DUILIB_API CLabelUI : public CControlUI
    {
    public:
        CLabelUI();
        ~CLabelUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        void SetFixedWidth(int cx);
        void SetFixedHeight(int cy);
        void SetText(LPCTSTR pstrText);

        void SetTextStyle(UINT uStyle);
        UINT GetTextStyle() const;
        BOOL IsMultiLine();
        void SetMultiLine(BOOL bMultiLine = TRUE);
        void SetTextColor(DWORD dwTextColor);
        DWORD GetTextColor() const;
        void SetDisabledTextColor(DWORD dwTextColor);
        DWORD GetDisabledTextColor() const;
        void SetFont(int index);
        int GetFont() const;
        RECT GetTextPadding() const;
        void SetTextPadding(RECT rc);
        BOOL IsShowHtml();
        void SetShowHtml(BOOL bShowHtml = TRUE);

        SIZE EstimateSize(SIZE szAvailable);
        void DoEvent(TEVENT_UI& event);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        void PaintText(HDC hDC);

#ifdef _USE_GDIPLUS
        void		SetEnabledEffect(BOOL _EnabledEffect);
        BOOL		GetEnabledEffect();
        void		SetEnabledLuminous(BOOL bEnableLuminous);
        BOOL		GetEnabledLuminous();
        void		SetLuminousFuzzy(float fFuzzy);
        float		GetLuminousFuzzy();
        void		SetGradientLength(int _GradientLength);
        int			GetGradientLength();
        void		SetShadowOffset(int _offset, int _angle);
        RectF		GetShadowOffset();
        void		SetTextColor1(DWORD _TextColor1);
        DWORD		GetTextColor1();
        void		SetTextShadowColorA(DWORD _TextShadowColorA);
        DWORD		GetTextShadowColorA();
        void		SetTextShadowColorB(DWORD _TextShadowColorB);
        DWORD		GetTextShadowColorB();
        void		SetStrokeColor(DWORD _StrokeColor);
        DWORD		GetStrokeColor();
        void		SetGradientAngle(int _SetGradientAngle);
        int			GetGradientAngle();
        void		SetEnabledStroke(BOOL _EnabledStroke);
        BOOL		GetEnabledStroke();
        void		SetEnabledShadow(BOOL _EnabledShadowe);
        BOOL		GetEnabledShadow();
#endif

    protected:
        LPWSTR  m_pWideText;
        DWORD	m_dwTextColor;
        DWORD	m_dwDisabledTextColor;
        int		m_iFont;
        UINT	m_uTextStyle;
        RECT	m_rcTextPadding;
        BOOL	m_bShowHtml;
        SIZE    m_szAvailableLast;
        SIZE    m_cxyFixedLast;
        BOOL    m_bNeedEstimateSize;

        float					m_fLuminousFuzzy;
        int						m_GradientLength;
        int						m_GradientAngle;
        BOOL					m_EnableEffect;
        BOOL					m_bEnableLuminous;
        BOOL					m_EnabledStroke;
        BOOL					m_EnabledShadow;
        DWORD					m_dwTextColor1;
        DWORD					m_dwTextShadowColorA;
        DWORD					m_dwTextShadowColorB;
        DWORD					m_dwStrokeColor;
        RectF					m_ShadowOffset;
        ULONG_PTR				m_gdiplusToken;
#ifdef _USE_GDIPLUS
        GdiplusStartupInput		m_gdiplusStartupInput;
#endif
    };
}

#endif // __UILABEL_H__