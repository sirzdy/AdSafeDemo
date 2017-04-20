#pragma once
#include <UIlib.h>
using namespace DuiLib;
class CDuiMenu : public WindowImplBase
{
protected:
	virtual ~CDuiMenu(){};        // 私有化析构函数，这样此对象只能通过new来生成，而不能直接定义变量。就保证了delete this不会出错
	CDuiString  m_strXMLPath;

public:
	explicit CDuiMenu(LPCTSTR pszXMLPath) : m_strXMLPath(pszXMLPath){}
	virtual LPCTSTR    GetWindowClassName()const{ return _T("CDuiMenu "); }
	virtual CDuiString GetSkinFolder()          { return _T(""); }
	virtual CDuiString GetSkinFile()            { return m_strXMLPath; }
	virtual void       OnFinalMessage(HWND hWnd){ delete this; }

	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		Close();
		bHandled = FALSE;
		return 0;
	}

	void Init(HWND hWndParent, POINT ptPos)
	{
		/*RECT rc;
		GetWindowRect(this->m_hWnd, &rc);
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
		if (ptPos.x + 105>width)
		{
			ptPos.x = width - 105;
		}*/
		Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
		::ClientToScreen(hWndParent, &ptPos);
		::SetWindowPos(*this, NULL, ptPos.x, ptPos.y,0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	virtual void    Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("itemclick"))
		{
			CDuiString strName = msg.pSender->GetName();
			if (strName == _T("lcClose"))
			{
				PostQuitMessage(0);
			}
		}
		__super::Notify(msg);
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL    bHandled = TRUE;

		switch (uMsg)
		{
		case WM_KILLFOCUS:
			lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
			break;
		default:
			bHandled = FALSE;
		}

		if (bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}
};