#pragma once
class OperatorSystemMailManager
{
	typedef std::map<DWORD, tagOperatorSystemMail> MAILS;
public:
	OperatorSystemMailManager();
	virtual ~OperatorSystemMailManager();
	void AddNewMail(tagOperatorSystemMail& mail);
	void OnLoadSystemMailByDB();
	void OnLoadSystemMail(DBO_Cmd_LoadAllSystemMail* pMsg);
protected:
	MAILS _OperatorMails;
};
