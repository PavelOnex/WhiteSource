
#ifndef SSH_client_H 
#define SSH_client_H
#include <stdio.h>
#include <libssh/libssh.h> 
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
class IPasswordAgent
{
public:
	virtual ~IPasswordAgent(){};
	virtual int CheckExpect(string sOut, int nCommandNumber) = 0;
	virtual string WriteConsole(ssh_channel Channel) = 0;
	virtual string CleanOutput(ssh_channel Channel, string sOut) = 0;
	virtual void MakeJsonOutput(int nGlobalStatus, string sValue, int nCommandNumberError) = 0;
	virtual int Connection()=0;//ssh_channel Channel, ssh_session Session) = 0;
	//virtual int ExecuteCommand(ssh_channel Channel, ssh_session Session) = 0;
};

class AbstractPasswordAgent : public IPasswordAgent
{
protected:
	ssh_session Session= ssh_new();
	ssh_channel Channel = ssh_channel_new(Session);
	int m_nId;
	string m_sHost;
	int m_nPort;
	string m_sUsernameEnter;
	string m_sPassEnter;
	int m_nNumber;
	string *m_sCommand;
	string *m_sExpect;
	//virtual int ExecuteCommand(ssh_channel Channel, ssh_session Session);
	
public:
	AbstractPasswordAgent(){};
	virtual ~AbstractPasswordAgent(){};
	virtual int Connection();//ssh_channel Channel, ssh_session Session);
	virtual void MakeJsonOutput(int nGlobalStatus, string sValue, int nCommandNumberError);
	virtual int CheckExpect(string sOut, int nCommandNumber);
};
class CSshClient : public AbstractPasswordAgent
{
protected:
	virtual string WriteConsole(ssh_channel Channel);
public:
	//CSshClient(int nId, const string csHost, int nPort, const string csUsernameEnter, const string csPassEnter, int nNumber, string *sCommand, string *sExpect);
	CSshClient(const char *szInputJson);
	~CSshClient(); 
	//virtual int ExecuteCommand(ssh_channel Channel, ssh_session Session);
	
	virtual string CleanOutput(ssh_channel Channel, string sOut);
};


#endif