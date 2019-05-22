#ifndef __UIDefine_H_
#define __UIDefine_H_

#include "Utils/Utils.h"

//////////////BEGIN消息映射宏定义////////////////////////////////////////////////////
///

namespace DUILIB
{

#define _USEIMM					1
#define MAX_FONT_ID				30000
#define LAYEREDUPDATE_TIMERID	0x2000

#define SCROLLBAR_LINESIZE      8





    /////////////////////////////////////////////////////////////////////////////////////
    //

    // Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_UPDATETEST    0x00000008
#define UIFIND_TOP_FIRST     0x00000010
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040


    enum SIG_UI
    {
        UISIG_end = 0, // [marks end of message map]
        UISIG_lwl,     // LRESULT (WPARAM, LPARAM)
        UISIG_vn,      // void (struct TNOTIFY_UI)
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    enum EVENTTYPE_UI
    {
        UIEVENT__FIRST = 1,
        UIEVENT__KEYBEGIN,
        UIEVENT_KEYDOWN,
        UIEVENT_KEYUP,
        UIEVENT_CHAR,
        UIEVENT_SYSKEY,
        UIEVENT__KEYEND,
        UIEVENT__MOUSEBEGIN,
        UIEVENT_MOUSEMOVE,
        UIEVENT_MOUSELEAVE,
        UIEVENT_MOUSEENTER,
        UIEVENT_MOUSEHOVER,
        UIEVENT_BUTTONDOWN,
        UIEVENT_BUTTONUP,
        UIEVENT_RBUTTONDOWN,
        UIEVENT_DBLCLICK,
        UIEVENT_CONTEXTMENU,
        UIEVENT_SCROLLWHEEL,
        UIEVENT__MOUSEEND,
        UIEVENT_KILLFOCUS,
        UIEVENT_SETFOCUS,
        UIEVENT_WINDOWSIZE,
        UIEVENT_SETCURSOR,
        UIEVENT_TIMER,
        UIEVENT_NOTIFY,
        UIEVENT_COMMAND,
        UIEVENT__LAST,
    };

    // Structure for notifications to the outside world
    class CControlUI;
    struct TNOTIFY_UI
    {
        CStringUI sType;
        CStringUI sVirtualWnd;
        CControlUI* pSender;
        DWORD dwTimestamp;
        POINT ptMouse;
        WPARAM wParam;
        LPARAM lParam;
    };

    class CNotifyPump;
    typedef void (CNotifyPump::* DUI_PMSG)(struct TNOTIFY_UI& msg);  //指针类型

