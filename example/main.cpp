#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/core/macro/codegen.hpp"

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  * Message Data-Transfer-Object
 *   */
class MessageDto : public oatpp::DTO {

    DTO_INIT(MessageDto, DTO /* Extends */)
    DTO_FIELD(Int32, statusCode);   // Status code field
    DTO_FIELD(String, message);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)
class Handler : public oatpp::web::server::HttpRequestHandler {
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;
public:
    /*
     * Construct with - object mapper
     * */
    Handler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper> & objectMapper)
        :m_objectMapper{objectMapper} {}
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
        auto message {MessageDto::createShared()};
        message->statusCode = 1024;
        message->message = "hello ddata!!";
        return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
    }
};

void run() {

    auto objectMapper {oatpp::parser::json::mapping::ObjectMapper::createShared()};

    auto router = oatpp::web::server::HttpRouter::createShared();

    router->route("GET", "/hello", std::make_shared<Handler>(objectMapper));

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::
    createShared(router);
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::
    createShared({"localhost", 8001, oatpp::network::Address::IP_4});

    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGI("myapp","port:%s", connectionProvider->getProperty("port").getData());
    server.run();
}
class Sqlite{
public:
private:
    /*
     * save SQL statement
     * */
    std::string m_sqlSatement;
};
int main() {
    oatpp::base::Environment::init();

    run();

    oatpp::base::Environment::destroy();

    return 0;
}
