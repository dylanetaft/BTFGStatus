#include <iostream>
#include <string>
#include <exception>

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"


void doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response) {
	session.sendRequest(request);
	std::istream& rs = session.receiveResponse(response);
	if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
		std::string json_data;
		Poco::StreamCopier::copyToString(rs,json_data);
		Poco::JSON::Parser parser;
		auto res = parser.parse(json_data);
		auto obj = res.extract<Poco::JSON::Object::Ptr>();
	
		auto pendingPaymentList = obj->getObject("pendingPaymentList");
		if (pendingPaymentList.get() == nullptr) throw std::runtime_error("Unexpected HTTP Data Response"); 
		if (pendingPaymentList->has("4058609956838583597")) {
			auto val = pendingPaymentList->getValue<std::string>("4058609956838583597");
			std::cout << val << "\n";
		}
		else {
			throw std::runtime_error("Account ID does not have any pending payment.");  
		}
	}
	else {
		throw std::runtime_error("Unexpected HTTP Response");
	}
}
int main() {
	  Poco::URI uri("http://burst.btfg.space");
		Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
		Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/pool-payments.json", Poco::Net::HTTPMessage::HTTP_1_1);
		Poco::Net::HTTPResponse response;
		doRequest(session, request, response);
		std::cout << "Hello\n";
		return 0;
}