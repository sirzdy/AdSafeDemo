#pragma once
#include <UIlib.h>
using namespace DuiLib;
#define inisrc TEXT(".//config.ini")
class CSettingFrameWnd :public WindowImplBase
{
	CWndShadow m_WndShadow;
public:
	virtual LPCTSTR GetWindowClassName() const	{ return _T("SettingFrame"); }
	virtual CDuiString GetSkinFile()			{ return _T("setting.xml"); }
	virtual CDuiString GetSkinFolder()			{ return _T(""); }
	virtual void InitWindow()
	{
		m_WndShadow.Create(m_hWnd);
		m_WndShadow.SetSize(3);
		m_WndShadow.SetColor(0xFF123456);
		m_WndShadow.SetDarkness(200);
		m_WndShadow.SetPosition(0, 0);
		int iKey = GetPrivateProfileInt(TEXT("Key"), TEXT("acctype"), 0, inisrc);
		SetKey(iKey);
	}
	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			/*if (msg.pSender->GetName() == _T("btnClose"))
			{
				PostQuitMessage(0);
			}*/
			if (msg.pSender->GetName() == _T("btnKeyY"))
			{
				SetKey(1);
				return;
			}
			if (msg.pSender->GetName() == _T("btnKeyN"))
			{
				SetKey(0);
				return;
			}
		}
		__super::Notify(msg);
	}
	/**
	* @brief 用于设置账户类型
	* @param iKey账户类型：0无key，1有key
	*/
	void SetKey(int iKey)
	{
		CButtonUI* pBtnKeyY = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnKeyY")));
		CButtonUI* pBtnKeyN = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnKeyN")));
		if (!iKey)//无key：无key按钮高亮，不可用；key按钮灰色，可用
		{
			WritePrivateProfileString(TEXT("Key"), TEXT("acctype"), _T("0"), inisrc);
			pBtnKeyY->SetNormalImage(L"SysBtn//key_yo.png");
			pBtnKeyY->SetTextColor(0xffabaead);
			pBtnKeyY->SetEnabled(true);
			pBtnKeyN->SetNormalImage(L"SysBtn//key_np.png");
			pBtnKeyN->SetTextColor(0xff267ffc);
			pBtnKeyN->SetEnabled(false);
		}
		else
		{
			WritePrivateProfileString(TEXT("Key"), TEXT("acctype"), _T("1"), inisrc);
			pBtnKeyY->SetNormalImage(L"SysBtn//key_yp.png");
			pBtnKeyY->SetTextColor(0xff267ffc);
			pBtnKeyY->SetEnabled(false);
			pBtnKeyN->SetNormalImage(L"SysBtn//key_no.png");
			pBtnKeyN->SetTextColor(0xffabaead);
			pBtnKeyN->SetEnabled(true);	
		}
		return;
	}
};