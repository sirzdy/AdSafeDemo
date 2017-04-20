#pragma once
#include <UIlib.h>
using namespace DuiLib;
class CMenuNotify : public INotifyUI
{
public:
	CMenuNotify(void);
	~CMenuNotify(void);
protected:
	void Notify(TNotifyUI& msg);
};

