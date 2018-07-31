#include <stdio.h>
#include <iomanip>
#include <libssh/libssh.h> 
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "Classes.h"
//#include "nlohmann/json.hpp"
using namespace std;
string CSshClient::WriteConsole(ssh_channel Channel)
{  
  int nBytes;
  char szBuffer[2024];
  stringstream sStream;
  nBytes = ssh_channel_read_nonblocking(Channel, szBuffer, sizeof(szBuffer), 0);
  sStream<<szBuffer;
  write(1, szBuffer, nBytes);
  memset(szBuffer, 0, sizeof(szBuffer));
  return sStream.str(); 
}



/*
CSshClient::CSshClient(int nId, const string csHost, int nPort, const string csUsernameEnter, const string csPassEnter, int nNumber, string *sCommand, string *sExpect)
{
  m_nId=nId;
	m_sHost = csHost;
	m_nPort = nPort;
	m_sUsernameEnter = csUsernameEnter;
	m_sPassEnter = csPassEnter;
  m_nNumber=nNumber;
  m_sCommand=new string[nNumber];
  m_sExpect=new string[nNumber];
  for (int i =0; i<nNumber; i++)
  {
    m_sCommand[i]=sCommand[i];
    m_sExpect[i]=sExpect[i];
  }
} */

int AbstractPasswordAgent::Connection()//ssh_channel Channel, ssh_session Session)
{
  
	int nConnection;
  string sValue;
  if (Session == NULL) 
  {
    MakeJsonOutput(2, "Couldn't create the session", -1);
    return 2;
  }			
  ssh_options_set(Session, SSH_OPTIONS_HOST, m_sHost.c_str());
	ssh_options_set(Session, SSH_OPTIONS_PORT, &m_nPort);
	ssh_options_set(Session, SSH_OPTIONS_USER, m_sUsernameEnter.c_str());
	nConnection = ssh_connect(Session);
	if (nConnection != SSH_OK) 
  {
    sValue="Error connecting to" + m_sHost + ": " + ssh_get_error(Session);
    MakeJsonOutput(2, sValue, -1);
    return 2;
  }   
  if (Channel == NULL) return 2;
  nConnection = ssh_userauth_password(Session, m_sUsernameEnter.c_str(), m_sPassEnter.c_str());
  if (nConnection == SSH_AUTH_SUCCESS) 
  {
  	cout<<"OKEY!"<<endl;
  	return 0;
  }
  if (nConnection != SSH_AUTH_SUCCESS) 
  {
    
    sValue="Error authenticating with login " + m_sUsernameEnter + ": " + ssh_get_error(Session);
    MakeJsonOutput(2, sValue, -1);
    ssh_disconnect(Session);
    ssh_free(Session);
    return 2;
  }
  return 2;
}
