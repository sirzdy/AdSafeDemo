#pragma once
#include <UIlib.h>
#include <stack>
using namespace DuiLib;
class Calculator : public WindowImplBase
{

public:

	virtual LPCTSTR    GetWindowClassName()const{ return _T("Calculator "); }
	virtual CDuiString GetSkinFolder()          { return _T(""); }
	virtual CDuiString GetSkinFile()            { return _T("Calculator.xml"); }
	CDuiString labEquation =_T("");
	CWndShadow m_WndShadow;
	virtual void InitWindow()
	{
		m_WndShadow.Create(m_hWnd);
		m_WndShadow.SetSize(3);
		m_WndShadow.SetColor(0xFF123456);
		m_WndShadow.SetDarkness(200);
		m_WndShadow.SetPosition(0, 0);
	}
	virtual void    Notify(TNotifyUI& msg)
	{
		CDuiString strName = msg.pSender->GetName();
		if (msg.sType == _T("click"))
		{
			if (strName == _T("btnOne"))
			{
				labEquation += _T("1");
			}
			if (strName == _T("btnTwo"))
			{
				labEquation += _T("2");
			}
			if (strName == _T("btnThree"))
			{
				labEquation += _T("3");
			}
			if (strName == _T("btnFour"))
			{
				labEquation += _T("4");
			}
			if (strName == _T("btnFive"))
			{
				labEquation += _T("5");
			}
			if (strName == _T("btnSix"))
			{
				labEquation += _T("6");
			}
			if (strName == _T("btnSeven"))
			{
				labEquation += _T("7");
			}
			if (strName == _T("btnEight"))
			{
				labEquation += _T("8");
			}
			if (strName == _T("btnNine"))
			{
				labEquation += _T("9");
			}
			if (strName == _T("btnZero"))
			{
				labEquation += _T("0");
			}
			if (strName == _T("btnPoint"))
			{
				labEquation += _T(".");
			}
			if (strName == _T("btnAddition"))
			{
				labEquation += _T("+");
			}
			if (strName == _T("btnSubtraction"))
			{
				labEquation += _T("-");
			}
			if (strName == _T("btnMultiplication"))
			{
				labEquation += _T("*");
			}
			if (strName == _T("btnDivision"))
			{
				labEquation.Append(_T("/"));
			}
			if (strName == _T("btnClear"))
			{
				labEquation.Empty();
			}
			if (strName == _T("btnDel"))
			{
				int len = labEquation.GetLength();
				labEquation = labEquation.Left(len - 1);
			}
			if (strName == _T("btnLeftBracket"))
			{
				labEquation.Append(_T("("));
			}
			if (strName == _T("btnRightBracket"))
			{
				labEquation.Append(_T(")"));
			}
			if (strName == _T("btnFactorial"))
			{
				labEquation.Append(_T("!"));
			}
			if (strName == _T("btnRoot"))
			{
				labEquation.Append(_T("¡Ì"));
			}
			if (strName == _T("btnPower"))
			{
				labEquation.Append(_T("^"));
			}
			if (strName == _T("btnMod"))
			{
				labEquation.Append(_T("%"));
			}
			if (strName == _T("btnMod"))
			{
				labEquation.Append(_T("%"));
			}
			CLabelUI* pLabEquation = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("labEquation")));
			pLabEquation->SetText(labEquation);
			if (strName == _T("btnResult"))
			{
				int res;
				CDuiString sRes,s;
				stack<int>opnd;
				int a=0, b=0;
				stack<char>optr;
				for (int i = 0; i < labEquation.GetLength();i++)
				{
					sRes = labEquation.Mid(i,1);
					if (sRes>=_T("0")&&sRes<=_T("9"))
					{
						if (sRes==_T("0"))
						{
							a = a * 10 + 0;
						}
						if (sRes == _T("1"))
						{
							a = a * 10 + 1;
						}
						if (sRes == _T("2"))
						{
							a = a * 10 + 2;
						}
						if (sRes == _T("3"))
						{
							a = a * 10 + 3;
						}
						if (sRes == _T("4"))
						{
							a = a * 10 + 4;
						}
						if (sRes == _T("5"))
						{
							a = a * 10 + 5;
						}
						if (sRes == _T("6"))
						{
							a = a * 10 + 6;
						}
						if (sRes == _T("7"))
						{
							a = a * 10 + 7;
						}
						if (sRes == _T("8"))
						{
							a = a * 10 + 8;
						}
						if (sRes == _T("9"))
						{
							a = a * 10 + 9;
						}
					}
					if (sRes == _T("+") ||sRes == _T("-")||sRes == _T("*")|| sRes == _T("/"))
					{
						opnd.push(a);
						a = 0;
						if (sRes == _T("+"))
						{
							optr.push('+');
						}
						if (sRes == _T("-"))
						{
							optr.push('-');
						}
						if (sRes == _T("*"))
						{
							optr.push('*');
						}
						if (sRes == _T("/"))
						{
							optr.push('/');
						}
					}
				}
				CLabelUI* pLabResult = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("labResult")));
				int c[20],i=0 ;
				for (;a!=0;i++)
				{
					c[i] = a % 10;
					a = a / 10;
				}
				while (i-->0)
				{
					if (c[i]==0)
					{
						s.Append(_T("0"));
					}
					if (c[i]==1)
					{
						s.Append(_T("1"));
					}
					if (c[i] == 2)
					{
						s.Append(_T("2"));
					}
					if (c[i] == 3)
					{
						s.Append(_T("3"));
					}
					if (c[i] == 4)
					{
						s.Append(_T("4"));
					}
					if (c[i] == 5)
					{
						s.Append(_T("5"));
					}
					if (c[i] == 6)
					{
						s.Append(_T("6"));
					}
					if (c[i] == 7)
					{
						s.Append(_T("7"));
					}
					if (c[i] == 8)
					{
						s.Append(_T("8"));
					}
					if (c[i] == 9)
					{
						s.Append(_T("9"));
					}

				}
				
				//sRes = labEquation.Mid(3,1);
				pLabResult->SetText(s);
				
			}
		}
		__super::Notify(msg);
	}
};