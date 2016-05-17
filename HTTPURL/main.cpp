#include "stdafx.h"
#include "HttpUrl.h"

void HandleStream()
{
	std::string inputStr;
	while (std::getline(std::cin, inputStr))
	{
		try
		{
			CHttpUrl url(inputStr);

			std::cout << "URL: " << url.GetURL() << std::endl
				<< "Protocol: ";
			auto protocol = url.GetProtocol();
			switch (protocol)
			{
			case Protocol::HTTP:
				std::cout << "http";
				break;
			case Protocol::HTTPS:
				std::cout << "https";
				break;
			}
			std::cout << std::endl
				<< "Domain name: " << url.GetDomain() << std::endl
				<< "Document: " << url.GetDocument() << std::endl
				<< "Port: " << url.GetPort() << std::endl
				<< "------------------" << std::endl;

		}
		catch (std::invalid_argument const &err)
		{
			std::cout << err.what() << std::endl;
		}
	}
}

int main()
{
	HandleStream();
	return 0;
}