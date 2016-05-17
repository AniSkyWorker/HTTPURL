#pragma once

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string & msg = std::string());
};