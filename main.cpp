#include <stdio.h>
#include <libssh/libssh.h> 
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <regex>
#include "Classes.h"
#include "nlohmann/json.hpp"
//gcc *.cpp -o SSH -std=c++11 -lssh
using json = nlohmann::json;

int main(int argc, char **argv)
{
    const char szInputText[] = R"(
    {
        "JSON": 
        {
            "ID": 11,
            "Host":  "chns@dev.web-control.ru",
            "Port": 22033,
            "Username enter": "chns",
            "Pass enter": "Xsw23edc",
            "Script": 
            [
                {
                "Command": " grep home /etc/passwd | cut -d: -f1\n", 
                "Expect":"jira"
                },

            ]

        }
    }
    )";
//Вывод всех юзеров - " grep home /etc/passwd | cut -d: -f1\n"  либо "sed 's/:.*//' /etc/passwd\n"
//rc = ssh_Channel_request_exec(Channel, " echo -e \"Xsw23edc\nCde34rfv\nCde34rfv\n\" | passwd | tail -n +2\n");
//Смена пароля от юзера (норм вывод) " script -qc ' echo -e \"Xsw23edc\nCde34rfv\nCde34rfv\n\" | passwd'"
//Смена пароля из рута (норм) rc=ssh_Channel_request_exec(Channel, 
//" sh -c \"sleep 1; echo Xsw23edc\" | script -qc 'su -c \"sleep 1; echo -e \\\"Cde34rfv\\nCde34rfv\\n\\\" | passwd chns\"' | tail -n +2\n");
//Проверка актуальности -  rc=ssh_Channel_request_exec(Channel, " sh -c \"sleep 1; echo Xsw23edc\" | script -qc 'su -c \"whoami\" chns' | tail -n +2\n");
/*


                {
                "Command": "su chns\n", 
                "Expect":"Password:"
                },
                {
                "Command": "Xsw23edc\n", 
                "Expect":""
                },
                {
                "Command": "whoami\n", 
                "Expect":"chns\r\n"
                }

               {
                "Command": "su root\n", 
                "Expect":"Password:"
                },
                {
                "Command": "Xsw23edc\n", 
                "Expect":"root@"
                },
                {
                "Command": "passwd chns\n", 
                "Expect":"Enter new UNIX password:"
                },
                {
                "Command": "Xsw23edc\n", 
                "Expect":"Retype new UNIX password:"
                },
                {
                "Command": "Xsw23edc\n", 
                "Expect":"passwd: password updated successfully"
                }


                {
                "Command": "passwd\n", 
                "Expect":"\\(current\\) UNIX password:"
                },
                {
                "Command": "Xsw23edc\n", 
                "Expect":"Enter new UNIX password:"
                },
                {
                "Command": "Cde34rfv\n", 
                "Expect":"Retype new UNIX password:"
                },
                {
                "Command": "Cde34rfv1\n", 
                "Expect":"passwd: password updated successfully"
                }


                {
                "Command": " grep home /etc/passwd | cut -d: -f1\n", 
                "Expect":"jira"
                },
                {
                "Command": " ls\n", 
                "Expect":"qpm"
                }

                {
                "Command": " mysql -u root -p\n", 
                "Expect":"Enter"
                },
                {
                "Command": "Zaq12wsx\n", 
                "Expect":"Welcome"
                },
                {
                "Command": "use mysql;\n", 
                "Expect":" changed"
                },
                {
                "Command": "select User from user;\n", 
                "Expect":"User"
                },

                {
                "Command": "exit\n", 
                "Expect":"Bye"
                },
*/

    int nCallback=0;
   /* ssh_channel Channel;
    ssh_session Session;
    Session = ssh_new();
    Channel = ssh_channel_new(Session); */
    
    //CSshClient TObjSshClient(nId, sHost, nPort, sUsernameEnter, sPassEnter, nComNumb, sCommands, sExpects);
    CSshClient TObjSshClient(szInputText);
    nCallback=TObjSshClient.Connection();//Channel, Session);
    //if (nCallback==0) nCallback=TObjSshClient.ExecuteCommand(Channel, Session);


    return 0;
}




