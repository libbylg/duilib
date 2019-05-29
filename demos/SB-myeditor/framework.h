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
#include "Core/UIManager.h"
#include "Control/UIDialogBuilder.h"
#include "Utils/Utils.h"
using namespace DUILIB;


class CMyFramework : public CWindowUI, public INotifyUI
{
public:
    CManagerUI m_pm;
    CButtonUI* m_pButton;

public:
    virtual LPCTSTR GetWindowClassName() const
    {
        return _T("CMyFramework");
    }

    virtual LRESULT OnCreated(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        m_pm.Init(m_hWnd);
        CDialogBuilderUI builder;
        CControlUI* pRoot = builder.Create(STRINGorID(_T("F:\\dev\\github.com\\libbylg\\duilib_v2\\demos\\SB-myeditor\\myeditor.xml")));
        m_pm.AttachDialog(pRoot);
        m_pm.AddNotifier(this);
        return 0;
    }

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            case WM_CREATE: return OnCreated(uMsg, wParam, lParam);
            case WM_DESTROY: ::PostQuitMessage(0);
        }

        LRESULT lRes = 0;
        if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) {
            return lRes;
        }

        return CWindowUI::HandleMessage(uMsg, wParam, lParam);
    }

    virtual void Notify(TNOTIFY_UI& msg)
    {
        if (msg.sType == _T("click")) {
            if (msg.pSender->GetName() == _T("changeskinbtn")) {
                Close();
            }
        }
    }
};


//if (uMsg == WM_CREATE) {
//    m_pm.Init(m_hWnd);
//    CControlUI* pButton = new CButtonUI;
//    pButton->SetName(_T("closebtn"));
//    pButton->SetBkColor(0xFFFF0000);
//    m_pm.AttachDialog(pButton);
//    m_pm.AddNotifier(this);
//    return 0;
//} else if (uMsg == WM_DESTROY) {
//    ::PostQuitMessage(0);
//}
//LRESULT lRes = 0;
//if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
//return CWindowWnd::HandleMessage(uMsg, wParam, lParam);

#endif//__MYFRAMEWORK_H_
