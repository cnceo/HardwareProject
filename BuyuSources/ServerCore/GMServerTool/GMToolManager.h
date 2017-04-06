#pragma once



class GMToolManager
{
public:
	GMToolManager();
	virtual ~GMToolManager();
public:
	bool Init();
	void SendLoginReq(const char* Account, const char* PassWord);
	void KickUser(DWORD UserID, int FrozenTime);
	void SendQueryUser(QueryUserType en, CString NickName);
	void Update();
	bool HandleControlMsg(NetCmd* pCmd);
	void ConnectControl();
	void SendNetCmdToControl(NetCmd*pCmd);
	void StringToChar(const CString s, char *Destination);
	void Notice(CString n);
public:
	std::map<DWORD, tagRoleInfo>* GetRoleList();
	
protected:
	void OnTcpClientConnect(TCPClient* pClient);
	void OnTcpClientLeave(TCPClient* pClient);
public:
	TCPClient _ControlTcp;
	int _GMToolNetWorkID;
	bool m_ControlIsConnect;
	ControlServerConfig m_ControlServerConfig;
	bool _login_successful;
	std::map<DWORD, tagRoleInfo> _RoleList;
};




