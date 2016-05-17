#pragma once
#include "UrlParsingError.h"

class CHttpUrl
{
public:
	CHttpUrl(const std::string & url);
	CHttpUrl(const std::string & domain, const std::string & document, Protocol protocol = Protocol::HTTP, unsigned short port = 80);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	void ParseUrl(const std::string & url);
	static Protocol GetProtocolType(const std::string & scheme);
	static bool IsDomainCorrect(const std::string & domain);

	static std::string GetDocumentPath(const std::string & document);
	static std::string GetDomain(const std::string & str);
	static std::string GetProtocol(const std::string & str);
	static std::string GetPort(const std::string & str);

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};