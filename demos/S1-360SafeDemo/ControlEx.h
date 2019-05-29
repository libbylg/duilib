#ifndef __ComputerExamineUI_H_
#define __ComputerExamineUI_H_

#include "Core/UIContainer.h"
#include "Control/UIDialogBuilder.h"

using namespace DUILIB;

class ComputerExamineUI : public CContainerUI
{
public:
	ComputerExamineUI()
	{
		CDialogBuilderUI builder;
		CContainerUI* pComputerExamine = static_cast<CContainerUI*>(builder.Create(_T("ComputerExamine.xml"), (UINT)0));
		if( pComputerExamine ) {
			this->Add(pComputerExamine);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};



class CDialogBuilderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass) 
	{
		if( _tcscmp(pstrClass, _T("ComputerExamine")) == 0 ) return new ComputerExamineUI;
		return NULL;
	}
};


#endif//__ComputerExamineUI_H_

