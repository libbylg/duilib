#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#include "Core/UIMarkup.h"

namespace DUILIB
{

    class CMarkupNodeUI;
    class CMarkupUI;
    class CControlUI;
    class CManagerUI;
    class STRINGorID;


    class IDialogBuilderCallback
    {
    public:
        virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
    };



    class DUILIB_API CDialogBuilder
    {
    public:
        CDialogBuilder();
        CControlUI* Create(STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL, CManagerUI* pManager = NULL, CControlUI* pParent = NULL);
        CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, CManagerUI* pManager = NULL, CControlUI* pParent = NULL);

        CMarkupUI* GetMarkup();

        void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
        void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
    private:
        CControlUI* _Parse(CMarkupNodeUI* parent, CControlUI* pParent = NULL, CManagerUI* pManager = NULL);

        CMarkupUI m_xml;
        IDialogBuilderCallback* m_pCallback;
        LPCTSTR m_pstrtype;
    };

} // namespace DUILIB

#endif // __UIDLGBUILDER_H__
