#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#include "UIMarkup.h"

namespace DUILIB
{

    class CMarkupNode;
    class CMarkup;
    class CControlUI;
    class CPaintManagerUI;
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
        CControlUI* Create(STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
        CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);

        CMarkup* GetMarkup();

        void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
        void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
    private:
        CControlUI* _Parse(CMarkupNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);

        CMarkup m_xml;
        IDialogBuilderCallback* m_pCallback;
        LPCTSTR m_pstrtype;
    };

} // namespace DUILIB

#endif // __UIDLGBUILDER_H__
