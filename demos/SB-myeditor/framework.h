#ifndef __MYFRAMEWORK_H_
#define __MYFRAMEWORK_H_


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "Core/UIWindow.h"
#include "Control/UIButton.h"
using namespace DUILIB;


class CMyFramework : public CWindowUI
{
    CButtonUI* m_pButton;
public:
    virtual LPCTSTR GetWindowClassName() const
    {
        return _T("CMyFramework");
    }

    virtual LRESULT OnCreated(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        m_pButton = new CButtonUI();
    }

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            case WM_CREATE: return OnCreated(uMsg, wParam, lParam);
        }
    }
};


#endif//__MYFRAMEWORK_H_
