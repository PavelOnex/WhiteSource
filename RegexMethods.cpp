#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <regex>
#include "Classes.h"
using namespace std;
int AbstractPasswordAgent::CheckExpect(string sOut, int nCommandNumber)
{
  int nResult=0;
  regex ExpectValue(m_sExpect[nCommandNumber]);
  if (regex_search (sOut.begin(), sOut.end(), ExpectValue) == true) nResult = 0;
  else nResult = 1; 
  cout<<endl<<"nStatus "<<nResult<<endl; 
  return nResult;
}

string CSshClient::CleanOutput(ssh_channel Channel, string sOut)
{ 
  regex Expression("[!-}\\s\\x1b]+");
  smatch Reg;   
  string sOutComplete;
  regex Enter("^\r\n.{0,3}");
  if (regex_search (sOut, Reg, Expression) == true)
  {
    for (int iLength=0; iLength<Reg.length(); iLength++)
      sOutComplete+=sOut[iLength];
    if (regex_match(sOutComplete, Reg, Enter)==false)
    {
      return sOutComplete;
    }
    else 
    {
      sleep(2);
      smatch RegLast;
      string sOutCompleteLast;
      string sOutLast=WriteConsole(Channel);
      if (regex_search (sOutLast, RegLast, Expression) == true) 
      {
        for (int iLength=0; iLength<RegLast.length(); iLength++)
          sOutCompleteLast+=sOutLast[iLength];
        return sOutCompleteLast; 
      } 
      return sOutComplete;  
    }
  } else return sOut; 
}