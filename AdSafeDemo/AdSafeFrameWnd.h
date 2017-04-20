#pragma once
#include <UIlib.h>
#include "DuiMenu.h"
#include "Setting.h"
HANDLE hMutex;
CPaintManagerUI paintManager;
using namespace DuiLib;
int checkingState = 0;//0��ɣ�1����С�
CRITICAL_SECTION g_cs;

//DWORD WINAPI funContent(LPVOID lpParameter)
//{
//	
//	return 0;
//}
DWORD WINAPI funContent(LPVOID lpParameter){
	EnterCriticalSection(&g_cs);
	
	while (true)
	{
		if (checkingState)
		{
			
		}
		else
		{
			
			break;
		}
	}
	LeaveCriticalSection(&g_cs);
	return 0;
}

DWORD WINAPI fun2to16(LPVOID lpParameter)
{
	EnterCriticalSection(&g_cs);
	checkingState = 1;
	CContainerUI* pConCheckState = static_cast<CContainerUI*>(paintManager.FindControl(_T("conCheckState")));
	CGifAnimUI* pGifChecking = static_cast<CGifAnimUI*>(paintManager.FindControl(_T("gifChecking")));
	CTextUI* pTextState = static_cast<CTextUI*>(paintManager.FindControl(_T("textState")));
	CButtonUI* pBtnOneKeyCheck = static_cast<CButtonUI*>(paintManager.FindControl(_T("btnOneKeyCheck")));
	CButtonUI* pBtnOneKeyRepair = static_cast<CButtonUI*>(paintManager.FindControl(_T("btnOneKeyRepair")));
	CButtonUI* pBtnReCheck = static_cast<CButtonUI*>(paintManager.FindControl(_T("btnReCheck")));
	CProgressUI* pProgressOneKeyRepair = static_cast<CProgressUI*>(paintManager.FindControl(_T("progressOneKeyRepair")));
	pConCheckState->SetVisible(false);
	pGifChecking->SetVisible(true);
	pTextState->SetText(_T("���ڼ���С�"));

	FILE *fp = fopen("D:\\a.exe", "rb");
	FILE *f = fopen("D:\\b.txt", "w");
	unsigned char buf[16] = { 0 };
	int rc;//fread����ֵ
	int k = 0;
	fseek(fp, 0, SEEK_END); //��λ���ļ�ĩ 
	int nFileLen = ftell(fp); //�ļ�����
	rewind(fp);
	while ((rc = fread(buf, sizeof(unsigned char), 16, fp)) != 0)
	{
		for (int i = 0; i < rc; i++)
		{
			int num = buf[i];
			/**�淶��д*/
			if (num < 16)
			{
				fprintf(f, "0%x ", num);
			}
			else
			{
				fprintf(f, "%x ", num);
			}
			
		}
		fprintf(f, "\n");
		int ppp = (k * 16 + rc) * 100 / nFileLen;
		pProgressOneKeyRepair->SetValue(ppp);
		k++;
	}
	fclose(fp);
	fclose(f);
	
	pTextState->SetText(_T("�����ɣ����޸���"));
	pBtnOneKeyCheck->SetVisible(false);
	pBtnOneKeyRepair->SetVisible(true);
	pBtnReCheck->SetVisible(true);
	checkingState = 0;
	pConCheckState->SetBkImage(_T("mainpage//check_e.png"));
	pGifChecking->SetVisible(false);
	pConCheckState->SetVisible(true);
	LeaveCriticalSection(&g_cs);
	return 0;
	
}
DWORD WINAPI fun16to2(LPVOID lpParameter)
{
	
	WaitForSingleObject(hMutex,INFINITE);
	FILE *fp = fopen("D:\\b.txt", "r");
	FILE *f = fopen("D:\\c.exe", "wb");
	int k = 0;
	fseek(fp, 0, SEEK_END); //��λ���ļ�ĩ 
	int nFileLen = ftell(fp); //�ļ�����
	rewind(fp);
	int n;
	while (fscanf(fp, "%x", &n) != EOF)
	{
		fwrite(&n, 1, 1, f);
		//progress->SetValue((++k) * 50 / nFileLen+50);
	}
	fclose(fp);
	fclose(f);
	ReleaseMutex(hMutex);
	return 0;
}
class CAdSafeFrameWnd :public WindowImplBase
{
	NOTIFYICONDATA m_notify;     //��������  
	HMENU hMenu;            //���̲˵� 
public:
	CWndShadow m_WndShadow;
	virtual LPCTSTR GetWindowClassName() const	{ return _T("AdSafeMainFrame"); }
	virtual CDuiString GetSkinFile()			{ return _T("duilib.xml"); }
	virtual CDuiString GetSkinFolder()			{ return _T(""); }
	virtual void InitWindow()
	{
		m_WndShadow.Create(m_hWnd);
		m_WndShadow.SetSize(3);
		m_WndShadow.SetDarkness(200);
		//m_WndShadow.SetColor(0x0AFF00);
		m_WndShadow.SetPosition(0, 0);

		int iControlMode = GetPrivateProfileInt(TEXT("ControlMode"), TEXT("status"), 1, inisrc);
		int iControlMessage = GetPrivateProfileInt(TEXT("ControlMessage"), TEXT("status"), 1, inisrc);
		int iCloseStatus = GetPrivateProfileInt(TEXT("CloseStatus"), TEXT("status"), 1, inisrc);
		int iAutoRun = GetPrivateProfileInt(TEXT("AutoRun"), TEXT("status"), 1, inisrc);
		int iUpdateFrequency = GetPrivateProfileInt(TEXT("Update"), TEXT("frequency"), 1, inisrc);
		SetCloseStatus(iCloseStatus);
		SetAutoRun(iAutoRun);
		SetUpdateFrequency(iUpdateFrequency);
		SetControlModeMessage(iControlMode, iControlMessage);
		return;
	}
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg)
	{
		//if (msg.sType == _T("windowinit")) { return; }
		if (msg.sType == _T("selectchanged"))
		{
			CDuiString strName = msg.pSender->GetName();
			CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("AdSafeContent")));
			if (strName == _T("AdSafe1"))
			{
				pControl->SelectItem(0);
			}
			if (strName == _T("AdSafe2"))
			{
				pControl->SelectItem(1);
			}
			if (strName == _T("AdSafe3"))
			{
				pControl->SelectItem(2);
			}
			if (strName == _T("AdSafe4"))
			{
				pControl->SelectItem(3);
			}
			if (strName == _T("AdSafe5"))
			{
				pControl->SelectItem(4);
			}

		}
		if (msg.sType == _T("itemselect"))
		{
			CDuiString strName = msg.pSender->GetName();
			if (strName == _T("comboUpdateFrequency"))
			{
				CComboUI* pComboUpdateFrequency = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("comboUpdateFrequency")));
				pComboUpdateFrequency->SetInternVisible(true);
				int iComboUpdateFrequency = pComboUpdateFrequency->GetCurSel();
				if (iComboUpdateFrequency == 0)
				{
					WritePrivateProfileString(TEXT("Update"), TEXT("frequency"), _T("0"), inisrc);
				}
				if (iComboUpdateFrequency == 1)
				{
					WritePrivateProfileString(TEXT("Update"), TEXT("frequency"), _T("1"), inisrc);
				}
				if (iComboUpdateFrequency == 2)
				{
					WritePrivateProfileString(TEXT("Update"), TEXT("frequency"), _T("2"), inisrc);
				}
			}
		}
		if (msg.sType == _T("click"))
		{
			CDuiString strName = msg.pSender->GetName();
			if (strName == _T("closebtn"))
			{
				int iCloseStatus = GetPrivateProfileInt(TEXT("CloseStatus"), TEXT("status"),0, inisrc);
				if (iCloseStatus)
				{
					ShowWindow(SW_HIDE);
					return;
				}
				if (!iCloseStatus)
				{
					PostQuitMessage(0);
					return;
				}
			}
			if (strName == _T("reportAd"))
			{				
				MessageBox(NULL, _T("�ٱ����"), _T("����˰�ť"), NULL);
				return;
			}

			if (strName == _T("btnMes"))
			{
				CSettingFrameWnd SettingFrame;
				SettingFrame.Create(this->m_hWnd, _T("����"), UI_WNDSTYLE_DIALOG, NULL);
				SettingFrame.CenterWindow();
				SettingFrame.ShowModal();
				return;
			}
			if (strName == _T("btnMenu"))
			{
				RECT rc;
				GetWindowRect(this->m_hWnd, &rc);
				int width;
				int screenWidth = GetSystemMetrics(SM_CXSCREEN);
				int screenHeight = GetSystemMetrics(SM_CYSCREEN);
				if (rc.right>screenWidth)
				{

				}
				else
					width = rc.right - rc.left;
				POINT pt = { width - 105, 30 };
				CDuiMenu *pMenu = new CDuiMenu(_T("menu.xml"));
				pMenu->Init(*this, pt);
				pMenu->ShowWindow(TRUE);
				return;
			}
			if (strName == _T("btnMyPage"))
			{
				ShellExecute(NULL, L"open", L"http://zhangdanyang.com", NULL, NULL, SW_SHOW);
				return;
			}
			if (strName == _T("btnControlMode"))
			{
				int iControlMode = GetPrivateProfileInt(TEXT("ControlMode"), TEXT("status"), 1, inisrc);
				int iControlMessage = GetPrivateProfileInt(TEXT("ControlMessage"), TEXT("status"), 1, inisrc);
				SetControlModeMessage(!iControlMode, iControlMessage);
				return;
			}
			if (strName == _T("btnControlMessage"))
			{
				int iControlMode = GetPrivateProfileInt(TEXT("ControlMode"), TEXT("status"), 1, inisrc);
				int iControlMessage = GetPrivateProfileInt(TEXT("ControlMessage"), TEXT("status"), 1, inisrc);
				SetControlModeMessage(iControlMode, !iControlMessage);
				return;
			}
			if (strName == _T("btnOneKeyCheck") || msg.pSender->GetName() == _T("btnReCheck"))
			{
				paintManager = m_PaintManager;
				//hMutex = CreateMutex(NULL, true, _T("handleFile"));
				//ReleaseMutex(hMutex);
				//InitializeCriticalSection(&g_cs);
				//HANDLE handle2to16 = CreateThread(NULL, 0, fun2to16, &paintManager, 0, NULL);
				
				//HANDLE handleContent = CreateThread(NULL, 0, funContent, &paintManager, 0, NULL);
				//HANDLE handle16to2 = CreateThread(NULL, 0, fun16to2, &paintManager, 0, NULL);
				
				OneKeyCheck();
				return;
			}
			if (strName == _T("btnOneKeyRepair"))
			{
				OneKeyRepair();
				return;
			}
			if (strName == _T("btnCloseStatus"))
			{
				int iCloseStatus = GetPrivateProfileInt(TEXT("CloseStatus"), TEXT("status"), 1, inisrc);
				SetCloseStatus(!iCloseStatus);
				return;
			}
			if (strName == _T("btnAutoRun"))
			{
				int iAutoRun = GetPrivateProfileInt(TEXT("AutoRun"), TEXT("status"), 1, inisrc);
				SetAutoRun(!iAutoRun);
				return;
			}
			if (strName == _T("btnRepair"))
			{
				MessageBox(NULL, _T("���ڰ�װ��"), _T("��ȫ����ؼ�"), NULL);
				return;
			}
		}
		__super::Notify(msg);
	}
	/**
	* @brief �������ùر�ʱ�Ƿ���С��������
	* @param iCloseStatus ģʽ��0�رգ�1����
	*/
	void SetCloseStatus(int iCloseStatus)
	{
		CButtonUI* pBtnCloseStatus = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnCloseStatus")));
		ControlMessageBtn(pBtnCloseStatus, iCloseStatus);
		if (!iCloseStatus)
		{
			WritePrivateProfileString(TEXT("CloseStatus"), TEXT("status"), _T("0"), inisrc);
		}
		else
		{
			WritePrivateProfileString(TEXT("CloseStatus"), TEXT("status"), _T("1"), inisrc);
		}
		return;
	}
	/**
	* @brief �������ÿ���ʱ�Ƿ��Զ�����
	* @param iAutoRunģʽ��0�رգ�1����
	*/
	void SetAutoRun(int iAutoRun)
	{
		CButtonUI* pBtnAutoRun = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnAutoRun")));
		ControlMessageBtn(pBtnAutoRun, iAutoRun);
		UpdateRegisterAutoRun(iAutoRun);
		if (!iAutoRun)
		{
			WritePrivateProfileString(TEXT("AutoRun"), TEXT("status"), _T("0"), inisrc);
		}
		else
		{
			WritePrivateProfileString(TEXT("AutoRun"), TEXT("status"), _T("1"), inisrc);
		}
		return;
	}
	/**
	* @brief �������ø���Ƶ��
	* @param iUpdateFrequency Ƶ�ʣ�0ÿ�죬1ÿ�ܣ�2ÿ��
	*/
	void SetUpdateFrequency(int iUpdateFrequency)
	{
		CComboUI* pComboUpdateFrequency = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("comboUpdateFrequency")));
		pComboUpdateFrequency->SetInternVisible(true);
		if (iUpdateFrequency == 0)
		{
			pComboUpdateFrequency->SelectItem(0);
		}
		else if (iUpdateFrequency == 1)
		{
			pComboUpdateFrequency->SelectItem(1);
		}
		else if (iUpdateFrequency == 2)
		{
			pComboUpdateFrequency->SelectItem(2);
		}
	}
	/**
	* @brief �������ð�ť����ͼƬ
	* @param  pControl �ؼ�
	* @param iStateMode ����״̬��0�رգ�1��
	*/
	void ControlMessageBtn(CControlUI* pControl, int iStateMode)
	{
		if (iStateMode == 0)
		{
			pControl->SetBkImage(_T("mainpage//close.png"));
		}
		else
		{
			pControl->SetBkImage(_T("mainpage//open.png"));
		}
		return;
	}
	/**
	* @brief �������þ���ģʽ�����˲�����Ϣ����
	* @param iControlMode ����ģʽ��0�رգ�1����
	* @param iControlMessage ���˲�����ϢControlMessage��0�رգ�1����
	*/
	void SetControlModeMessage(int iControlMode, int iControlMessage)
	{
		if (iControlMode == 0)//����ģʽ�ر�ʱ�����˲�����ϢҲ�ر�
		{
			iControlMessage = 0;
		}
		CButtonUI* pBtnControlMode = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnControlMode")));
		CTextUI* pTextControlMessage = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textControlMessage")));
		CButtonUI* pBtnControlMessage = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnControlMessage")));
		if (iControlMode == 0)
		{
			pBtnControlMode->SetNormalImage(L"mainpage//circle_ob.png");
			pBtnControlMode->SetHotImage(L"mainpage//circle_pb.png");
			pBtnControlMode->SetText(_T("��������ģʽ"));
			pBtnControlMode->SetTextColor(0xff00a0e9);
			WritePrivateProfileString(TEXT("ControlMode"), TEXT("status"), _T("0"), inisrc);
		}
		else
		{
			pBtnControlMode->SetNormalImage(L"mainpage//circle_og.png");
			pBtnControlMode->SetHotImage(L"mainpage//circle_pg.png");
			pBtnControlMode->SetText(_T("����ģʽ�ѿ���"));
			pBtnControlMode->SetTextColor(0xff1ddb6e);
			WritePrivateProfileString(TEXT("ControlMode"), TEXT("status"), _T("1"), inisrc);
		}
		if (iControlMessage == 0)
		{
			pBtnControlMessage->SetBkImage(L"mainpage//close.png");
			pTextControlMessage->SetText(_T("���˲�����Ϣ�ѹر�"));
			WritePrivateProfileString(TEXT("ControlMessage"), TEXT("status"), _T("0"), inisrc);
		}
		else
		{
			pBtnControlMessage->SetBkImage(L"mainpage//open.png");
			pTextControlMessage->SetText(_T("���˲�����Ϣ�ѿ���"));
			WritePrivateProfileString(TEXT("ControlMessage"), TEXT("status"), _T("1"), inisrc);
		}
		return;
	}
	/**
	* @brief һ�����
	*/
	void OneKeyCheck()
	{
		CContainerUI* pConCheckState = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("conCheckState")));
		CGifAnimUI* pGifChecking = static_cast<CGifAnimUI*>(m_PaintManager.FindControl(_T("gifChecking")));
		CTextUI* pTextState = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textState")));
		CButtonUI* pBtnOneKeyCheck = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnOneKeyCheck")));
		CButtonUI* pBtnOneKeyRepair = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnOneKeyRepair")));
		CButtonUI* pBtnReCheck = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnReCheck")));
		CProgressUI* pProgressOneKeyRepair = static_cast<CProgressUI*>(m_PaintManager.FindControl(_T("progressOneKeyRepair")));
		pConCheckState->SetVisible(false);
		pGifChecking->SetVisible(true);
		pTextState->SetText(_T("���ڼ���С�"));
		/*pProgressOneKeyRepair->SetValue(100);*/
		CheckProgress(pTextState, pProgressOneKeyRepair);
		pTextState->SetText(_T("�����ɣ����޸���"));
		pConCheckState->SetBkImage(_T("mainpage//check_e.png"));
		pConCheckState->SetVisible(true);
		pGifChecking->SetVisible(false);
		pBtnOneKeyCheck->SetVisible(false);
		pBtnOneKeyRepair->SetVisible(true);
		pBtnReCheck->SetVisible(true);
		return;
	}
	void CheckProgress(CTextUI* pTextState, CProgressUI* pProgressOneKeyRepair)
	{
		RECT rc;
		rc.left = 20;
		rc.top = 0;
		rc.right = 9999;
		rc.bottom = 9999;
		CTreeViewUI* pView = static_cast<CTreeViewUI*>(m_PaintManager.FindControl(_T("treeviewCheckRes")));
		pView->RemoveAll();
		for (int i = 1; i <= 5; i++)
		{
			CTreeNodeUI* pNode = new CTreeNodeUI;
			pNode->SetFixedWidth(9999);
			pNode->SetFixedHeight(24);
			pNode->SetAttribute(_T("folderattr"), _T("normalimage=\"file='SysBtn\\list_icon_e.png' dest='6,6,18,18'\" selectedimage=\"file='SysBtn\\list_icon_f.png' dest='6,6,18,18'\""));
			pView->Add(pNode);
			if (i == 1)
			{

				CTextUI* pText = new CTextUI;
				pText->SetText(_T("������"));
				pText->SetTextColor(0xffff0000);
				pText->SetFont(3);
				pNode->Add(pText);
				pText->SetFloat(true);
				pText->SetPos(rc);
				CTreeNodeUI* pNodeLeaf = new CTreeNodeUI;
				pNodeLeaf->SetFixedWidth(9999);
				pNode->AddAt(pNodeLeaf, 0);
				pNodeLeaf->SetItemText(_T("����ȫ����ؼ���δ��װ"));
				pNodeLeaf->SetAttribute(_T("folderattr"), _T("width=\"0\" float=\"true\""));
				CButtonUI* pBtnRepair = new CButtonUI;
				pBtnRepair->SetText(_T("�޸�"));
				pBtnRepair->SetName(_T("btnRepair"));
				pBtnRepair->SetFixedWidth(50);
				pBtnRepair->SetTextColor(0xff1ddb6e);
				pBtnRepair->SetAttribute(_T("width"), _T("50"));
				pNodeLeaf->Add(pBtnRepair);
				pProgressOneKeyRepair->SetValue(20);

			}
			if (i == 2)
			{
				CTextUI* pText = new CTextUI;
				pText->SetText(_T("������"));
				pText->SetTextColor(0xffff8c00);
				pText->SetFont(3);
				pNode->Add(pText);
				pText->SetFloat(true);
				pText->SetPos(rc);
				CTreeNodeUI* pNodeLeaf = new CTreeNodeUI;
				pNodeLeaf->SetFixedWidth(9999);
				pNode->AddAt(pNodeLeaf, 0);
				pNodeLeaf->SetItemText(_T("��DNS�������쳣"));
				pNodeLeaf->SetAttribute(_T("folderattr"), _T("width=\"0\" float=\"true\""));
				pProgressOneKeyRepair->SetValue(40);
			}
			if (i == 3)
			{
				CTextUI* pText = new CTextUI;
				pText->SetText(_T("ϵͳ����"));
				pText->SetFont(3);
				pNode->Add(pText);
				pText->SetFloat(true);
				pText->SetPos(rc);
				for (int i = 0; i < 4; i++)
				{
					CTreeNodeUI* pNodeLeaf = new CTreeNodeUI;
					pNodeLeaf->SetFixedWidth(9999);
					pNode->AddAt(pNodeLeaf, i);
					if (i == 0)
					{
						pNodeLeaf->SetItemText(_T("������ϵͳ��Windows 10 64-bit"));
					}
					if (i == 1)
					{
						pNodeLeaf->SetItemText(_T("����ǰ�û���zdy"));
					}
					if (i == 2)
					{
						pNodeLeaf->SetItemText(_T("������ʱ�䡿����ʱ��׼ȷ"));
					}
					if (i == 3)
					{
						pNodeLeaf->SetItemText(_T("��֤������֤��������"));
					}
					pNodeLeaf->SetAttribute(_T("folderattr"), _T("width=\"0\" float=\"true\""));
				}
				pProgressOneKeyRepair->SetValue(60);

			}
			if (i == 4)
			{
				CTextUI* pText = new CTextUI;
				pText->SetText(_T("���������"));
				pText->SetFont(3);
				pNode->Add(pText);
				pText->SetFloat(true);
				pText->SetPos(rc);
				for (int i = 0; i < 3; i++)
				{
					CTreeNodeUI* pNodeLeaf = new CTreeNodeUI;
					pNodeLeaf->SetFixedWidth(9999);
					pNode->AddAt(pNodeLeaf, i);
					if (i == 0)
					{
						pNodeLeaf->SetItemText(_T("��IE�������9.11.14393.0"));
					}
					if (i == 1)
					{
						pNodeLeaf->SetItemText(_T("��IE����վ�㡿����� csii.com.cn"));
					}
					if (i == 2)
					{
						pNodeLeaf->SetItemText(_T("��IE��ȫ���á�������"));
					}
					pNodeLeaf->SetAttribute(_T("folderattr"), _T("width=\"0\" float=\"true\""));
				}
				pProgressOneKeyRepair->SetValue(80);

			}
			if (i == 5)
			{
				CTextUI* pText = new CTextUI;
				pText->SetText(_T("��������"));
				pText->SetFont(3);
				pNode->Add(pText);
				pText->SetFloat(true);
				pText->SetPos(rc);
				CTreeNodeUI* pNodeLeaf = new CTreeNodeUI;
				pNodeLeaf->SetFixedWidth(9999);
				pNode->AddAt(pNodeLeaf, i);
				pNodeLeaf->SetItemText(_T("��HOSTS�ļ�������"));
				pProgressOneKeyRepair->SetValue(100);
				pNodeLeaf->SetAttribute(_T("folderattr"), _T("width=\"0\" float=\"true\""));
			}
		}
		return;
	}
	/**
	* @brief һ���޸�
	*/
	void OneKeyRepair()
	{
		CTreeViewUI* pView = static_cast<CTreeViewUI*>(m_PaintManager.FindControl(_T("treeviewCheckRes")));
		pView->RemoveAll();
		CContainerUI* pConCheckState = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("conCheckState")));
		CGifAnimUI* pGifChecking = static_cast<CGifAnimUI*>(m_PaintManager.FindControl(_T("gifChecking")));
		CTextUI* pTextState = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textState")));
		CButtonUI* pBtnOneKeyCheck = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnOneKeyCheck")));
		CButtonUI* pBtnOneKeyRepair = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnOneKeyRepair")));
		CButtonUI* pBtnReCheck = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnReCheck")));
		CProgressUI* pProgressOneKeyRepair = static_cast<CProgressUI*>(m_PaintManager.FindControl(_T("progressOneKeyRepair")));
		pTextState->SetText(_T("�����޸��С�"));
		pConCheckState->SetVisible(false);
		pGifChecking->SetVisible(true);
		pProgressOneKeyRepair->SetValue(100);
		pTextState->SetText(_T("�޸���ɣ���ϲ��"));
		pConCheckState->SetBkImage(_T("mainpage//check_r.png"));
		pConCheckState->SetVisible(true);
		pGifChecking->SetVisible(false);
		pBtnOneKeyCheck->SetVisible(true);
		pBtnOneKeyRepair->SetVisible(false);
		pBtnReCheck->SetVisible(false);
		return;
	}
	//��������,����ע���ע�����ȡ��
	void UpdateRegisterAutoRun(int iAutoRun)
	{
		HKEY hKey;
		CDuiString strRegPath = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");//�ҵ�ϵͳ��������  
		if (iAutoRun)
		{
			if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //��������       
			{
				TCHAR szModule[_MAX_PATH];
				GetModuleFileName(NULL, szModule, _MAX_PATH);//�õ������������ȫ·��  
				RegSetValueEx(hKey, _T("AdSafeDemo"), 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, strlen((char*)szModule)); //���һ����Key,������ֵ��"Client"��Ӧ�ó������֣����Ӻ�׺.exe��  
				RegCloseKey(hKey); //�ر�ע���  
			}
			else
			{
				MessageBox(NULL, _T("�ٱ����"), _T("����˰�ť"), NULL);
			}
		}
		else
		{
			if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
			{
				RegDeleteValue(hKey, _T("AdSafeDemo"));
				RegCloseKey(hKey);
			}
		}
	}

};
