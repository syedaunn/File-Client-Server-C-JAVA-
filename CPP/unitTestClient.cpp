#include "CPPClient.cpp"

int main(){

		Client cl("127.0.0.1");
		if(!cl.Recv("/home/aunn/cpp/recvd")){
			printf("Unit Test Failed");
		}else{
			printf("Unit Test Passed");
		}	
}