    union DuiMessageMapFunctions
    {
        DUI_PMSG pfn;   // generic member function pointer
        LRESULT(CNotifyPump::* pfn_Notify_lwl)(WPARAM, LPARAM);
        void (CNotifyPump::* pfn_Notify_vn)(struct TNOTIFY_UI&);
    };

//定义所有消息类型
//////////////////////////////////////////////////////////////////////////

#define DUI_MSGTYPE_MENU                   (_T("menu"))
#define DUI_MSGTYPE_LINK                   (_T("link"))

#define DUI_MSGTYPE_TIMER                  (_T("timer"))
#define DUI_MSGTYPE_CLICK                  (_T("click"))

#define DUI_MSGTYPE_RETURN                 (_T("return"))
#define DUI_MSGTYPE_SCROLL                 (_T("scroll"))

#define DUI_MSGTYPE_DROPDOWN               (_T("dropdown"))
#define DUI_MSGTYPE_SETFOCUS               (_T("setfocus"))

#define DUI_MSGTYPE_KILLFOCUS              (_T("killfocus"))
#define DUI_MSGTYPE_ITEMCLICK 		   	   (_T("itemclick"))
#define DUI_MSGTYPE_TABSELECT              (_T("tabselect"))

#define DUI_MSGTYPE_ITEMSELECT 		   	   (_T("itemselect"))
#define DUI_MSGTYPE_ITEMEXPAND             (_T("itemexpand"))

#define DUI_MSGTYPE_WINDOWINIT             (_T("windowinit"))
#define DUI_MSGTYPE_BUTTONDOWN 		   	   (_T("buttondown"))
#define DUI_MSGTYPE_MOUSEENTER			   (_T("mouseenter"))
#define DUI_MSGTYPE_MOUSELEAVE			   (_T("mouseleave"))

#define DUI_MSGTYPE_TEXTCHANGED            (_T("textchanged"))
#define DUI_MSGTYPE_HEADERCLICK            (_T("headerclick"))
#define DUI_MSGTYPE_ITEMDBCLICK            (_T("itemdbclick"))
#define DUI_MSGTYPE_SHOWACTIVEX            (_T("showactivex"))

#define DUI_MSGTYPE_ITEMCOLLAPSE           (_T("itemcollapse"))
#define DUI_MSGTYPE_ITEMACTIVATE           (_T("itemactivate"))
#define DUI_MSGTYPE_VALUECHANGED           (_T("valuechanged"))

#define DUI_MSGTYPE_SELECTCHANGED 		   (_T("selectchanged"))


//////////////////////////////////////////////////////////////////////////



struct DUI_MSGMAP_ENTRY;
struct DUI_MSGMAP
{
#ifndef UILIB_STATIC
	const DUI_MSGMAP* (PASCAL* pfnGetBaseMap)();
#else
	const DUI_MSGMAP* pBaseMap;
#endif
	const DUI_MSGMAP_ENTRY* lpEntries;
};

//结构定义
struct DUI_MSGMAP_ENTRY //定义一个结构体，来存放消息信息
{
	CStringUI sMsgType;          // DUI消息类型
	CStringUI sCtrlName;         // 控件名称
	UINT       nSig;              // 标记函数指针类型
	DUI_PMSG   pfn;               // 指向函数的指针
};

//定义
#ifndef UILIB_STATIC
#define DUI_DECLARE_MESSAGE_MAP()                                         \
private:                                                                  \
	static const DUI_MSGMAP_ENTRY _messageEntries[];                      \
protected:                                                                \
	static const DUI_MSGMAP messageMap;                                   \
	static const DUI_MSGMAP* PASCAL _GetBaseMessageMap();                 \
	virtual const DUI_MSGMAP* GetMessageMap() const;                      \

#else
#define DUI_DECLARE_MESSAGE_MAP()                                         \
private:                                                                  \
	static const DUI_MSGMAP_ENTRY _messageEntries[];                      \
protected:                                                                \
	static  const DUI_MSGMAP messageMap;				                  \
	virtual const DUI_MSGMAP* GetMessageMap() const;                      \

#endif


//基类声明开始
#ifndef UILIB_STATIC
#define DUI_BASE_BEGIN_MESSAGE_MAP(theClass)                              \
	const DUI_MSGMAP* PASCAL theClass::_GetBaseMessageMap()               \
		{ return NULL; }                                                  \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{  &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] };\
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#else
#define DUI_BASE_BEGIN_MESSAGE_MAP(theClass)                              \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{  NULL, &theClass::_messageEntries[0] };                         \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#endif


//子类声明开始
#ifndef UILIB_STATIC
#define DUI_BEGIN_MESSAGE_MAP(theClass, baseClass)                        \
	const DUI_MSGMAP* PASCAL theClass::_GetBaseMessageMap()               \
		{ return &baseClass::messageMap; }                                \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{ &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#else
#define DUI_BEGIN_MESSAGE_MAP(theClass, baseClass)                        \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{ &baseClass::messageMap, &theClass::_messageEntries[0] };        \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#endif


//声明结束
#define DUI_END_MESSAGE_MAP()                                             \
	{ _T(""), _T(""), UISIG_end, (DUI_PMSG)0 }                           \
};                                                                        \


//定义消息类型--执行函数宏
#define DUI_ON_MSGTYPE(msgtype, memberFxn)                                \
	{ msgtype, _T(""), UISIG_vn, (DUI_PMSG)&memberFxn},                  \


//定义消息类型--控件名称--执行函数宏
#define DUI_ON_MSGTYPE_CTRNAME(msgtype,ctrname,memberFxn)                 \
	{ msgtype, ctrname, UISIG_vn, (DUI_PMSG)&memberFxn },                \


//定义click消息的控件名称--执行函数宏
#define DUI_ON_CLICK_CTRNAME(ctrname,memberFxn)                           \
	{ DUI_MSGTYPE_CLICK, ctrname, UISIG_vn, (DUI_PMSG)&memberFxn },      \


//定义selectchanged消息的控件名称--执行函数宏
#define DUI_ON_SELECTCHANGED_CTRNAME(ctrname,memberFxn)                   \
    { DUI_MSGTYPE_SELECTCHANGED,ctrname,UISIG_vn,(DUI_PMSG)&memberFxn }, \


//定义killfocus消息的控件名称--执行函数宏
#define DUI_ON_KILLFOCUS_CTRNAME(ctrname,memberFxn)                       \
	{ DUI_MSGTYPE_KILLFOCUS,ctrname,UISIG_vn,(DUI_PMSG)&memberFxn },     \


//定义menu消息的控件名称--执行函数宏
#define DUI_ON_MENU_CTRNAME(ctrname,memberFxn)                            \
	{ DUI_MSGTYPE_MENU,ctrname,UISIG_vn,(DUI_PMSG)&memberFxn },          \


//定义与控件名称无关的消息宏

