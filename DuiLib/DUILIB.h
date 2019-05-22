#ifndef _DUILIB_
#define _DUILIB_


#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <olectl.h>
#include <richedit.h>
#include <zmouse.h>


#include <stddef.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _DEBUG
#include <shlwapi.h>
#endif


#if defined(__GNUC__)
// 怎么都没找到min，max的头文件-_-
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#endif

#if defined(_MSC_VER)
#pragma warning (disable : 4511) // copy operator could not be generated
#pragma warning (disable : 4512) // assignment operator could not be generated
#pragma warning (disable : 4702) // unreachable code (bugs in Microsoft's STL)
#pragma warning (disable : 4786) // identifier was truncated
#pragma warning (disable : 4996) // function or variable may be unsafe (deprecated)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // eliminate deprecation warnings for VS2005
#endif
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#endif

#if defined(__BORLANDC__)
#pragma option -w-8027		   // function not expanded inline
#endif



#ifndef __FILET__
#define __DUILIB_STR2WSTR(str)  L##str
#define _DUILIB_STR2WSTR(str)   __DUILIB_STR2WSTR(str)
#ifdef _UNICODE
#define __FILET__	    _DUILIB_STR2WSTR(__FILE__)
#define __FUNCTIONT__	_DUILIB_STR2WSTR(__FUNCTION__)
#else
#define __FILET__	    __FILE__
#define __FUNCTIONT__	__FUNCTION__
#endif
#endif



// Required for VS 2008 (fails on XP and Win2000 without this fix)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif


#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif


#define lengthof(x)     (sizeof(x)/sizeof(*x))
#define MAX max
#define MIN min
#define CLAMP(x,a,b)    (MIN(b,MAX(a,x)))


#ifdef UILIB_STATIC
#	define DUILIB_API 
#else
#	if defined(UILIB_EXPORTS)
#		if	defined(_MSC_VER)
#			define DUILIB_API __declspec(dllexport)
#		else
#			define DUILIB_API 
#		endif
#	else
#		if defined(_MSC_VER)
#			define DUILIB_API __declspec(dllimport)
#		else
#			define DUILIB_API 
#		endif
#	endif
#endif


#define UILIB_COMDAT __declspec(selectany)







//#include "Utils/Utils.h"
//#include "Utils/UIDelegate.h"
//#include "Core/UIDefine.h"
//#include "Core/UIManager.h"
//#include "Core/UIBase.h"
//#include "Core/UIControl.h"
//#include "Core/UIContainer.h"
//#include "Core/UIMarkup.h"
//#include "Core/UIDlgBuilder.h"
//#include "Core/UIRender.h"
//#include "Utils/WinImplBase.h"
//#include "Utils/WndShadow.h"

//#include "Layout/UIVerticalLayout.h"
//#include "Layout/UIHorizontalLayout.h"
//#include "Layout/UITileLayout.h"
//#include "Layout/UITabLayout.h"
//#include "Layout/UIChildLayout.h"
//
//#include "Control/UIList.h"
//#include "Control/UICombo.h"
//#include "Core/UIScrollBar.h"
//#include "Control/UITreeView.h"
//
//#include "Control/UILabel.h"
//#include "Control/UIText.h"
//#include "Control/UIEdit.h"
//
//#include "Control/UIButton.h"
//#include "Control/UIOption.h"
//#include "Control/UICheckBox.h"
//
//#include "Control/UIProgress.h"
//#include "Control/UISlider.h"
//
//#include "Control/UIRichEdit.h"
//#include "Control/UIDateTime.h"
//
//#include "Control/UIActiveX.h"
//#include "Control/UIWebBrowser.h"
//#include "Control/UIGifAnim.h"

//#include "Control/UIFlash.h"
namespace DUILIB
{
};

#endif//_DUILIB_

