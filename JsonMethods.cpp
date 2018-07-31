#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <regex>
#include "Classes.h"
#include "nlohmann/json.hpp"
using namespace std;
CSshClient::CSshClient(const char *szInputJson)
{
    nlohmann::json JsonComplete;
    try
    {
        JsonComplete = nlohmann::json::parse(szInputJson);
        m_nId=JsonComplete.at("/JSON/ID"_json_pointer);
    	m_sHost=JsonComplete.at("/JSON/Host"_json_pointer);
    	m_nPort=JsonComplete.at("/JSON/Port"_json_pointer);
    	m_sUsernameEnter=JsonComplete.at("/JSON/Username enter"_json_pointer);
    	m_sPassEnter=JsonComplete.at("/JSON/Pass enter"_json_pointer);
    	m_nNumber=JsonComplete["JSON"]["Script"].size();
    	m_sCommand=new string[m_nNumber];
    	m_sExpect=new string[m_nNumber];
    	for (int iCommands=0; iCommands<m_nNumber; iCommands++)
    	{
    		m_sCommand[iCommands]=JsonComplete["JSON"]["Script"][iCommands]["Command"];
    		m_sExpect[iCommands]=JsonComplete["JSON"]["Script"][iCommands]["Expect"];
    	}
    }
    catch(...) 
    {
       	cout<<"JSON format error"<<endl;
    }
}

CSshClient::~CSshClient()
{
    delete[] m_sCommand;
    delete[] m_sExpect;
} 

void AbstractPasswordAgent::MakeJsonOutput(int nGlobalStatus, string sValue, int nCommandNumberError)
{
  nlohmann::json JsonOutput;
  JsonOutput["ID"]=m_nId;
  JsonOutput["Global status"]=nGlobalStatus;
  JsonOutput["Value"]=sValue;
  if (nCommandNumberError==-1)
  {
    JsonOutput["Command number error"];
  } 
  else 
  {
    JsonOutput["Command number error"]=nCommandNumberError;
  }
  cout<<setw(4)<<JsonOutput<<endl;
}

