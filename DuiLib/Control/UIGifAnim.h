#ifndef GifAnimUI_h__
#define GifAnimUI_h__

#include "Core/UIControl.h"

namespace DUILIB
{
	class CControl;

#define EVENT_TIEM_ID	100

	class DUILIB_API CGifAnimUI : public CControlUI
	{
	public:
		CGifAnimUI(void);
		~CGifAnimUI(void);

		LPCTSTR	GetClass() const;
		LPVOID	GetInterface(LPCTSTR pstrName);
		void	DoInit() override;
		BOOL	DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		void	DoEvent(TEVENT_UI& event);
		void	SetVisible(BOOL bVisible = TRUE );
		void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void	SetBkImage(LPCTSTR pStrImage);
		LPCTSTR GetBkImage();

		void	SetAutoPlay(BOOL bIsAuto = TRUE );
		BOOL	IsAutoPlay() const;
		void	SetAutoSize(BOOL bIsAuto = TRUE );
		BOOL	IsAutoSize() const;
		void	PlayGif();
		void	PauseGif();
		void	StopGif();

	private:
		void	InitGifImage();
		void	DeleteGif();
		void    OnTimer( UINT_PTR idEvent );
		void	DrawFrame( HDC hDC );		// 绘制GIF每帧
		Gdiplus::Image*	LoadGifFromFile(LPCTSTR pstrGifPath);
		Gdiplus::Image* LoadGifFromMemory( LPVOID pBuf,size_t dwSize );
	private:
		Gdiplus::Image	*m_pGifImage;
		UINT			m_nFrameCount;				// gif图片总帧数
		UINT			m_nFramePosition;			// 当前放到第几帧
		Gdiplus::PropertyItem*	m_pPropertyItem;	// 帧与帧之间间隔时间

		CStringUI		m_sBkImage;
		BOOL			m_bIsAutoPlay;				// 是否自动播放gif
		BOOL			m_bIsAutoSize;				// 是否自动根据图片设置大小
		BOOL			m_bIsPlaying;

	};
}

#endif // GifAnimUI_h__