  //定义timer消息--执行函数宏
#define DUI_ON_TIMER()                                                    \
	{ DUI_MSGTYPE_TIMER, _T(""), UISIG_vn,(DUI_PMSG)&OnTimer },          \


///
//////////////END消息映射宏定义////////////////////////////////////////////////////


//////////////BEGIN控件名称宏定义//////////////////////////////////////////////////
///

#define  DUI_CTR_EDIT                            (_T("Edit"))
#define  DUI_CTR_LIST                            (_T("List"))
#define  DUI_CTR_TEXT                            (_T("Text"))
#define  DUI_CTR_TREE                            (_T("Tree"))
#define  DUI_CTR_HBOX                            (_T("HBox"))
#define  DUI_CTR_VBOX                            (_T("VBox"))

#define  DUI_CTR_ILIST                           (_T("IList"))
#define  DUI_CTR_COMBO                           (_T("Combo"))
#define  DUI_CTR_LABEL                           (_T("Label"))
#define  DUI_CTR_FLASH							 (_T("Flash"))

#define  DUI_CTR_BUTTON                          (_T("Button"))
#define  DUI_CTR_OPTION                          (_T("Option"))
#define  DUI_CTR_SLIDER                          (_T("Slider"))

#define  DUI_CTR_CONTROL                         (_T("Control"))
#define  DUI_CTR_ACTIVEX                         (_T("ActiveX"))
#define  DUI_CTR_GIFANIM                         (_T("GifAnim"))

#define  DUI_CTR_PROGRESS                        (_T("Progress"))
#define  DUI_CTR_RICHEDIT                        (_T("RichEdit"))
#define  DUI_CTR_CHECKBOX                        (_T("CheckBox"))
#define  DUI_CTR_COMBOBOX                        (_T("ComboBox"))
#define  DUI_CTR_DATETIME                        (_T("DateTime"))
#define  DUI_CTR_TREEVIEW                        (_T("TreeView"))
#define  DUI_CTR_TREENODE                        (_T("TreeNode"))

#define  DUI_CTR_ILISTITEM                       (_T("IListItem"))
#define  DUI_CTR_CONTAINER                       (_T("Container"))
#define  DUI_CTR_TABLAYOUT                       (_T("TabLayout"))
#define  DUI_CTR_SCROLLBAR                       (_T("ScrollBar"))

#define  DUI_CTR_ICONTAINER                      (_T("IContainer"))
#define  DUI_CTR_ILISTOWNER                      (_T("IListOwner"))
#define  DUI_CTR_LISTHEADER                      (_T("ListHeader"))
#define  DUI_CTR_TILELAYOUT                      (_T("TileLayout"))
#define  DUI_CTR_WEBBROWSER                      (_T("WebBrowser"))

#define  DUI_CTR_CHILDLAYOUT                     (_T("ChildLayout"))
#define  DUI_CTR_LISTELEMENT                     (_T("ListElement"))
#define  DUI_CTR_VIRTUALLIST                     (_T("VirtualList"))

#define  DUI_CTR_VERTICALLAYOUT                  (_T("VerticalLayout"))
#define  DUI_CTR_LISTHEADERITEM                  (_T("ListHeaderItem"))

#define  DUI_CTR_LISTHBOXELEMENT                 (_T("ListHBoxElement"))
#define  DUI_CTR_LISTTEXTELEMENT                 (_T("ListTextElement"))

#define  DUI_CTR_HORIZONTALLAYOUT                (_T("HorizontalLayout"))
#define  DUI_CTR_LISTLABELELEMENT                (_T("ListLabelElement"))

#define  DUI_CTR_LISTCONTAINERELEMENT            (_T("ListContainerElement"))


///
//////////////END控件名称宏定义//////////////////////////////////////////////////


};// namespace DUILIB

#endif//__UIDefine_H_