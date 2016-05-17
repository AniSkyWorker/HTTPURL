#include "stdafx.h"
#include "HttpUrl.h"

CHttpUrl::CHttpUrl(const std::string & url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(const std::string & domain, const std::string & document, Protocol protocol, unsigned short port)
	: m_domain(IsDomainCorrect(domain) ? domain: "")
	, m_document(GetDocumentPath(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

void CHttpUrl::ParseUrl(const std::string & url)
{
	std::string copy(url);

	auto protocolStr = GetProtocol(copy);
	m_protocol = GetProtocolType(protocolStr);
	copy = copy.substr(protocolStr.size() + 3, copy.size() - 1);

	auto domain = GetDomain(copy);
	m_domain = IsDomainCorrect(domain) ? domain : "";
	copy = copy.substr(m_domain.size(), copy.size() - 1);

	if (copy[0] == ':')
	{
		auto portStr = GetPort(copy);
		copy = copy.substr(portStr.size() + 1, copy.size() - 1);
		m_port = std::stoi(portStr);
	}
	else
	{
		m_port = static_cast<unsigned short>(m_protocol);
	}

	m_document = GetDocumentPath(copy);
}

std::string CHttpUrl::GetDomain(const std::string & str)
{
	auto domainEnd = str.find(':');
	if (domainEnd == std::string::npos)
	{
		domainEnd = str.find("/");
	}

	return str.substr(0, domainEnd);
}

bool CHttpUrl::IsDomainCorrect(const std::string & domain)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain's empty.");
	}
	else if (std::any_of(domain.begin(), domain.end(), [&](char ch) {return (isspace(ch) || (ch == '/') || (ch == '\'')); }))
	{
		throw std::invalid_argument("Domain mustn't contain spaces, tabulation or slash.");
	}

	return true;
}

std::string CHttpUrl::GetDocumentPath(const std::string & document)
{
	if (std::any_of(document.begin(), document.end(), [&](char ch) {return (isspace(ch));}))
	{
		throw std::invalid_argument("Document mustn't contain spaces or tabulation.");
	}

	if (document[0] != '/')
	{
		return '/' + document;
	}

	return document;
}

std::string CHttpUrl::GetProtocol(const std::string & str)
{
	std::string protocolDel = "://";
	auto protocolEnd = str.find(protocolDel);

	if (protocolEnd == std::string::npos)
	{
		throw CUrlParsingError("Invalid URL protocol.");
	}

	return str.substr(0, protocolEnd);
}

std::string CHttpUrl::GetPort(const std::string & str)
{
	auto portEnd = str.find('/');
	auto portStr = str.substr(1, portEnd - 1);

	if (portStr.empty())
	{
		throw CUrlParsingError("Invalid URL port.");
	}

	return portStr;
}

std::string CHttpUrl::GetURL() const
{
	std::string protocol;
	switch (m_protocol)
	{
	case Protocol::HTTP:
		protocol = "http";
		break;
	case Protocol::HTTPS:
		protocol = "https";
		break;
	default:
		protocol = "";
		break;
	}

	return protocol + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::GetProtocolType(const std::string & protocol)
{
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw std::invalid_argument("Invalid protocol type");
}