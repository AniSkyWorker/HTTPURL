#include "stdafx.h"
#include "../HTTPURL/HttpUrl.h"

void VerifyUrl(const CHttpUrl & url, const std::string & expectedDomain, const std::string & expectedDocument, Protocol expectedProtocol, unsigned short expectedPort)
{
	BOOST_CHECK_EQUAL(url.GetDocument(), expectedDocument);
	BOOST_CHECK_EQUAL(url.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(url.GetPort(), expectedPort);
	BOOST_CHECK(url.GetProtocol() == expectedProtocol);
}

BOOST_AUTO_TEST_SUITE(CHttpURL)

	BOOST_AUTO_TEST_SUITE(throw_exeptions_when_given_url_with)

		BOOST_AUTO_TEST_CASE(invalid_protocol_declaration_or_type)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("htp://www.zappa.com/"), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url("ftp://www.zappa.com/"), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(incorrect_slashes)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http:/www.zappa.com/"), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url("http//www.zappa.com/"), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(invalid_domain_declaration)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http///z"), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url("https://     ww.w/zappagens/"), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(invalid_port_declaration)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://www.zappa.com:/zappagens/"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("http://www.zappa.com:"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_SUITE(incorrect_components_same_as)

			BOOST_AUTO_TEST_CASE(incorrect_domain)
			{
				BOOST_REQUIRE_THROW(CHttpUrl url("", ""), std::invalid_argument);
				BOOST_REQUIRE_THROW(CHttpUrl url("ftp://ewqw.ew", ""), std::invalid_argument);
				BOOST_REQUIRE_THROW(CHttpUrl url("zap .com", ""), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(incorrect_document)
			{
				BOOST_REQUIRE_THROW(CHttpUrl url("zappa.com", "/  /"), std::invalid_argument);
				BOOST_REQUIRE_THROW(CHttpUrl url("zappa.com", "/dsfasd/s /"), std::invalid_argument);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_init_with)

		BOOST_AUTO_TEST_CASE(empty_document_then_get_doc_will_be_slash)
		{
			VerifyUrl(CHttpUrl("http://www.zappa.com/"), "www.zappa.com", "/", Protocol::HTTP, 80);
			VerifyUrl(CHttpUrl("http://zappa.com"), "zappa.com", "/", Protocol::HTTP, 80);
		}

		BOOST_AUTO_TEST_CASE(non_empty_document)
		{
			VerifyUrl(CHttpUrl("http://www.zappa.com/whatsnew/images/2016/StarDarlings.jpg"), "www.zappa.com", "/whatsnew/images/2016/StarDarlings.jpg", Protocol::HTTP, 80);
			VerifyUrl(CHttpUrl("http://www.zappa.com/whatsnew/images/2016/"), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP, 80);
		}

		BOOST_AUTO_TEST_CASE(non_standart_port)
		{
			VerifyUrl(CHttpUrl("http://www.zappa.com:33/whatsnew/images/2016/"), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP, 33);
			VerifyUrl(CHttpUrl("https://www.zappa.com:250/whatsnew/images/2016/"), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS, 250);
			VerifyUrl(CHttpUrl("https://www.zappa.com:80"), "www.zappa.com", "/", Protocol::HTTPS, 80);
		}

		BOOST_AUTO_TEST_SUITE(components_same_as)

			BOOST_AUTO_TEST_CASE(empty_document_then_get_doc_will_be_slash)
			{
				VerifyUrl(CHttpUrl("www.zappa.com", ""), "www.zappa.com", "/", Protocol::HTTP, 80);
			}

			BOOST_AUTO_TEST_CASE(non_empty_document)
			{
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/StarDarlings.jpg"), "www.zappa.com", "/whatsnew/images/2016/StarDarlings.jpg", Protocol::HTTP, 80);
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/"), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP, 80);
			}

			BOOST_AUTO_TEST_CASE(non_standart_protocol)
			{
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS, 80);
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP, 80);
			}

			BOOST_AUTO_TEST_CASE(non_standart_port)
			{
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS, 443), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS, 443);
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP, 20), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTP, 20);
				VerifyUrl(CHttpUrl("www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS, 75), "www.zappa.com", "/whatsnew/images/2016/", Protocol::HTTPS, 75);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()