#ifndef RBEAST_HTTP_SERVER_ASYNC_H
#define RBEAST_HTTP_SERVER_ASYNC_H

#include <boost/beast/core.hpp>

namespace rbeast
{

    namespace beast = boost::beast;   // from <boost/beast.hpp>
    namespace net = boost::asio;      // from <boost/asio.hpp>
    using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

    // Accepts incoming connections and launches the sessions
    class listener : public std::enable_shared_from_this<listener>
    {
        net::io_context &ioc_;
        tcp::acceptor acceptor_;
        std::shared_ptr<std::string const> doc_root_;

    public:
        listener(
            net::io_context &ioc,
            tcp::endpoint endpoint,
            std::shared_ptr<std::string const> const &doc_root);

        // Start accepting incoming connections
        void
        run();

    private:
        void
        do_accept();

        void
        on_accept(beast::error_code ec, tcp::socket socket);
    };

} // namespace rbeast

#endif