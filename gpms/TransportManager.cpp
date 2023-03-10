/*
 * TransportManager.cpp
 *
 *  Created on: 21 Dec 2022
 *      Author: tasneem
 */

#include "TransportManager.h"
#include "ConnectionChanel.h"
#include "MDSMessage.h"
#include "stdlib.h"
#include "SlaveManager.h"
TransportManager::TransportManager() {
	// TODO Auto-generated constructor stub
	ReadPortsFromSetting();
//	cout<< "supported ports : ";
//	for(unsigned int i=0; i < ports_list.size();i++){
//		cout << ports_list[i] << " ";
//	}

}

TransportManager::~TransportManager() {
	// TODO Auto-generated destructor stub
}

void TransportManager::ReadPortsFromSetting(){
   std::ifstream ifs { R"(/home/tasneem/eclipse-workspace/server/src/setting.json)" };
    if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        return;
    }

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );
    assert(doc.IsObject());
    assert(doc.HasMember("Key"));
    assert(doc["Key"].IsString());
    const Value& a = doc["connections"]["tcp"];
    assert(a.IsArray());

    int temp;
    for (SizeType i = 0; i < a.Size(); i++) {
    		temp=a[i]["port"].GetInt();
            ports_list.push_back(temp);

    }
    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    if ( doc.HasParseError() )
    {
        std::cout << "Error  : " << doc.GetParseError()  << '\n'
                  << "Offset : " << doc.GetErrorOffset() << '\n';
        return;
    }

}


void TransportManager::StartListening(){
	cout << "waiting.." << endl;
	bool stay_in=1;
	do{
		int port_number = ports_list[0];
	    sockaddr_in client;
	    socklen_t clientSize = sizeof(client);
	    char host[NI_MAXHOST];      // Client's remote name
	    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
	    uint8_t buf[4096];
	    vector<char> temp_message;

		int listening = socket(AF_INET, SOCK_STREAM, 0);
	    if (listening == -1)
	    {
	        cerr << "Can't create a socket! Quitting" << endl;
	        exit(0);
	    }

	    // Bind the ip address and port to a socket
	    sockaddr_in hint;
	    hint.sin_family = AF_INET;
	    hint.sin_port = htons(port_number);
	    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	    bind(listening, (sockaddr*)&hint, sizeof(hint));
	    listen(listening, SOMAXCONN);

	    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	    memset(service, 0, NI_MAXSERV);

	    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	    {
	        cout << host << " 2.connected on port " << service << endl;
	    }
	    else
	    {
	        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	        cout << host << " 1.connected on port " << ntohs(client.sin_port) << endl;
	    }

	    close(listening);

	    while (true)
	    {
	    	temp_message.clear();
	        memset(buf, 0, 4096);

	        // Wait for client to send data
	        int bytesReceived = recv(clientSocket, buf, 4096, 0);
	        if (bytesReceived == -1)
	        {
	            cerr << "Error in recv(). Quitting" << endl;
	            close(clientSocket);
	            //continue;
	            break;
	        }

	        if (bytesReceived == 0)
	        {
	            cout << "Client disconnected " << endl;
	            close(clientSocket);
	            //stay_in = 0;
	            break;
	        }
//------------- decode message in slave manager------------

	        uint8_t fCode = buf[7];
	        uint8_t *resp_msg;
	        resp_msg = SlaveManager::sendMessage(fCode, buf);

//------------- return response to client -----------------

	        write(clientSocket, resp_msg,256);
	        //here we should check if 256 bytes is enough or not...

	    }
	}while(stay_in);

}

