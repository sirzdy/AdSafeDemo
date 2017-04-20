#pragma once
#include "resource.h"
#include "AdSafeFrameWnd.h"
#include "Calculator.h"
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif
#define WM_TRAY (WM_USER + 100)  
#define WM_TASKBAR_CREATED RegisterWindowMessage(TEXT("TaskbarCreated")) 
#define APP_NAME    TEXT("张丹阳")  
#define APP_TIP     TEXT("系统托盘") 
NOTIFYICONDATA nid;     //托盘属性  
HMENU hMenu;            //托盘菜单 
HWND hWnd;
void InitTray(HINSTANCE hInstance, HWND hWnd)
{
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uID = IDI_TRAY;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	nid.uCallbackMessage = WM_TRAY;
	nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAY));
	lstrcpy(nid.szTip, APP_NAME); //复制APP_NAME到szTip
	hMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, ID_SHOW, TEXT("显示主窗口"));
	AppendMenu(hMenu, MF_STRING, ID_EXIT, TEXT("退出"));
	Shell_NotifyIcon(NIM_ADD, &nid);
}
//演示托盘气泡提醒  
//void ShowTrayMsg()
//{
//	lstrcpy(nid.szInfoTitle, APP_NAME);
//	lstrcpy(nid.szInfo, TEXT("收到一条消息！"));
//	nid.uTimeout = 1000;
//	Shell_NotifyIcon(NIM_MODIFY, &nid);
//}
LRESULT CAdSafeFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_TRAY:
		switch (lParam)
		{
			case WM_RBUTTONDOWN:
			{
				Calculator CalculatorWnd;
				CalculatorWnd.Create(this->m_hWnd, _T("设置"), UI_WNDSTYLE_DIALOG, NULL);
				CalculatorWnd.CenterWindow();
				CalculatorWnd.ShowModal();
				//POINT pt; 
				//GetCursorPos(&pt);
				////解决在菜单外单击左键菜单不消失的问题  
				//SetForegroundWindow(hWnd);
				////使菜单某项变灰  
				////EnableMenuItem(hMenu, ID_SHOW, MF_GRAYED);      

				////显示并获取选中的菜单  
				//int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hWnd,NULL);
				//MessageBox(nullptr, _T("显示"), _T("--"), NULL);

				//if (cmd == ID_SHOW)
				//{
				//	ShowWindow(hWnd);
				//	MessageBox(nullptr, _T("3"), _T("--"), NULL);
				//}
				//if (cmd == ID_EXIT)
				//{
				//	MessageBox(nullptr, _T("4"), _T("--"), NULL);
				//	ExitProcess(0);
				//}
			}
			break;
		case WM_LBUTTONDOWN:
			ShowWindow(hWnd);
			break;
		case WM_LBUTTONDBLCLK:
			CSettingFrameWnd SettingFrame;
			SettingFrame.Create(this->m_hWnd, _T("设置"), UI_WNDSTYLE_DIALOG, NULL);
			SettingFrame.CenterWindow();
			SettingFrame.ShowModal();
			break;
		}
		break;
	case WM_DESTROY:
		//窗口销毁时删除托盘  
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	if (uMsg == WM_TASKBAR_CREATED)
	{
		//系统Explorer崩溃重启时，重新加载托盘  
		Shell_NotifyIcon(NIM_ADD, &nid);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	/*HWND handle = FindWindow(NULL, TEXT("AdSafeDemo.exe"));
	if (handle != NULL)
	{
		MessageBox(NULL, TEXT("Application is already running"), TEXT("净网大师"), MB_ICONERROR);
		return 0;
	}*/
	
	CWndShadow::Initialize(hInstance);
	CPaintManagerUI::SetInstance(hInstance);
	CAdSafeFrameWnd AdSafeFrame;
	hWnd = AdSafeFrame.Create(NULL, _T("净网大师"), UI_WNDSTYLE_FRAME, NULL);
	InitTray(hInstance, hWnd);
	AdSafeFrame.CenterWindow();
	AdSafeFrame.ShowModal();
	return 0;
}